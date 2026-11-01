/*
* Adéla Grichová
* GRI0073
* ZPG 2026
*/

#include "ForestScene.h"
#include "tree.h"
#include "bushes.h"
#include "ground.h"
#include "clock.h"
#include "sphere.h"
#include "login.h"

#include "ClockHands.h"

namespace
{
	static float RandomFloat(float min, float max)
	{
		float random = ((float)rand()) / (float)RAND_MAX; // random float between 0.0 and 1.0
		float range = max - min;
		return (random * range) + min;
	}
}

ForestScene::ForestScene(Camera& camera) : Scene(camera), light(glm::vec3(0.0f, 0.1f, 0.0f), 1.0f, 0.35f, 0.45f)
{
	ShaderProgram* treeShader = AddShaderProgram("shaders/tree.vert", "shaders/light/forest-blinn.frag");
	ShaderProgram* bushShader = AddShaderProgram("shaders/bush.vert", "shaders/light/forest-blinn.frag");
	clockShader = AddShaderProgram("shaders/clock.vert", "shaders/light/forest-blinn.frag");
	ShaderProgram* groundShader = AddShaderProgram("shaders/bush.vert", "shaders/light/forest-blinn.frag");
	ShaderProgram* fireflyShader = AddShaderProgram("shaders/firefly.vert", "shaders/light/firefly-const.frag");
	ShaderProgram* loginShader = AddShaderProgram("shaders/login.vert", "shaders/light/forest-blinn.frag");

	light.Attach(treeShader);
	light.Attach(bushShader);
	light.Attach(clockShader);
	light.Attach(groundShader);
	light.Attach(loginShader);

	Model* treeModel = AddModel(tree, LAYOUT_POS_NORMAL);
	Model* bushModel = AddModel(bushes, LAYOUT_POS_NORMAL);
	Model* clockModel = AddModel(clockMod, LAYOUT_POS_NORMAL_COLOR);
	Model* groundModel = AddModel(ground, LAYOUT_POS_NORMAL);
	Model* fireflyModel = AddModel(sphere, LAYOUT_POS_NORMAL);
	Model* loginModel = AddModel(login, LAYOUT_POS_NORMAL);

	for (int i = 0; i < 74; i++) {
		float x = RandomFloat(-30.0f, 30.0f);
		float z = RandomFloat(-0.8f, 20.0f);

		float angle = RandomFloat(0.0f, 359.0f);	// random rotation angle in degrees
		float scale = RandomFloat(0.5f, 1.2f);

		auto treeTransform = std::make_shared<TransformationComposite>();
		treeTransform->Add(std::make_shared<Translation>(glm::vec3(x, -1.0f, z)));
		treeTransform->Add(std::make_shared<Rotation>(angle, glm::vec3(0, 1, 0)));
		treeTransform->Add(std::make_shared<Scale>(glm::vec3(scale)));

		AddObject(treeModel, treeShader, treeTransform);
	}

	for (int i = 0; i < 150; i++) {
		float x = RandomFloat(-30.0f, 30.0f);
		float z = RandomFloat(-0.8f, 20.0f);

		float angle = RandomFloat(0.0f, 359.0f);	// random rotation angle in degrees
		float scale = RandomFloat(0.8f, 2.0f);

		auto bushTransform = std::make_shared<TransformationComposite>();
		bushTransform->Add(std::make_shared<Translation>(glm::vec3(x, -1.0f, z)));
		bushTransform->Add(std::make_shared<Rotation>(angle, glm::vec3(0, 1, 0)));
		bushTransform->Add(std::make_shared<Scale>(glm::vec3(scale)));

		AddObject(bushModel, bushShader, bushTransform);
	}

	auto clockTransform = std::make_shared<TransformationComposite>();
	clockTransform->Add(std::make_shared<Translation>(glm::vec3(1.0f, 0.3f, 4.5f)));
	clockTransform->Add(std::make_shared<Rotation>(-180.0f, glm::vec3(0, 1, 0)));
	clockTransform->Add(std::make_shared<Scale>(glm::vec3(-0.5f, 0.5f, 0.5f)));

	AddObject(clockModel, clockShader, clockTransform);

	auto groundTransform = std::make_shared<TransformationComposite>();
	groundTransform->Add(std::make_shared<Translation>(glm::vec3(0.0f, -1.0f, 0.0f)));
	groundTransform->Add(std::make_shared<Scale>(glm::vec3(60.0f, 1.0f, 60.0f)));

	AddObject(groundModel, groundShader, groundTransform);

	auto fireflyTransform = std::make_shared<TransformationComposite>();
	fireflyTransform->Add(std::make_shared<DynamicRotation>(12.0f, glm::vec3(0, 1, 0)));
	fireflyTransform->Add(std::make_shared<Translation>(glm::vec3(0.0f, 0.1f, -6.0f)));
	fireflyTransform->Add(std::make_shared<Scale>(glm::vec3(0.08f)));

	AddObject(fireflyModel, fireflyShader, fireflyTransform);

	auto loginTransform = std::make_shared<TransformationComposite>();
	loginTransform->Add(std::make_shared<Translation>(glm::vec3(0.0f, 0.0f, 5.0f)));
	loginTransform->Add(std::make_shared<Scale>(glm::vec3(0.5f)));

	AddObject(loginModel, loginShader, loginTransform);

	lightTransform = fireflyTransform;
}

void ForestScene::Update(float deltaTime)
{
	ClockHands::Update(clockShader);	// Update the clock hands based on the current time
	light.SetPosition(glm::vec3(lightTransform->GetMatrix()[3]));	// Update the light position based on the sphere's transformation, notifies observers of the change
}

glm::vec3 ForestScene::ClearColor() const
{
	return glm::vec3(0.0f, 0.0f, 0.10f);
}

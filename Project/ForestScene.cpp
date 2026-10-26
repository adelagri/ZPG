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
#include "login.h"

namespace
{
	static float RandomFloat(float min, float max)
	{
		float random = ((float)rand()) / (float)RAND_MAX; // random float between 0.0 and 1.0
		float range = max - min;
		return (random * range) + min;
	}
}

ForestScene::ForestScene(Camera& camera) : Scene(camera)
{
	ShaderProgram* treeShader = AddShaderProgram("shaders/tree.vert", "shaders/tree.frag");
	ShaderProgram* bushShader = AddShaderProgram("shaders/bush.vert", "shaders/bush.frag");
	ShaderProgram* groundShader = AddShaderProgram("shaders/basic.vert", "shaders/basic.frag");
	ShaderProgram* loginShader = AddShaderProgram("shaders/login.vert", "shaders/default.frag");

	Model* treeModel = AddModel(tree, LAYOUT_POS_NORMAL);
	Model* bushModel = AddModel(bushes, LAYOUT_POS_NORMAL);
	Model* groundModel = AddModel(ground, LAYOUT_POS_COLOR);
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

	for (int i = 0; i < 60; i++) {
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

	auto groundTransform = std::make_shared<TransformationComposite>();
	groundTransform->Add(std::make_shared<Translation>(glm::vec3(0.0f, -1.0f, 0.0f)));
	groundTransform->Add(std::make_shared<Rotation>(90.0f, glm::vec3(1, 0, 0))); // rotate the ground to be horizontal
	groundTransform->Add(std::make_shared<Scale>(glm::vec3(60.0f)));

	AddObject(groundModel, groundShader, groundTransform);

	AddLogin({ 0.0f, 0.0f, -3.0f }, 0.5f);
}

glm::vec3 ForestScene::ClearColor() const
{
	return glm::vec3(0.5f, 0.8f, 1.0f);
}

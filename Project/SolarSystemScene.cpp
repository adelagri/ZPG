/*
* Adéla Grichová
* GRI0073
* ZPG 2026
*/

#include "SolarSystemScene.h"
#include "sun.h"
#include "earth.h"
#include "moon.h"
#include "solar_panel.h"
#include "rocket.h"

namespace {
	struct Body {
		std::shared_ptr<TransformationComposite> frame,
		transform;
	};

	Body MakeBody(const std::shared_ptr<TransformationComposite>& parentFrame,
		float orbitSpeed, float orbitRadius, float spinSpeed, float size) 
	{
		auto frame = std::make_shared<TransformationComposite>();
		if (parentFrame) frame->Add(parentFrame);
		frame->Add(std::make_shared<DynamicRotation>(orbitSpeed, glm::vec3(0, 0, 1)));
		frame->Add(std::make_shared<Translation>(glm::vec3(orbitRadius, 0, 0)));

		auto transform = std::make_shared<TransformationComposite>();
		transform->Add(frame);
		transform->Add(std::make_shared<DynamicRotation>(spinSpeed, glm::vec3(0, 0, 1)));
		transform->Add(std::make_shared<Scale>(glm::vec3(size)));
		return { frame, transform };
	}
}

SolarSystemScene::SolarSystemScene(Camera& camera) : Scene(camera)
{
	ShaderProgram* sunShader = AddShaderProgram("shaders/light/sun.vert", "shaders/light/sun.frag");
	ShaderProgram* planetShader = AddShaderProgram("shaders/light/planet.vert", "shaders/light/planet.frag");
	light.Attach(planetShader);

	Model* sunModel = AddModel(sun, LAYOUT_POS_COLOR_NORMAL);
	Model* earthModel = AddModel(earth, LAYOUT_POS_COLOR_NORMAL);
	Model* moonModel = AddModel(moon, LAYOUT_POS_COLOR_NORMAL);
	Model* panelModel = AddModel(solarPanel, LAYOUT_POS_COLOR_NORMAL);
	Model* rocketModel = AddModel(rocket, LAYOUT_POS_COLOR_NORMAL);

	Body sunB = MakeBody(nullptr, 5.0f, 1.0f, 1.5f, 0.4f);
	Body earthB = MakeBody(sunB.frame, 20.0f, 2.5f, 330.0f, 0.3f);
	Body moonB = MakeBody(earthB.frame, 30.0f, 1.0f, 90.0f, 0.15f);
	Body panelB = MakeBody(earthB.frame, 180.0f, 0.7f, 20.0f, 0.08f);
	Body rocketB = MakeBody(sunB.frame, 40.0f, 4.0f, 5.0f, 0.3f);

	AddObject(sunModel, sunShader, sunB.transform);
	AddObject(earthModel, planetShader, earthB.transform);
	AddObject(moonModel, planetShader, moonB.transform);
	AddObject(panelModel, planetShader, panelB.transform);
	AddObject(rocketModel, planetShader, rocketB.transform);

	sunTransform = sunB.transform;
	AddLogin({ -2.0f, -1.0f, 0.0f }, 0.5f);
}

void SolarSystemScene::Update(float deltaTime)
{
	light.SetPosition(glm::vec3(sunTransform->GetMatrix()[3]));	// Update the light position based on the sun's transformation, notifies observers of the change
}

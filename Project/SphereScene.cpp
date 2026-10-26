/*
* Adéla Grichová
* GRI0073
* ZPG 2026
*/

#include "SphereScene.h"
#include "sphere.h"

SphereScene::SphereScene(Camera& camera) : Scene(camera)
{
	ShaderProgram* constantShader = AddShaderProgram("shaders/light/constant.vert", "shaders/light/constant.frag");
	ShaderProgram* lambertShader = AddShaderProgram("shaders/light/lambert.vert", "shaders/light/lambert.frag");
	ShaderProgram* phongShader = AddShaderProgram("shaders/light/phong.vert", "shaders/light/phong.frag");
	ShaderProgram* blinnShader = AddShaderProgram("shaders/light/blinn.vert", "shaders/light/blinn.frag");

	Model* sphereModel = AddModel(sphere, LAYOUT_POS_NORMAL);

	auto sphereTransform1 = std::make_shared<TransformationComposite>();
	sphereTransform1->Add(std::make_shared<Translation>(glm::vec3(1.5f, 0.0f, 0.0f)));
	AddObject(sphereModel, constantShader, sphereTransform1);

	auto sphereTransform2 = std::make_shared<TransformationComposite>();
	sphereTransform2->Add(std::make_shared<Translation>(glm::vec3(0.0f, 1.5f, 0.0f)));
	AddObject(sphereModel, lambertShader, sphereTransform2);

	auto sphereTransform3 = std::make_shared<TransformationComposite>();
	sphereTransform3->Add(std::make_shared<Translation>(glm::vec3(-1.5f, 0.0f, 0.0f)));
	AddObject(sphereModel, phongShader, sphereTransform3);

	auto sphereTransform4 = std::make_shared<TransformationComposite>();
	sphereTransform4->Add(std::make_shared<Translation>(glm::vec3(0.0f, -1.5f, 0.0f)));
	AddObject(sphereModel, blinnShader, sphereTransform4);

	AddLogin({ -2.0f, -2.0f, 0.0f }, 0.5f);
}

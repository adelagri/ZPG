/*
* Adéla Grichová
* GRI0073
* ZPG 2026
*/

#pragma once

#include "Scene.h"
#include "Light.h"

class ForestScene : public Scene
{
public:
    ForestScene(Camera& camera);
	~ForestScene() override = default;

	glm::vec3 ClearColor() const override;

	void Update(float deltaTime) override;

private:
    Light light;

	std::shared_ptr<TransformationComposite> lightTransform;
	ShaderProgram* clockShader = nullptr;
};


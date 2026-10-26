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
	glm::vec3 ClearColor() const override;

private:
    Light light{ glm::vec3(0.0f) };
};


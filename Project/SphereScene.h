/*
* Adéla Grichová
* GRI0073
* ZPG 2026
*/

#pragma once

#include "Scene.h"
#include "Light.h"

class SphereScene : public Scene
{
public:
    SphereScene(Camera& camera);

private:
    Light light{ glm::vec3(0.0f) };
};


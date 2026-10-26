/*
* Adéla Grichová
* GRI0073
* ZPG 2026
*/

#pragma once

#include "Scene.h"
#include "Light.h"

class SolarSystemScene : public Scene
{
public:
    SolarSystemScene(Camera& camera);
    void Update(float deltaTime) override;

private:
    Light light{ glm::vec3(0.0f) };
    std::shared_ptr<TransformationComposite> sunTransform;
};


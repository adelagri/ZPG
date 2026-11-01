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
    ~SolarSystemScene() override = default;

    void Update(float deltaTime) override;

private:
    Light light;

    std::shared_ptr<TransformationComposite> sunTransform;
};


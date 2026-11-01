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
    ~SphereScene() override = default;
};


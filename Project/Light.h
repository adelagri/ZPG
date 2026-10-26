/*
* Adéla Grichová
* GRI0073
* ZPG 2026
*/

#pragma once
#include <vector>
#include <glm/glm.hpp>

#include "ILightObserver.h"

class Light
{
public:
	explicit Light(glm::vec3 p) : position(p) {}

    void Attach(ILightObserver* o);
	void SetPosition(const glm::vec3& p);
	const glm::vec3& GetPosition() const;

private:
	glm::vec3 position;
	std::vector<ILightObserver*> observers; // List of observers to notify when the light changes
};


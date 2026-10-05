/*
* Adéla Grichová
* GRI0073
* ZPG 2026
*/

#pragma once
#include <glm/vec3.hpp>

class Transformation {
public:
	float angle = 0.0f;     // angle of rotation around the y-axis (in radians)
	glm::vec3 translation{ 0.0f }; // translation vector (movement)
	glm::vec3 scale{ 1.0f };       // scaling vector (size)

	int rotationAxis = 0; // 0 for x-axis, 1 for y-axis, 2 for z-axis
};

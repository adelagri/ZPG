/*
* Adéla Grichová
* GRI0073
* ZPG 2026
*/

#pragma once
#include <vector>
#include <glm/glm.hpp>

#include "LightObserver.h"

class Light
{
public:
	explicit Light(glm::vec3 p, float constant, float linear, float quadratic);

	~Light() = default;

    void Attach(LightObserver* o);
	void SetPosition(const glm::vec3& p);
	const glm::vec3& GetPosition() const;

	float GetConstant() const;
	float GetLinear() const;
	float GetQuadratic() const;

private:
	std::vector<LightObserver*> observers; // List of observers to notify when the light changes

	glm::vec3 position;
	float con, lin, quad; // Attenuation factors: constant, linear, quadratic

	void Notify();	// Notify all observers of a change in the light
};


/*
* Adéla Grichová
* GRI0073
* ZPG 2026
*/

#include "Light.h"

Light::Light(glm::vec3 p, float constant, float linear, float quadratic)
	: position(p), con(constant), lin(linear), quad(quadratic) {}

void Light::Attach(LightObserver* o)
{
	observers.push_back(o);
	o->Update(*this);	// Notify the observer of the current light state upon attachment
}

void Light::SetPosition(const glm::vec3& p)
{
	if (p == position) {
		return;
	}

	position = p;
	Notify();
}

const glm::vec3& Light::GetPosition() const
{
	return position;
}

float Light::GetConstant() const
{
	return con;
}

float Light::GetLinear() const
{
	return lin;
}

float Light::GetQuadratic() const
{
	return quad;
}

void Light::Notify()
{
	for (auto* o : observers) {
		o->Update(*this);
	}
}

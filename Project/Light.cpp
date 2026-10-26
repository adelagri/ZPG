/*
* Adéla Grichová
* GRI0073
* ZPG 2026
*/

#include "Light.h"

void Light::Attach(ILightObserver* o)
{
	observers.push_back(o);
	o->OnLightChanged(*this);	// Notify the observer of the current light state upon attachment
}

void Light::SetPosition(const glm::vec3& p)
{
	if (p == position) {
		return;
	}

	position = p;
	for (auto* o : observers) {
		o->OnLightChanged(*this);
	}
}

const glm::vec3& Light::GetPosition() const
{
	return position;
}

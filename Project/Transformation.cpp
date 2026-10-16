/*
* Adéla Grichová
* GRI0073
* ZPG 2026
*/

#include "Transformation.h"
#include <GLFW/glfw3.h>

Translation::Translation(const glm::vec3& offset) : offset(offset) {}

glm::mat4 Translation::GetMatrix() const
{
	return glm::translate(glm::mat4(1.0f), offset);
}

Rotation::Rotation(float angle, const glm::vec3& axis) : angle(angle), axis(axis) {}

glm::mat4 Rotation::GetMatrix() const
{
	return glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis);
}

Scale::Scale(const glm::vec3& scale) : scale(scale) {}

glm::mat4 Scale::GetMatrix() const
{
	return glm::scale(glm::mat4(1.0f), scale);
}

DynamicRotation::DynamicRotation(float speed, const glm::vec3& axis) : speed(speed), axis(axis) {}

glm::mat4 DynamicRotation::GetMatrix() const
{
	float angle = speed * (float)glfwGetTime();	// Calculate the angle based on speed and elapsed time
	return glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis);
}

TransformationComposite &TransformationComposite::Add(std::shared_ptr<Transformation> t)
{
	children.push_back(std::move(t));
	return *this;	// Returns reference to allow chaining of Add calls
}

glm::mat4 TransformationComposite::GetMatrix() const
{
	glm::mat4 M(1.0f);
	for (const auto& c : children)
		M = M * c->GetMatrix();
	return M;
}

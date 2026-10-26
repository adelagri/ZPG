/*
* Adéla Grichová
* GRI0073
* ZPG 2026
*/

#include "Camera.h"

Camera::Camera(glm::vec3 eye, glm::vec3 center, glm::vec3 up) : 
	eye(eye), front(glm::normalize(center - eye)), up(up) 
{
	yaw = 270.0f;
	pitch = 0.0f;
	UpdateFront();
}

glm::mat4 Camera::GetViewMatrix() const
{
	return glm::lookAt(eye, eye + front, up);
}

glm::mat4 Camera::GetProjectionMatrix() const
{
	return glm::perspective(fov, ratio, zNear, zFar);
}

glm::vec3 Camera::GetEye() const
{
	return eye;
}

void Camera::UpdateFront()
{
	float y = glm::radians(yaw);
	float p = glm::radians(pitch);

	front = glm::normalize(glm::vec3(
		cos(p) * cos(y),
		sin(p),
		cos(p) * sin(y)
	));
}

void Camera::Move(float forward, float right)
{
	if (forward == 0.0f && right == 0.0f) {	// No movement, no need to update
		return;
	}

	glm::vec3 f = glm::normalize(glm::vec3(front.x, 0.0f, front.z));
	glm::vec3 rightDir = glm::normalize(glm::cross(f, up));
	eye += f * forward + rightDir * right;

	Notify();
}

void Camera::Rotate(float deltaYaw, float deltaPitch)
{
	yaw += deltaYaw;
	pitch = glm::clamp(pitch + deltaPitch, -89.0f, 89.0f);
	UpdateFront();

	Notify();
}

void Camera::SetRatio(float r)
{
	ratio = r;

	Notify();
}

void Camera::Attach(Observer* observer)
{
	observers.push_back(observer);
	observer->Update(*this);	// Notify the observer immediately with the current camera state
}

void Camera::Notify()
{
	for (Observer* o : observers) {
		o->Update(*this);
	}
}

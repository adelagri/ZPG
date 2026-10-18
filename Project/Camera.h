/*
* Adéla Grichová
* GRI0073
* ZPG 2026
*/

#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Observer.h"

class Camera
{
public:
	Camera(glm::vec3 eye, glm::vec3 center, glm::vec3 up = glm::vec3{0.0f, 1.0f, 0.0f});

	glm::mat4 GetViewMatrix() const;
	glm::mat4 GetProjectionMatrix() const;

	void Move(float forward, float right);
	void Rotate(float deltaYaw, float deltaPitch);
	void SetRatio(float r);
	void Attach(Observer* observer);

private:
	void UpdateFront(); // Update the target vector based on the current rotation angles

	glm::vec3 eye; // Camera position
	glm::vec3 front;	// Target vector
	glm::vec3 up; // Up vector

	std::vector<Observer*> observers; // List of observers to notify when the camera changes

	float yaw;		// Horizontal rotation angle
	float pitch;	// Vertical rotation angle

	float fov = glm::radians(60.0f);
	float ratio = 4.0f / 3.0f;
	float zNear = 0.01f;
	float zFar = 100.0f;

	void Notify();	// Notify all observers of a change in the camera
};


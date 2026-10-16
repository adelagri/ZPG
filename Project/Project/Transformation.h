/*
* Adéla Grichová
* GRI0073
* ZPG 2026
*/

#pragma once
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <memory>

// Component for transformations
class Transformation {
	public:
		virtual ~Transformation() = default;
		virtual glm::mat4 GetMatrix() const = 0;
};

// Derived classes for specific transformations
class Translation : public Transformation {
	public:
		// explicit constructor to prevent implicit conversions from glm::vec3 to Translation
		explicit Translation(const glm::vec3& offset);
		glm::mat4 GetMatrix() const override;

	private:
		glm::vec3 offset;
};

class Rotation : public Transformation {
	public:
		explicit Rotation(float angle, const glm::vec3& axis);
		glm::mat4 GetMatrix() const override;

	private:
		float angle;
		glm::vec3 axis;
};

class Scale : public Transformation {
	public:
		explicit Scale(const glm::vec3& scale);
		glm::mat4 GetMatrix() const override;

	private:
		glm::vec3 scale;
};

// Derived class for dynamic rotation - rotates over time based on speed and axis
class DynamicRotation : public Transformation { 
	public:
		DynamicRotation(float speed, const glm::vec3& axis);
		glm::mat4 GetMatrix() const override;

	private:
		float speed; glm::vec3 axis;
};


// Composite transformation that can hold multiple transformations
class TransformationComposite : public Transformation {
	public:
		TransformationComposite& Add(std::shared_ptr<Transformation> t);
		glm::mat4 GetMatrix() const override;
	private:
		std::vector<std::shared_ptr<Transformation>> children; // Store child transformations
};

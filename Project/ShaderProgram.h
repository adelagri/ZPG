/*
* Adéla Grichová
* GRI0073
* ZPG 2026
*/

#pragma once
#include "Shader.h"
#include "Observer.h"
#include "VertexAttributes.h"
#include "LightObserver.h"
#include "Light.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/ext/vector_float3.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>


class ShaderProgram : public Observer, public LightObserver
{
public:
	ShaderProgram(const char* vertexPath, const char* fragmentPath);
	~ShaderProgram();
	void Use();

	void SetUniform(const char* name, int value);
	void SetUniform(const char* name, float value, bool required = true);
	void SetUniform(const char* name, const glm::vec3& value, bool required = true);
	void SetUniform(const char* name, const glm::mat4& matrix);

	void Update(const Camera& camera) override;	// Update the shader program with the camera's view and projection matrices
	void Update(const Light& light) override;	// Update the shader program with the light's properties

private:
	GLuint Id = 0;
	Shader* VertexShader;
	Shader* FragmentShader;

	GLuint GetID() const { return Id; }
};


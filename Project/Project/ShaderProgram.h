/*
* Adéla Grichová
* GRI0073
* ZPG 2026
*/

#pragma once
#include "Shader.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/ext/vector_float3.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>


class ShaderProgram
{
public:
	ShaderProgram(const char* vertexPath, const char* fragmentPath);
	~ShaderProgram();
	void Use();
	GLuint GetID() const { return Id; }

	void SetUniform1i(const char* name, int value);
	void SetUniform1f(const char* name, float value);
	void SetUniform3f(const char* name, const glm::vec3& value);
	void SetUniformMatrix4fv(const char* name, const glm::mat4& matrix);

private:
	GLuint Id;
	Shader* VertexShader;
	Shader* FragmentShader;
};


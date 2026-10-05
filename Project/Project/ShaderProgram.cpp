/*
* Adéla Grichová
* GRI0073
* ZPG 2026
*/

#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(const char* vertexPath, const char* fragmentPath)
{
	VertexShader = new Shader(GL_VERTEX_SHADER, vertexPath);
	FragmentShader = new Shader(GL_FRAGMENT_SHADER, fragmentPath);

	Id = glCreateProgram();
	glAttachShader(Id, FragmentShader->GetID());
	glAttachShader(Id, VertexShader->GetID());

	glLinkProgram(Id);

	GLint success;
	glGetProgramiv(Id, GL_LINK_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetProgramInfoLog(Id, 512, nullptr, infoLog);
		std::cerr << "Program link error: " << infoLog << std::endl;
		delete VertexShader;
		delete FragmentShader;
		glDeleteShader(Id);
		exit(1);
	}

	delete VertexShader;
	delete FragmentShader;
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(Id);
}

void ShaderProgram::Use()
{
	glUseProgram(Id);
}

void ShaderProgram::SetUniform1i(const char* name, int value)
{
	GLint location = glGetUniformLocation(Id, name);
	if (location == -1)
	{
		std::cerr << "Error: uniform '" << name << "' not found in shader program." << std::endl;
		exit(-1);
	}
	glUniform1i(location, value);
}

void ShaderProgram::SetUniform1f(const char* name, float value)
{
	GLint location = glGetUniformLocation(Id, name);
	if (location == -1)
	{
		std::cerr << "Error: uniform '" << name << "' not found in shader program." << std::endl;
		exit(-1);
	}
	glUniform1f(location, value);
}

void ShaderProgram::SetUniform3f(const char* name, const glm::vec3& value)
{
	GLint location = glGetUniformLocation(Id, name);
	if (location == -1)
	{
		std::cerr << "Error: uniform '" << name << "' not found in shader program." << std::endl;
		exit(-1);
	}
	glUniform3f(location, value.x, value.y, value.z);
}

void ShaderProgram::SetUniformMatrix4fv(const char* name, const glm::mat4& matrix)
{
	GLint location = glGetUniformLocation(Id, name);
	if (location == -1)
	{
		std::cerr << "Error: uniform '" << name << "' not found in shader program." << std::endl;
		exit(-1);
	}
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

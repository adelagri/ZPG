/*
* Adéla Grichová
* GRI0073
* ZPG 2026
*/

#include "Shader.h"

Shader::Shader(GLenum shaderType, const char* shaderFile)
{
	// Creates an empty shader
	Id = glCreateShader(shaderType);

	if (Id == 0)
	{
		std::cout << "Unable to create shader" << std::endl;
		exit(EXIT_FAILURE);
	}

	//Loading the contents of a file into a variable
	std::ifstream file(shaderFile);
	if (!file.is_open())
	{
		std::cout << "Unable to open file " << shaderFile << std::endl;
		glDeleteShader(Id);
		exit(-1);
	}

	// Removes the UTF-8 BOM if present
	std::string shaderCode((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	if (shaderCode.compare(0, 3, "\xEF\xBB\xBF") == 0)
		shaderCode.erase(0, 3);

	// Set the shader source code
	const char* source = shaderCode.c_str();
	glShaderSource(Id, 1, &source, nullptr);

	// Compile the shader source code
	glCompileShader(Id);

	// Check specialization/compilation status
	GLint success;
	glGetShaderiv(Id, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char infoLog[1024];
		glGetShaderInfoLog(Id, sizeof(infoLog), nullptr, infoLog);
		std::cout
			<< "Shader failed:\n"
			<< infoLog << std::endl;
		glDeleteShader(Id);
		exit(1);
	}
}

Shader::~Shader()
{
	glDeleteShader(Id);
}

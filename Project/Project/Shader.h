/*
* Adéla Grichová
* GRI0073
* ZPG 2026
*/

#pragma once

#include <string>
#include <stdio.h>
#include <iostream>
#include <fstream>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

class Shader
{
public:
	Shader(GLenum shaderType, const char* filePath);
	~Shader();
	GLuint GetID() const { return Id; }

private:
	GLuint Id;
};


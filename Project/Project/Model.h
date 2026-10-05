/*
* Adéla Grichová
* GRI0073
* ZPG 2026
*/

#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>


class Model
{
public:
	Model(const float* verticies, int vertexCount, int floatsPerVertex);
	~Model();
	void Draw();

private:
	GLuint VBO;
	GLuint VAO;
	int VertexCount;
};


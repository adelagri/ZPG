/*
* Adéla Grichová
* GRI0073
* ZPG 2026
*/

#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "VertexAttributes.h"

struct VertexLayout {	// describes the layout of the vertex data in the VBO
	int floatsPerVertex;
	int positionOffset;
	int colorOffset;     // -1 = model has no color
	int normalOffset;    // -1 = model has no normal
};

// Predefined vertex layouts for common vertex formats
const VertexLayout LAYOUT_POS_COLOR{ 6, 0, 3, -1 };
const VertexLayout LAYOUT_POS_NORMAL{ 6, 0, -1, 3 };
const VertexLayout LAYOUT_POS_COLOR_NORMAL{ 9, 0, 3, 6 };
const VertexLayout LAYOUT_POS_NORMAL_COLOR{ 9, 0, 6, 3 };

class Model
{
public:
	Model(const float* verticies, int vertexCount, const VertexLayout& layout);
	~Model();

	void SetAttribute(GLuint index, int offset, GLsizei stride);

	void Draw();

private:
	GLuint VBO;
	GLuint VAO;
	int VertexCount;
};


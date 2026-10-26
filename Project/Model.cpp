/*
* Adéla Grichová
* GRI0073
* ZPG 2026
*/

#include "Model.h"

Model::Model(const float* verticies, int vertexCount, const VertexLayout& layout)
{
	// Vertex Buffer Object (VBO)
	VertexCount = vertexCount;
	glGenBuffers(1, &VBO); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);	// bind the VBO
	glBufferData(
		GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(VertexCount * layout.floatsPerVertex * sizeof(float)),
		verticies, GL_STATIC_DRAW);	// copy the vertex data to the VBO

	//Vertex Array Object (VAO)
	glGenVertexArrays(1, &VAO); //generate the VAO
	glBindVertexArray(VAO); //bind the VAO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);	// bind the VBO

	const GLsizei stride = layout.floatsPerVertex * sizeof(float);

	SetAttribute(ATTR_POSITION, layout.positionOffset, stride);	// position attribute is always present
	if (layout.colorOffset >= 0) {
		SetAttribute(ATTR_COLOR, layout.colorOffset, stride);	// color attribute is optional
	}
	if (layout.normalOffset >= 0) {
		SetAttribute(ATTR_NORMAL, layout.normalOffset, stride);	// normal attribute is optional
	}
}

Model::~Model()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void Model::SetAttribute(GLuint index, int offset, GLsizei stride)	// set the vertex attribute pointer
{
	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)(offset * sizeof(float)));
}

void Model::Draw()
{
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, VertexCount);
}

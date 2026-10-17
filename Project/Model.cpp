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

	glEnableVertexAttribArray(0);	// enable the vertex attribute array for position
	// index, number of components, data type, normalized, vertex stride, offset
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)(layout.positionOffset * sizeof(float)));	// VBO is bound, so VAO knows where to find the vertex data and we can set the vertex attribute pointers


	if (layout.colorOffset > 0) {
		glEnableVertexAttribArray(1);	// enable the vertex attribute array for color
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)(layout.colorOffset * sizeof(float)));
	}

	if (layout.normalOffset > 0) {
		glEnableVertexAttribArray(2);	// enable the vertex attribute array for normal
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)(layout.normalOffset * sizeof(float)));
	}
}

Model::~Model()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void Model::Draw()
{
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, VertexCount);
}

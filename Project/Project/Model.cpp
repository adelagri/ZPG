/*
* Adéla Grichová
* GRI0073
* ZPG 2026
*/

#include "Model.h"

Model::Model(const float* verticies, int vertexCount, int floatsPerVertex)
{
	// Vertex Buffer Object (VBO)
	VertexCount = vertexCount;
	glGenBuffers(1, &VBO); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);	// bind the VBO
	glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(VertexCount * floatsPerVertex * sizeof(float)), verticies, GL_STATIC_DRAW);	// copy the vertex data to the VBO

	//Vertex Array Object (VAO)
	glGenVertexArrays(1, &VAO); //generate the VAO
	glBindVertexArray(VAO); //bind the VAO
	glEnableVertexAttribArray(0); //enable vertex attributes
	glEnableVertexAttribArray(1);
	if (floatsPerVertex > 6)
	{
		glEnableVertexAttribArray(2);
	}
	glBindBuffer(GL_ARRAY_BUFFER, VBO);	// bind the VBO

	const auto stride = (GLsizei)(floatsPerVertex * sizeof(float));

	// index, number of components, data type, normalized, vertex stride, offset
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)0);	// VBO is bound, so VAO knows where to find the vertex data and we can set the vertex attribute pointers
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)(3 * sizeof(float)));
	if (floatsPerVertex > 6)
	{
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)(6 * sizeof(float)));
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

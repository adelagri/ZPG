/*
* Adéla Grichová
* GRI0073
* ZPG 2026
*/

#include "DrawableObject.h"
#include <glm/glm.hpp>

DrawableObject::DrawableObject(Model* model, ShaderProgram* shader, std::shared_ptr<Transformation> transformation)
{
	this->model = model;
	this->shader = shader;
	this->transformation = std::move(transformation);
}

void DrawableObject::Draw()
{
	shader->Use();
	shader->SetUniform("modelMatrix", transformation->GetMatrix());	// Set the model matrix uniform in the shader
	shader->SetUniform("material", glm::vec3(material.ambient, material.diffuse, material.specular), false);
	shader->SetUniform("shininess", material.shininess, false);
	model->Draw();
}

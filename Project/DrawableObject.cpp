/*
* Adéla Grichová
* GRI0073
* ZPG 2026
*/

#include "DrawableObject.h"

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
	model->Draw();
}

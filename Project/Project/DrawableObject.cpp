/*
* Adéla Grichová
* GRI0073
* ZPG 2026
*/

#include "DrawableObject.h"

DrawableObject::DrawableObject(Model* model, ShaderProgram* shader) : model(model), shader(shader)
{
}

void DrawableObject::Draw()
{
	shader->Use();
	shader->SetUniform1f("angle", transform.angle);
	shader->SetUniform3f("translation", transform.translation);
	shader->SetUniform3f("scale", transform.scale);
	shader->SetUniform1i("rotationAxis", transform.rotationAxis);
	model->Draw();
}

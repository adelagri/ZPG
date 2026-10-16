/*
* Adéla Grichová
* GRI0073
* ZPG 2026
*/

#pragma once
#include "Model.h"
#include "ShaderProgram.h"
#include "Transformation.h"

class DrawableObject
{
public:
	DrawableObject(Model* model, ShaderProgram* shader, std::shared_ptr<Transformation> transformation);
	void Draw();

	std::shared_ptr<Transformation> transformation; // Transformation component for the object

private:
	Model* model;
	ShaderProgram* shader;
};


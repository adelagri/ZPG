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
	DrawableObject(Model* model, ShaderProgram* shader);
	void Draw();

	Transformation transform;	// Transformation data for the object - public (KeyCallback has direct access)

private:
	Model* model;
	ShaderProgram* shader;
};


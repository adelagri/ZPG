/*
* Adéla Grichová
* GRI0073
* ZPG 2026
*/

#pragma once
#include <vector>
#include "DrawableObject.h"
#include "ShaderProgram.h"
#include "Model.h"

class Scene
{
public:
	~Scene();

	void AddObject(DrawableObject* object);
	ShaderProgram* AddShader(const char* vertexPath, const char* fragmentPath);
	Model* AddModel(const float* verticies, int vertexCount, int floatsPerVertex);

	void Draw();

	std::vector<DrawableObject*>& GetObjects() { return objects; }
	DrawableObject* GetSelectedObject();

	void SelectNextObject();

private:
	std::vector<DrawableObject*> objects;
	std::vector<ShaderProgram*> shaders;
	std::vector<Model*> models;

	int selectedObjIndex = 0; // index of the currently selected object
};


/*
* Adéla Grichová
* GRI0073
* ZPG 2026
*/

#include "Scene.h"

void Scene::AddObject(DrawableObject* object)
{
	objects.push_back(object);
}

ShaderProgram* Scene::AddShader(const char* vertexPath, const char* fragmentPath)
{
	ShaderProgram* shader = new ShaderProgram(vertexPath, fragmentPath);
	shaders.push_back(shader);
	return shader;
}

Model* Scene::AddModel(const float* verticies, int vertexCount, int floatsPerVertex)
{
	Model* model = new Model(verticies, vertexCount, floatsPerVertex);
	models.push_back(model);
	return model;
}

void Scene::Draw()	// Draws all objects in the scene
{
	for (DrawableObject* obj : objects)
	{
		obj->Draw();
	}
}

DrawableObject* Scene::GetSelectedObject()	// Returns the currently selected object in the scene
{
	if (objects.empty()) return nullptr;

	return objects[selectedObjIndex];
}

void Scene::SelectNextObject()	// Selects the next object in the scene
{
	if (objects.empty()) return;

	selectedObjIndex = (selectedObjIndex + 1) % objects.size();
}

Scene::~Scene()	// Destructor - deletes all objects, shaders, and models in the scene
{
	for (DrawableObject* obj : objects)
	{
		delete obj;
	}
	for (ShaderProgram* shader : shaders)
	{
		delete shader;
	}
	for (Model* model : models)
	{
		delete model;
	}
}



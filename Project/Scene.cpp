/*
* Adéla Grichová
* GRI0073
* ZPG 2026
*/

#include "Scene.h"
#include "login.h"

glm::vec3 Scene::ClearColor() const
{
	return {0, 0, 0};
}

void Scene::Draw()
{
	for (auto& object : objects) {
		object->Draw();
	}
}

ShaderProgram* Scene::AddShaderProgram(const char* vert, const char* frag)
{
    shaderPrograms.push_back(std::make_unique<ShaderProgram>(vert, frag));
    ShaderProgram* shader = shaderPrograms.back().get();
    camera.Attach(shader);
    return shader;
}

DrawableObject* Scene::AddObject(Model* model, ShaderProgram* shader, std::shared_ptr<Transformation> transformation)
{
    objects.push_back(std::make_unique<DrawableObject>(model, shader, transformation));
    return objects.back().get();
}

void Scene::AddLogin(glm::vec3 position, float scale)
{
    ShaderProgram* shader = AddShaderProgram("shaders/login.vert", "shaders/default.frag");
    Model* model = AddModel(login, LAYOUT_POS_NORMAL);

    auto t = std::make_shared<TransformationComposite>();
    t->Add(std::make_shared<Translation>(position));
    t->Add(std::make_shared<Scale>(glm::vec3(scale)));
    AddObject(model, shader, t);
}

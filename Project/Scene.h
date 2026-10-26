/*
* Adéla Grichová
* GRI0073
* ZPG 2026
*/

#pragma once
#include <vector>
#include <memory>

#include "DrawableObject.h"
#include "ShaderProgram.h"
#include "Model.h"
#include "Camera.h"

class Scene {
public:
    virtual ~Scene() = default;

    virtual void Update(float deltaTime) {}        // Update the scene (light, clock, ...)
    virtual glm::vec3 ClearColor() const;
    void Draw();

protected:
    Scene(Camera& camera) : camera(camera) {}

    ShaderProgram* AddShaderProgram(const char* vert, const char* frag);

    template <size_t N>
    Model* AddModel(const float(&data)[N], const VertexLayout& layout);

    DrawableObject* AddObject(Model* model, ShaderProgram* shader, std::shared_ptr<Transformation> transformation);
    void AddLogin(glm::vec3 position, float scale);

    Camera& camera;
    std::vector<std::unique_ptr<ShaderProgram>> shaderPrograms;
    std::vector<std::unique_ptr<Model>> models;
    std::vector<std::unique_ptr<DrawableObject>> objects;
};

template <size_t N>
Model* Scene::AddModel(const float(&data)[N], const VertexLayout& layout) {
    models.push_back(std::make_unique<Model>(data, N / layout.floatsPerVertex, layout));
    return models.back().get();
}
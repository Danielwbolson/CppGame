
#include "GameObject.h"
#include "Component.h"
#include "Collider.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include <algorithm>

GameObject::GameObject() {
    model = glm::mat4();
}

GameObject::~GameObject() {
    components.clear();
    components.empty();
}

GameObject::GameObject(const GameObject& rhs) {
    this->name = rhs.name;

    components.clear();
    components.empty();
    components = std::vector<Component*>();

    for (auto& element : rhs.components) {
        components.push_back(element->clone());
    }

    this->model = rhs.model;
}

GameObject& GameObject::operator=(const GameObject& rhs) {
    if (this == &rhs) return *this;
    this->name = rhs.name;

    components.clear();
    components.empty();
    components = std::vector<Component*>();
    for (auto& element : rhs.components) {
        components.push_back(element->clone());
    }

    this->model = rhs.model;

    return *this;
}

void GameObject::Update(const float& dt) {
    for (int i = 0; i < (int)components.size(); i++) {
        components[i]->Update(dt);
    }
}

void GameObject::Render(const glm::mat4& v, const glm::mat4& p) {
    model = glm::mat4();
    model = glm::translate(model, GetTransform()->position);

    MeshRenderer* m = (MeshRenderer*)GetComponent("meshRenderer");
    if (m) {
        m->Render(model, v, p);
    }
}

void GameObject::AddComponent(Component* c) {
    components.push_back(c);
    c->gameObject = this;
}

Component* GameObject::GetComponent(std::string componentType) {
    std::vector<Component*>::iterator it = std::find_if(components.begin(), components.end(), [&](const Component* c) {
        return c->ComponentType() == componentType;
    });

    if (it != components.end())
        return *it;
    else
        return nullptr;
}

Transform* GameObject::GetTransform() {
    return &(*(Transform*)GetComponent("transform"));
}


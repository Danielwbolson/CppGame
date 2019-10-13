
#include "GameObject.h"
#include "Component.h"
#include "Collider.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include <algorithm>

GameObject::GameObject() {}

GameObject::~GameObject() {
    components.clear();
    components.empty();

    for (std::vector<Component*>::iterator it = components.begin(); it != components.end(); it++) {
        delete (*it);
    }
}

GameObject::GameObject(const GameObject& rhs) {
    this->name = rhs.name;

    components.clear();
    components.empty();
    components = std::vector<Component*>();

    for (auto& element : rhs.components) {
        components.push_back(element->clone());
    }
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

    return *this;
}

void GameObject::SDLInput(const Uint8* k, const float& xRel, const float& yRel) {
    for (int i = 0; i < (int)components.size(); i++) {
        components[i]->SDLInput(k, xRel, yRel);
    }
}

void GameObject::Update(const float& dt) {
    for (int i = 0; i < (int)components.size(); i++) {
        components[i]->Update(dt);
    }
}

void GameObject::Render(const glm::mat4& v, const glm::mat4& p) {
    MeshRenderer* mr = (MeshRenderer*)GetComponent("meshRenderer");
    if (mr) {
        mr->Render(GetTransform()->model, v, p);
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


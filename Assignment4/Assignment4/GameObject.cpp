
#include "GameObject.h"
#include "Component.h"
#include "MeshRenderer.h"
#include <algorithm>

GameObject::GameObject() {
    model = glm::mat4();
}

GameObject::~GameObject() {
    components.clear();
    components.empty();
}

void GameObject::Update(const float& dt) {
    for (int i = 0; i < (int)components.size(); i++) {
        components[i]->Update(dt);
    }
}

void GameObject::Render(const glm::mat4& v, const glm::mat4& p) {
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

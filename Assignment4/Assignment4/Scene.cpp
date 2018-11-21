
#include "Scene.h"
#include <algorithm>

Scene::Scene() : window_width(640), window_height(480), background{ Vec3(0, 0, 0) } {}

Scene::~Scene() {
    gameObjects.clear();
    gameObjects.empty();

    instances.clear();
    instances.empty();

    lights.clear();
    lights.empty();
}

GameObject* Scene::FindGameObject(const std::string& name) {
    std::vector<GameObject*>::iterator it = std::find_if(gameObjects.begin(), gameObjects.end(), [&](const GameObject* c) {
        return c->name == name;
    });

    if (it != gameObjects.end())
        return *it;
    else
        return nullptr;
}

GameObject* Scene::FindInstance(const std::string& name) {
    std::vector<GameObject*>::iterator it = std::find_if(instances.begin(), instances.end(), [&](const GameObject* c) {
        return c->name == name;
    });

    if (it != instances.end())
        return *it;
    else
        return nullptr;
}

Camera* Scene::GetCamera() {
    return &(*(Camera*)FindInstance("player")->GetComponent("camera"));
}

void Scene::SDLInput(const Uint8* k, const float& xRel, const float& yRel) {
    for (int i = 0; i < instances.size(); i++) {
        instances[i]->SDLInput(k, xRel, yRel);
    }
}
void Scene::Update(const float dt) {
    for (int i = 0; i < instances.size(); i++) {
        instances[i]->Update(dt);
    }
}

bool Scene::CollisionChecks(const float& dt) const {
    for (int i = 0; i < instances.size(); i++) {
        Collider* c = (Collider*)instances[i]->GetComponent("collider");
        if (c && c->dynamic) {

            for (int j = 0; j < instances.size(); j++) {
                Collider* other = (Collider*)instances[j]->GetComponent("collider");
                if (other && i != j) {

                    if (c->CollisionDetect(*other, dt)) {
                        if (!other->isTrigger) {
                            c->gameObject->GetTransform()->velocity = glm::vec3(0, 0, 0);
                        }
                        c->colliding = true;
                        return true;
                    }
                    else {
                        other->colliding = false;
                    }

                }
            }
        }
    }
    return false;
}

void Scene::Render() {
    for (int i = 0; i < instances.size(); i++) {
        instances[i]->Render(GetCamera()->view, GetCamera()->proj);
    }
}

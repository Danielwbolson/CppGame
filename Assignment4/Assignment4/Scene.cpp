
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

void Scene::SetupCamera() {
    if (!cam) {
        cam = (Camera*)FindInstance("player")->GetComponent("camera");
        cam->gameObject = FindInstance("player");
        cam->ConnectTransform();
    }
}

void Scene::Update(const float dt) {
    for (int i = 0; i < instances.size(); i++) {
        instances[i]->Update(dt);
    }
}

bool Scene::CollisionChecks(const float& forward, const float& right) const {
    for (int i = 0; i < instances.size(); i++) {

        Collider* c = (Collider*)instances[i]->GetComponent("collider");
        if (c && c->dynamic) {
            for (int j = 0; j < instances.size(); j++) {

                Collider* other = (Collider*)instances[j]->GetComponent("collider");
                if (other && i != j) {
                    if (c->CollisionDetect(*other, forward, right))
                        return true;
                }
            }
        }
    }
    return false;
}

void Scene::Render() {
    for (int i = 0; i < instances.size(); i++) {
        instances[i]->Render(cam->view, cam->proj);
    }
}

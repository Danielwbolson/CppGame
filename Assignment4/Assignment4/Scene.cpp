
#include "Scene.h"
#include <algorithm>

Scene::Scene() : window_width(640), window_height(480), background{ Vec3(0, 0, 0) } {}

Scene::~Scene() {
    gameObjects.clear();
    gameObjects.empty();

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

void Scene::SetupCamera() {
    if (!cam)
        cam = (Camera*)FindGameObject("player")->GetComponent("camera");
}

void Scene::Update(const float dt) {
    for (int i = 0; i < gameObjects.size(); i++) {
        gameObjects[i]->Update(dt);
    }
}

void Scene::CollisionChecks() {

}

void Scene::Render() {
    for (int i = 0; i < gameObjects.size(); i++) {
        gameObjects[i]->Render(cam->view, cam->proj);
    }
}


#include "Scene.h"

Scene::Scene() : width(640), height(480),
camera{ Camera(Vec3(0, 0, 0), Vec3(0, 0, 1), Vec3(0, 1, 0), 45) },
background{ Vec3(0, 0, 0) } {

}

Scene::~Scene() {
    gameObjects.clear();
    gameObjects.empty();

    lights.clear();
    lights.empty();
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
        gameObjects[i]->Render();
    }
}


#ifndef SCENE_H_
#define SCENE_H_

#include "Camera.h"
#include "GameObject.h"
#include "Material.h"
#include "Light.h"
#include "Vec3.h"

#include <string>
#include <vector>

class Light;

class Scene {
public:
    int window_width;
    int window_height;

    Camera* cam;
    std::vector<GameObject*> gameObjects;
    std::vector<Light*> lights;
    Vec3 background;

    Scene();
    ~Scene();
    GameObject* FindGameObject(const std::string&);
    void SetupCamera();

    void Update(const float dt);
    void CollisionChecks();
    void Render();
};

#endif
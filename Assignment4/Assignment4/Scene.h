
#ifndef SCENE_H_
#define SCENE_H_

#include <SDL.h>

#include "Camera.h"
#include "GameObject.h"
#include "Material.h"
#include "Light.h"
#include "Vec3.h"
#include "Collider.h"

#include <string>
#include <vector>

class Light;

class Scene {
public:
    int window_width;
    int window_height;
    int cube_width = 2;

    std::vector<GameObject*> gameObjects;
    std::vector<GameObject*> instances;
    std::vector<Light*> lights;
    Vec3 background;

    Scene();
    ~Scene();
    GameObject* FindGameObject(const std::string&);
    GameObject* FindInstance(const std::string&);
    Camera* GetCamera();

    void SDLInput(const Uint8*);
    void Update(const float dt);
    bool CollisionChecks(const float&) const;
    void Render();
};

#endif
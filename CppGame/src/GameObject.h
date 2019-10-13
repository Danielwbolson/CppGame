
#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#define GLM_FORCE_RADIANS //ensure we are using radians
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "SDL.h"

#include <vector>

class Component;
class Collider;
class Transform;

class GameObject {

public:
    std::vector<Component*> components;
    std::string name;
    bool dead = false;

    GameObject();
    ~GameObject();
    GameObject(const GameObject&);
    GameObject& operator=(const GameObject&);

    void SDLInput(const Uint8*, const float&, const float&);
    void Update(const float&);
    void Render(const glm::mat4&, const glm::mat4&);

    void AddComponent(Component*);
    Component* GetComponent(const std::string);
    Transform* GetTransform();
};
#endif 


#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#define GLM_FORCE_RADIANS //ensure we are using radians
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <vector>

class Component;

class GameObject {

private:
    std::vector<Component*> components;

public:
    std::string name;
    glm::mat4 model;

    GameObject();
    ~GameObject();

    void Update(const float&);
    void Render(const glm::mat4&, const glm::mat4&);

    void AddComponent(Component*);
    Component* GetComponent(const std::string);
};
#endif 

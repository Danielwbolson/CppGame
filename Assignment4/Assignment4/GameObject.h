
#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include <vector>

class Component;

class GameObject {

private:
    std::vector<Component*> components;

public:

    GameObject();
    ~GameObject();

    void Update(const float&);
    void Render();

    void AddComponent(Component*);
    Component* GetComponent(const std::string);

};
#endif 

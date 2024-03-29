
#ifndef COMPONENT_H_
#define COMPONENT_H_

#include "SDL.h"

#include "Vec3.h"
#include "Vec2.h"
#include "Utility.h"
#include "GameObject.h"
#include <string>

#include <vector>

class GameObject;

class Component {

protected:
    std::string componentType;

public:
    GameObject* gameObject;
    std::string name;

    Component() {}
    ~Component() { delete gameObject; }

    // Returns camelCase name of components
    std::string ComponentType() const { return componentType; }

    virtual void SDLInput(const Uint8*, const float&, const float&) {}
    virtual void Update(const float&) {}
    virtual Component* clone() const = 0;

};
#endif 

#ifndef COLLIDER_H_
#define COLLIDER_H_

#include "Component.h"
#include "Transform.h"

class Collider : public Component {
public:
    Vec3 position;
    bool dynamic;
    bool colliding;
    GameObject* colliderObj;

    virtual bool CollisionDetect(const Collider&, const float&) const = 0;
    virtual void Update(const float&) = 0;
    virtual float MaxBoundsInDir(const Vec3&) const = 0;
};

#endif
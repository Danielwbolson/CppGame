
#ifndef COLLIDER_H_
#define COLLIDER_H_

#include "Component.h"

class Collider : public Component {

protected:
    Vec3 position;
    bool dynamic;

public:
    virtual void CollisionDetect(const Collider&) const = 0;
    virtual bool IsColliding(const Collider&) const = 0;
    virtual float MaxBounds() const = 0;
};

#endif

#ifndef SPHERE_COLLIDER_H_
#define SPHERE_COLLIDER_H_

#include "Collider.h"

class SphereCollider : public Collider {
    
private:
    float radius;

public:
    SphereCollider() {}
    SphereCollider(const Vec3&, const float&, const bool&);

    void CollisionDetect(const Collider&) const;
    bool IsColliding(const Collider&) const;
    float MaxBounds() const { return radius; }

    float Radius() const { return radius; }
    bool Dynamic() const { return dynamic; }
    Vec3 Position() const { return position; }

};

#endif

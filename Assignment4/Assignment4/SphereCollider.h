
#ifndef SPHERE_COLLIDER_H_
#define SPHERE_COLLIDER_H_

#include "Collider.h"

class SphereCollider : public Collider {
    
private:
    float radius;

public:
    SphereCollider() {}
    SphereCollider(const Vec3&, const float&, const bool&, const bool&);
    SphereCollider* clone() const;

    void Update(const float&);
    float MaxBoundsInDir(const Vec3&) const;
    bool CollisionDetect(const Collider&, const float&) const;
    float MaxBounds() const { return radius; }

    float Radius() const { return radius; }
    bool Dynamic() const { return dynamic; }
    Vec3 Position() const { return position; }

};

#endif


#ifndef BOX_COLLIDER_H_
#define BOX_COLLLIDER_H_

#include "Collider.h"

class BoxCollider : public Collider {

private:
    float width, height;

public:
    BoxCollider() {}
    BoxCollider(const Vec3&, const float&, const float&, const bool&);

    void CollisionDetect(const Collider&) const;
    bool IsColliding(const Collider&) const;
    float MaxBounds() const { return fmax(width, height); }

    float Width() const { return width; }
    float Height() const { return height; }
    bool Dynamic() const { return dynamic; }
    Vec3 Position() const { return position; }
};

#endif

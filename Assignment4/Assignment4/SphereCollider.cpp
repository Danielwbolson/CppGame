
#include "SphereCollider.h"

SphereCollider::SphereCollider(const Vec3& p, const float& r, const bool& d = false) {
    componentType = "sphereCollider";

    position = p;
    radius = r;
    dynamic = d;
}

void SphereCollider::CollisionDetect(const Collider&) const {

}

bool SphereCollider::IsColliding(const Collider&) const {
    return false;
}
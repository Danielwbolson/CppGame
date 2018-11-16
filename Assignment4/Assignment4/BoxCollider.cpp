
#include "BoxCollider.h"

BoxCollider::BoxCollider(const Vec3& p, const float& w, const float& h, const bool& d = false) {
    componentType = "boxCollider";

    position = p;
    width = w;
    height = h;
    dynamic = d;
}

void BoxCollider::CollisionDetect(const Collider&) const {

}

bool BoxCollider::IsColliding(const Collider&) const {
    return false;
}
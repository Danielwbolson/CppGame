
#include "SphereCollider.h"

SphereCollider::SphereCollider(const Vec3& p, const float& r, const bool& d = false) {
    componentType = "collider";

    position = p;
    radius = r;
    dynamic = d;
}

SphereCollider* SphereCollider::clone() const {
    return new SphereCollider(*this);
}

void SphereCollider::Update(const float& dt) {
    glm::vec3 p = gameObject->GetTransform()->position;
    position = Vec3(p.x, p.y, p.z);
}

float SphereCollider::MaxBoundsInDir(const Vec3& v) const {
    return radius;
}

bool SphereCollider::CollisionDetect(const Collider& c, const float& forward, const float& right) const {
    Transform* t = gameObject->GetTransform();
    glm::vec3 f = t->forward * forward;
    glm::vec3 r = t->right * right;

    Vec3 vec = c.position - (position + Vec3(f.x, f.y, f.z) + Vec3(r.x, r.y, r.z));
    float minDist = MaxBoundsInDir(vec.Normalize()) + c.MaxBoundsInDir(-vec.Normalize());
    float diff = minDist - vec.Length();

    return (diff >= 0.01f);
}
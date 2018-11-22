
#include "SphereCollider.h"

SphereCollider::SphereCollider(const Vec3& p, const float& r, const bool& d) {
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

bool SphereCollider::CollisionDetect(const Collider& c, const float& dt) const {
    Transform* t = gameObject->GetTransform();
    glm::vec3 v = t->velocity * dt;

    Vec3 vec = c.position - (position + 3 * Vec3(v.x, v.y, v.z));
    float minDist = MaxBoundsInDir(vec.Normalize()) + c.MaxBoundsInDir(-vec.Normalize());
    float diff = minDist - vec.Length();

    return (diff >= 0.01f);
}
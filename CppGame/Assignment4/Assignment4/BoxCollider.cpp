
#include "BoxCollider.h"

BoxCollider::BoxCollider(const Vec3& p, const float& w, const float& h, const bool& d) {
    componentType = "collider";

    position = p;
    width = w;
    height = h;
    dynamic = d;
}

BoxCollider::BoxCollider(const BoxCollider& rhs) {
    this->componentType = rhs.componentType;
    position = rhs.position;
    width = rhs.width;
    height = rhs.height;
    dynamic = rhs.dynamic;

    colliderObj = &(*rhs.gameObject);

    this->gameObject = &(*rhs.gameObject);
}

BoxCollider* BoxCollider::clone() const {
    return new BoxCollider(*this);
}

BoxCollider BoxCollider::operator=(const BoxCollider& rhs) {
    if (this == &rhs) return *this;

    this->componentType = rhs.componentType;
    position = rhs.position;
    width = rhs.width;
    height = rhs.height;
    dynamic = rhs.dynamic;
    this->gameObject = &(*rhs.gameObject);

    colliderObj = &(*rhs.gameObject);

    return *this;
}

void BoxCollider::Update(const float& dt) {
    glm::vec3 p = gameObject->GetTransform()->position;
    position = Vec3(p.x, p.y, p.z);
}

float BoxCollider::MaxBoundsInDir(const Vec3& v) const {
    float x = v.Normalize().x * width;
    float z = v.Normalize().z * width;
    return sqrt(x*x + z*z);
}

bool BoxCollider::CollisionDetect(const Collider& c, const float& dt) const {
    Transform* t = gameObject->GetTransform();
    glm::vec3 v = t->velocity * dt;

    Vec3 vec = c.position - (position + 3 * Vec3(v.x, v.y, v.z));
    float minDist = MaxBoundsInDir(position + 3 * Vec3(v.x, v.y, v.z)) + c.MaxBoundsInDir(-vec.Normalize());
    float diff = minDist - vec.Length();

    return (diff >= 0.01f);
}

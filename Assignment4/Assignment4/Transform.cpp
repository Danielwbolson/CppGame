
#include "Transform.h"

Transform::Transform() {
    componentType = "transform";

    position = glm::vec3(0, 0, 0);
    rotation = glm::vec3(0, 0, 0);
    scale = glm::vec3(1, 1, 1);

    forward = glm::vec3(0, 0, -1);
    right = glm::vec3(1, 0, 0);
    up = glm::vec3(0, 1, 0);

    model = glm::mat4();
}

Transform::~Transform() {
    delete gameObject;
}

Transform* Transform::clone() const {
    return new Transform(*this);
}

Transform::Transform(const Transform& t) {
    this->componentType = t.componentType;
    this->position = t.position;
    this->rotation = t.rotation;
    this->scale = t.scale;
    
    this->forward = t.forward;
    this->right = t.right;
    this->up = t.up;

    model = t.model;

    gameObject = t.gameObject;
}

Transform& Transform::operator=(const Transform& t) {
    if (this == &t) return *this;

    this->position = t.position;
    this->rotation = t.rotation;
    this->scale = t.scale;

    this->forward = t.forward;
    this->right = t.right;
    this->up = t.up;

    model = t.model;

    gameObject = t.gameObject;
    return *this;
}

void Transform::UpdateVelocity(const float& f, const float& r) {
    velocity = glm::vec3(forward.x, 0, forward.z) * f + glm::vec3(right.x, 0, right.z) * r;
}

void Transform::Update(const float& dt) {
    position += velocity * dt;

    model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::rotate(model, -rotation.x, glm::vec3(0, 1, 0));
    model = glm::rotate(model, rotation.y, right);

    forward = glm::vec3(model[2]);
    up = glm::vec3(model[1]);
    right = glm::vec3(model[0]);
}

#include "Camera.h"

Camera::Camera() {}

Camera::Camera(const Vec3& lookat, const Vec3& u, 
    const int& w, const int& h, const float& f, const float& np, const float& fp) {
    componentType = "camera";

    lookAt = glm::vec3(lookat.x, lookat.y, lookat.z);
    up = glm::vec3(u.x, u.y, u.z);
    fov = f;
    near_plane = np;
    far_plane = fp;
    aspect_ratio = w / (float)h;

    proj = glm::perspective(fov, aspect_ratio, near_plane, far_plane);
}

Camera* Camera::clone() const {
    return new Camera(*this);
}

void Camera::Update(const float& dt) {
    view = glm::lookAt(gameObject->GetTransform()->position, lookAt, up);
}

void Camera::UpdateView(const float& f, const float& r) {
    glm::vec3 temp_la = lookAt - gameObject->GetTransform()->position;

    glm::vec3 forward = glm::normalize(temp_la);
    glm::vec3 right = glm::normalize(glm::cross(forward, up));

    gameObject->GetTransform()->position += forward * f + right * r;
    lookAt = temp_la + gameObject->GetTransform()->position;
}

void Camera::ConnectTransform() {
    lookAt = gameObject->GetTransform()->position + lookAt;
    view = glm::lookAt(gameObject->GetTransform()->position, lookAt, up);
}

Camera Camera::operator=(const Camera& c) {
    if (this == &c) return *this;

    this->componentType = c.componentType;
    this->lookAt = c.lookAt;
    this->up = c.up;
    this->fov = c.fov;
    this->aspect_ratio = c.aspect_ratio;
    this->near_plane = c.near_plane;
    this->far_plane = c.far_plane;

    this->gameObject = c.gameObject;

    return *this;
}
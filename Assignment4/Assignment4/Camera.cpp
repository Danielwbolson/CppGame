
#include "Camera.h"

Camera::Camera() {}

Camera::Camera(const Vec3& pos, const Vec3& lookat, const Vec3& u, 
    const int& w, const int& h, const float& f, const float& np, const float& fp) {
    componentType = "camera";

    position = glm::vec3(pos.x, pos.y, pos.z);
    lookAt = glm::vec3(lookat.x, lookat.y, lookat.z);
    up = glm::vec3(u.x, u.y, u.z);
    fov = f;
    near_plane = np;
    far_plane = fp;
    aspect_ratio = w / (float)h;

    view = glm::lookAt(
        glm::vec3(position.x, position.y, position.z),   //Cam Position
        glm::vec3(-lookAt.x, -lookAt.y, lookAt.z),  //Look at point
        glm::vec3(up.x, up.y, up.z));

    proj = glm::perspective(fov, aspect_ratio, near_plane, far_plane);
}

void Camera::Update(const float& dt) {
    view = glm::lookAt(
        position,   //Cam Position
        lookAt,  //Look at point
        up); // Up vector
}

void Camera::UpdateView(const float& f, const float& r) {
    glm::vec3 temp_la = lookAt - position;

    glm::vec3 forward = glm::normalize(temp_la);
    glm::vec3 right = glm::normalize(glm::cross(forward, up));

    position += forward * f + right * r;
    lookAt = temp_la + position;
}

Camera Camera::operator=(const Camera& c) {
    if (this == &c) return *this;

    this->position = c.position;
    this->lookAt = c.lookAt;
    this->up = c.up;
    this->fov = c.fov;
    this->aspect_ratio = c.aspect_ratio;
    this->near_plane = c.near_plane;
    this->far_plane = c.far_plane;

    return *this;
}
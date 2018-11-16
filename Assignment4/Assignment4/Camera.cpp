
#include "Camera.h"

Camera::Camera() {}

Camera::Camera(Vec3 p, Vec3 d, Vec3 u, float a) {
    componentType = "camera";

    this->position = p;
    this->direction = d;
    this->up = u;
    this->vert_halfAngle = a / 180.0 * M_PI;
}

void Camera::Setup(int w, int h) {
    right = up.Cross(direction).Normalize();

    halfHeight = tan(vert_halfAngle);
    halfWidth = ((float)w / (float)h) * halfHeight;

    topLeft = position + direction + halfHeight * up - halfWidth * right;

    pixel_width = (2 * halfHeight) / (float)h;
}

Camera Camera::operator=(const Camera& c) {
    if (this == &c) return *this;
    this->position = c.position;
    this->direction = c.direction;
    this->up = c.up;
    this->vert_halfAngle = c.vert_halfAngle;
    this->right = c.right;
    this->halfHeight = c.halfHeight;
    this->halfWidth = c.halfWidth;
    this->topLeft = c.topLeft;
    this->pixel_width = c.pixel_width;
    return *this;
}

#include "Transform.h"

Transform::Transform() {
    componentType = "transform";

    position = Vec3(0, 0, 0);
    rotation = Vec3(0, 0, 0);
    scale = Vec3(1, 1, 1);
}
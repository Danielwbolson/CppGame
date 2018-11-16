
#ifndef CAMERA_H_
#define CAMERA_H_

#include "Vec3.h"
#include "Component.h"

#include <stdio.h>

class Camera : public Component {

private:

public:
    Camera();
    Camera(Vec3, Vec3, Vec3, float);
    void Setup(int w, int h);

    Camera operator=(const Camera&);

    Vec3 position;
    Vec3 direction;
    Vec3 up, right;

    Vec3 topLeft;

    float vert_halfAngle;
    float halfHeight, halfWidth;
    float pixel_width;
};

#endif
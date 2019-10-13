
#ifndef POINT_LIGHT_H_
#define POINT_LIGHT_H_

#include "Light.h"

class PointLight : public Light {

private:
    Vec3 position;

public:
    PointLight();
    PointLight(Vec3, Vec3);

};
#endif

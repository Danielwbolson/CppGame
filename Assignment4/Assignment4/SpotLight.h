
#ifndef SPOT_LIGHT_H_
#define SPOT_LIGHT_H_

#include "Light.h"

class SpotLight : public Light {

private:
    Vec3 position, direction;
    float theta, phi;

public:
    SpotLight();
    SpotLight(Vec3, Vec3, Vec3, float, float);

};
#endif

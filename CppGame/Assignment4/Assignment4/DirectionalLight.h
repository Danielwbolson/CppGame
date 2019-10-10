
#ifndef DIRECTIONAL_LIGHT_H_
#define DIRECTIONAL_LIGHT_H_

#include "Light.h"

class DirectionalLight : public Light {

private:
    Vec3 direction;

public:
    DirectionalLight();
    DirectionalLight(Vec3, Vec3);

};
#endif

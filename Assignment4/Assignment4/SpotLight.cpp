
#include "SpotLight.h"

SpotLight::SpotLight() {

}

SpotLight::SpotLight(Vec3 c, Vec3 p, Vec3 d, float theta, float phi) {
    color = c;
    position = p;
    direction = d;
    this->theta = theta;
    this->phi = phi;
}
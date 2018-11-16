
#include "DirectionalLight.h"

DirectionalLight::DirectionalLight() {

}

DirectionalLight::DirectionalLight(Vec3 c, Vec3 d) {
    color = c;
    direction = d;
}
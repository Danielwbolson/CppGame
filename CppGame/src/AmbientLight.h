
#ifndef AMBIENT_LIGHT_H_
#define AMBIENT_LIGHT_H_

#include "Light.h"
#include "Vec3.h"

class AmbientLight : public Light {

private:

public:
    AmbientLight();
    AmbientLight(Vec3 c);

};
#endif

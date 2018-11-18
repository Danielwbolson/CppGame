
#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include "Vec3.h"
#include "Component.h"

class Transform : public Component {

private:

public:
    Transform();

    Vec3 position;
    Vec3 rotation;
    Vec3 scale;

};
#endif


#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "glad/glad.h"  //Include order can matter here

#include "Vec3.h"
#include "Utility.h"

class Material {

private:
    Vec3 color;
    Vec3 c_ambient, c_diffuse, c_specular;

public:

    Material();
    Material(const Vec3&, const Vec3&, const Vec3&, const Vec3&);

    Vec3 Color() const { return color; }
    Vec3 Ambient() const { return c_ambient; }
    Vec3 Diffuse() const { return c_diffuse; }
    Vec3 Specular() const { return c_specular; }

    Material operator=(const Material&);
};

#endif
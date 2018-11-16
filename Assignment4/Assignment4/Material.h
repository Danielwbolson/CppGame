
#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "glad/glad.h"  //Include order can matter here

#include "Vec3.h"
#include "Utility.h"

class Material {

private:
    Vec3 c_ambient, c_diffuse, c_specular, c_transmissive;
    float exponent;
    float index_of_refraction;
    GLuint shaderProgram;

public:
    Material();
    Material(Vec3, Vec3, Vec3, float, Vec3, float);

    GLuint Shader() const { return shaderProgram; }

    Vec3 Ambient() const { return c_ambient; }
    Vec3 Diffuse() const { return c_diffuse; }
    Vec3 Specular() const { return c_specular; }
    Vec3 Transmissive() const { return c_transmissive; }
    float Exponent() const { return exponent; }
    float IofR() const { return index_of_refraction; }

    Material operator=(const Material&);
};

#endif
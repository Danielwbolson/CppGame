
#include "Material.h"

Material::Material() {}

    Material::Material(const Vec3& a, const Vec3& d, const Vec3& s) {
    this->c_ambient = a;
    this->c_diffuse = d;
    this->c_specular = s;
}

Material Material::operator=(const Material& m) {
    if (this == &m) return *this;

    this->c_ambient = m.Ambient();
    this->c_diffuse = m.Diffuse();
    this->c_specular = m.Specular();
}
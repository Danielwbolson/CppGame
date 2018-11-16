
#include "Mesh.h"

Mesh::Mesh() {

}

Mesh::Mesh(std::vector<Vec3> p, std::vector<Vec3> n, std::vector<Vec2> uv, std::vector<unsigned short> ind) {
    pos = p;
    normals = n;
    uvs = uv;
    indices = ind;
}

#ifndef MESH_H_
#define MESH_H_

#include <vector>
#include "Vec2.h"
#include "Vec3.h"

class Mesh {

private:
    int numVertices;
    int numNormals;
    int numIndices;

    std::vector<Vec3> pos;
    std::vector<Vec3> normals;
    std::vector<Vec2> uvs;
    std::vector<unsigned short> indices;

public:
    Mesh();
    Mesh(std::vector<Vec3>, std::vector<Vec3>, std::vector<Vec2>, std::vector<unsigned short>);

    std::string ComponentType() const { return "mesh"; }

    int NumVerts() const { return numVertices; }
    int NumNorms() const { return numNormals; }
    int NumIndices() const { return numIndices; }

    std::vector<Vec3>* Pos() { return &pos; }
    std::vector<Vec3>* Normals() { return &normals; }
    std::vector<Vec2>* UVs() { return &uvs; }
    std::vector<unsigned short>* Indices() { return &indices; }

};
#endif

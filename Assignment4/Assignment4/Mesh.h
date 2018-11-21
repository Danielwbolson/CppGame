
#ifndef MESH_H_
#define MESH_H_

#include <vector>
#include "Vec2.h"
#include "Vec3.h"

class Mesh {

private:
    int numPositions;
    int numNormals;
    int numIndices;

public:
    std::string name;

    std::vector<Vec3> pos;
    std::vector<Vec3> normals;
    std::vector<Vec2> uvs;
    std::vector<unsigned short> indices;

    Mesh();
    Mesh(std::vector<Vec3>, std::vector<Vec3>, std::vector<Vec2>, std::vector<unsigned short>);

    std::string ComponentType() const { return "mesh"; }

    int NumPositions() const { return numPositions; }
    int NumNorms() const { return numNormals; }
    int NumIndices() const { return numIndices; }

    std::vector<Vec3>* Pos() { return &pos; }
    std::vector<Vec3>* Normals() { return &normals; }
    std::vector<Vec2>* UVs() { return &uvs; }
    std::vector<unsigned short>* Indices() { return &indices; }

    void SetPositions(const std::vector<Vec3>& p) { pos = p; numPositions = pos.size(); }
    void SetNormals(const std::vector<Vec3>& n) { normals = n; numNormals = normals.size(); }
    void SetUvs(const std::vector<Vec2>& u) { uvs = u; }
    void SetIndices(const std::vector<unsigned short>& ind) { indices = ind; numIndices = indices.size(); }

};
#endif

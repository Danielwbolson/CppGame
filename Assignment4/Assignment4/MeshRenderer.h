
#ifndef MESH_RENDERER_H_
#define MESH_RENDERER_H_

#include "glad/glad.h"  //Include order can matter here

#include "Component.h"
#include "Mesh.h"
#include "Material.h"

class MeshRenderer : public Component {

private:

    // 0 : position, 1 : normals, 2 : uvs, 3 : indices
    GLuint vbo[4];
    GLuint vao;

    Mesh mesh;
    Material material;

public:
    MeshRenderer() {}
    MeshRenderer(const Mesh&, const Material&);

    void Render();

    GLuint VAO() { return vao; }
    GLuint Positions() { return vbo[0]; }
    GLuint Normals() { return vbo[1]; }
    GLuint UVs() { return vbo[2]; }
    GLuint Indices() { return vbo[3]; }

};
#endif

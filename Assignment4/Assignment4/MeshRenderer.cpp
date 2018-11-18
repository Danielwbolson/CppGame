
#include "MeshRenderer.h"

MeshRenderer::MeshRenderer(const Mesh& m, const Material& mat) {
    componentType = "meshRenderer";

    mesh = m;
    material = mat;

    glGenVertexArrays(1, &vao); //Create a VAO
    glBindVertexArray(vao); //Bind the above created VAO to the current context

    // Position
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    GLint posAttrib = glGetAttribLocation(material.Shader(), "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
    //Attribute, vals/attrib., type, isNormalized, stride, offset

    glGenBuffers(1, &vbo[0]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, 3 * mesh.NumPositions() * sizeof(float), &mesh.Pos()[0], GL_STREAM_DRAW);

    // Normals
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    GLint normAttrib = glGetAttribLocation(material.Shader(), "inNormal");
    glEnableVertexAttribArray(normAttrib);
    glVertexAttribPointer(normAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glGenBuffers(1, &vbo[1]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, 3 * mesh.NumNorms() * sizeof(float), &mesh.Normals()[0], GL_STREAM_DRAW);

    // UVS
    glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
    GLint uvAttrib = glGetAttribLocation(material.Shader(), "inUVs");
    glEnableVertexAttribArray(uvAttrib);
    glVertexAttribPointer(uvAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glGenBuffers(1, &vbo[2]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
    glBufferData(GL_ARRAY_BUFFER, 2 * mesh.NumPositions() * sizeof(float), &mesh.UVs()[0], GL_STATIC_DRAW);

    // Indices
    glGenBuffers(1, &vbo[3]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[3]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.NumIndices() * sizeof(unsigned short), &mesh.Indices()[0], GL_STATIC_DRAW);
}

void MeshRenderer::Render(const glm::mat4& m, const glm::mat4& v, const glm::mat4& p) {

    GLint uniModel = glGetUniformLocation(material.shaderProgram, "model");
    glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(m));
    GLint uniView = glGetUniformLocation(material.shaderProgram, "view");
    glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(v));
    GLint uniProj = glGetUniformLocation(material.shaderProgram, "proj");
    glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(p));

    // Indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[3]);

    // User our shader and draw our program
    glUseProgram(material.Shader());
    glBindVertexArray(vao);  //Bind the VAO for the shaders we are using
    glDrawElements(GL_TRIANGLES, mesh.NumIndices() * sizeof(unsigned short), GL_UNSIGNED_SHORT, 0); //Number of vertices
}
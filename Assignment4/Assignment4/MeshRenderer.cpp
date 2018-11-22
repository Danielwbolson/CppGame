
#include "MeshRenderer.h"

MeshRenderer::MeshRenderer(const Mesh& m, const Material& mat) {
    componentType = "meshRenderer";

    mesh = m;
    material = mat;

    /* * * SETUP SHADER * * */

    // Vert and frag shaders, compiled from file
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const std::string vertString = util::fileToString("Phong.vert");
    const GLchar* vertexSource = vertString.c_str();
    util::loadShader(vertexShader, vertexSource);

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const std::string fragString = util::fileToString("Phong.frag");
    const GLchar* fragmentSource = fragString.c_str();
    util::loadShader(fragmentShader, fragmentSource);

    //Join the vertex and fragment shaders together into one program
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glBindFragDataLocation(shaderProgram, 0, "outColor"); // set output
    glLinkProgram(shaderProgram); //run the linker

    /* * * FINISHED SHADER SETUP * * */

    glGenVertexArrays(1, &vao); //Create a VAO
    glBindVertexArray(vao); //Bind the above created VAO to the current context

    // Position
    glGenBuffers(1, &vbo[0]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, 3 * mesh.NumPositions() * sizeof(float), &(mesh.pos[0]), GL_STREAM_DRAW);

    GLuint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
    //Attribute, vals/attrib., type, isNormalized, stride, offset

    // Normals
    glGenBuffers(1, &vbo[1]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, 3 * mesh.NumNorms() * sizeof(float), &(mesh.normals[0]), GL_STREAM_DRAW);

    GLuint normAttrib = glGetAttribLocation(shaderProgram, "inNormal");
    glEnableVertexAttribArray(normAttrib);
    glVertexAttribPointer(normAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // UVS
    glGenBuffers(1, &vbo[2]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
    glBufferData(GL_ARRAY_BUFFER, 2 * mesh.NumPositions() * sizeof(float), &(mesh.uvs[0]), GL_STATIC_DRAW);

    GLuint uvAttrib = glGetAttribLocation(shaderProgram, "inUVs");
    glEnableVertexAttribArray(uvAttrib);
    glVertexAttribPointer(uvAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);

    // Indices
    glGenBuffers(1, &vbo[3]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[3]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.NumIndices() * sizeof(GL_UNSIGNED_INT), &(mesh.indices[0]), GL_STATIC_DRAW);
}

MeshRenderer* MeshRenderer::clone() const {
    return new MeshRenderer(*this);
}

void MeshRenderer::Render(const glm::mat4& m, const glm::mat4& v, const glm::mat4& p) {

    glBindVertexArray(vao);  //Bind the VAO for the shaders we are using
    glUseProgram(shaderProgram);

    GLint uniColor = glGetUniformLocation(shaderProgram, "inColor");
    glUniform3f(uniColor, material.Color().x, material.Color().y, material.Color().z);
    GLint uniModel = glGetUniformLocation(shaderProgram, "model");
    glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(m));
    GLint uniView = glGetUniformLocation(shaderProgram, "view");
    glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(v));
    GLint uniProj = glGetUniformLocation(shaderProgram, "proj");
    glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(p));

    // Indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[3]);

    // User our shader and draw our program
    glDrawElements(GL_TRIANGLES, mesh.NumIndices() * sizeof(GL_UNSIGNED_INT), GL_UNSIGNED_INT, 0); //Number of vertices
}
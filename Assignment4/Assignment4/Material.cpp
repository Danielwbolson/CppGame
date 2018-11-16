
#include "Material.h"

Material::Material() {}

Material::Material(Vec3 a, Vec3 d, Vec3 s, float e, Vec3 t, float i) {
    this->c_ambient = a;
    this->c_diffuse = d;
    this->c_specular = s;
    this->exponent = e;
    this->c_transmissive = t;
    this->index_of_refraction = i;

    /* * * SETUP SHADER * * */

    // Vert and frag shaders, compiled from file
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const std::string vertString = util::fileToString("Phong.vert");
    const GLchar* vertexSource = vertString.c_str();
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    util::loadShader(vertexShader, vertexSource);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const std::string fragString = util::fileToString("Phong.frag");
    const GLchar* fragmentSource = fragString.c_str();
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    util::loadShader(fragmentShader, fragmentSource);

    //Join the vertex and fragment shaders together into one program
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glBindFragDataLocation(shaderProgram, 0, "outColor"); // set output
    glLinkProgram(shaderProgram); //run the linker

    /* * * FINISHED SHADER SETUP * * */
}

Material Material::operator=(const Material& m) {
    if (this == &m) return *this;

    this->c_ambient = m.Ambient();
    this->c_diffuse = m.Diffuse();
    this->c_specular = m.Specular();
    this->exponent = m.Exponent();
    this->c_transmissive = m.Transmissive();
    this->index_of_refraction = m.IofR();
}
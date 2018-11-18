
#include "Material.h"

Material::Material() {}

    Material::Material(const Vec3& a, const Vec3& d, const Vec3& s) {
    this->c_ambient = a;
    this->c_diffuse = d;
    this->c_specular = s;

    /* * * SETUP SHADER * * */

    // Vert and frag shaders, compiled from file
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const std::string vertString = util::fileToString("./Phong.vert");
    const GLchar* vertexSource = vertString.c_str();
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    util::loadShader(vertexShader, vertexSource);

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const std::string fragString = util::fileToString("./Phong.frag");
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

Material::~Material() {
    if (glIsProgram(shaderProgram)) {
        glDeleteProgram(shaderProgram);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }
}

Material Material::operator=(const Material& m) {
    if (this == &m) return *this;

    this->c_ambient = m.Ambient();
    this->c_diffuse = m.Diffuse();
    this->c_specular = m.Specular();

    this->fragmentShader = m.fragmentShader;
    this->vertexShader = m.vertexShader;
    this->shaderProgram = m.shaderProgram;
}
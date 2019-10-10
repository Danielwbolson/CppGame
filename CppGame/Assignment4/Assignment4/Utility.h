
#ifndef UTILITY_H_
#define UTILITY_H_

#include "glad/glad.h"  //Include order can matter here

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

namespace util {

    static void loadShader(GLuint shaderID, const GLchar* shaderSource) {
        glShaderSource(shaderID, 1, &shaderSource, NULL);
        glCompileShader(shaderID);

        //Let's double check the shader compiled 
        GLint status;
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &status); //Check for errors
        if (!status) {
            char buffer[512]; glGetShaderInfoLog(shaderID, 512, NULL, buffer);
            printf("Shader Compile Failed. Info:\n\n%s\n", buffer);
        }
    }

    static const std::string fileToString(std::string filename) {
        std::ifstream file(filename);
        std::stringstream buf;
        buf << file.rdbuf();

        return buf.str();
    }
}

#endif
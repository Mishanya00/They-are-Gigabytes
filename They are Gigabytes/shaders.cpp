#include "shaders.hpp"
#include "mishanya_utils.hpp"

#include <iostream>


std::string pVSFileName = "shader.vs";
std::string pFSFileName = "shader.fs";

GLint gWorld;
GLint gProjectionLocation;
GLint gViewLocation;
GLint gSamplerLocation;


static void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType)
{
    GLuint ShaderObj = glCreateShader(ShaderType);

    if (ShaderObj == 0) {
        std::cerr << "Error creating shader type " << ShaderType << '\n';
        exit(1);
    }

    const GLchar* p[1];
    p[0] = pShaderText;

    GLint Lengths[1];
    Lengths[0] = (GLint)strlen(pShaderText);

    glShaderSource(ShaderObj, 1, p, Lengths);

    glCompileShader(ShaderObj);

    GLint success;
    glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);

    if (!success) {
        GLchar InfoLog[1024];
        glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
        std::cerr << "Error compiling shader type '" << ShaderType << "' " << InfoLog << '\n';
        exit(1);
    }

    glAttachShader(ShaderProgram, ShaderObj);
}

void CompileShaders()
{
    GLuint ShaderProgram = glCreateProgram();

    if (ShaderProgram == 0) {
        std::cerr << "Error creating shader program\n";
        exit(1);
    }

    std::string vs, fs;

    if (!mishanya::ReadFile(pVSFileName, vs)) {
        exit(1);
    };

    AddShader(ShaderProgram, vs.c_str(), GL_VERTEX_SHADER);

    if (!mishanya::ReadFile(pFSFileName, fs)) {
        exit(1);
    };

    AddShader(ShaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

    GLint Success = 0;
    GLchar ErrorLog[1024] = { 0 };

    glLinkProgram(ShaderProgram);

    glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);
    if (Success == 0) {
        glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
        std::cerr << "Error linking shader program: '" << ErrorLog << "'\n";
        exit(1);
    }

    gWorld = glGetUniformLocation(ShaderProgram, "World");
    if (gWorld == -1) {
        std::cerr << "Error getting uniform location of 'gRotation'\n";
        exit(1);
    }
    gProjectionLocation = glGetUniformLocation(ShaderProgram, "Projection");
    if (gProjectionLocation == -1) {
        std::cerr << "Error getting uniform location of 'gRotation'\n";
        exit(1);
    }
    gViewLocation = glGetUniformLocation(ShaderProgram, "View");
    if (gViewLocation == -1) {
        std::cerr << "Error getting uniform location of 'gViewLocation'\n";
        exit(1);
    }
    gSamplerLocation = glGetUniformLocation(ShaderProgram, "gSampler");
    if (gViewLocation == -1) {
        std::cerr << "Error getting uniform location of 'gSamplerLocation'\n";
        exit(1);
    }

    glValidateProgram(ShaderProgram);
    glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &Success);
    if (!Success) {
        glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
        std::cerr << "Invalid shader program: '" << ErrorLog << "'\n";
        exit(1);
    }

    glUseProgram(ShaderProgram);
}
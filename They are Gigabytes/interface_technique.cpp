#include "interface_technique.hpp"

InterfaceTechnique::InterfaceTechnique()
{
}

bool InterfaceTechnique::Init()
{
    if (!Technique::Init()) {
        return false;
    }

    if (!AddShader(GL_VERTEX_SHADER, "interface.vs")) {
        return false;
    }

    if (!AddShader(GL_FRAGMENT_SHADER, "interface.fs")) {
        return false;
    }

    if (!Finalize()) {
        return false;
    }

    colorLoc = GetUniformLocation("BtnColor");

    if ( colorLoc == 0xFFFFFFFF )
    {
        return false;
    }

    return true;
}

void InterfaceTechnique::SetColorUniform(GLfloat r, GLfloat g, GLfloat b, GLfloat alpha)
{
    //glUniform4fv(colorLoc, 1, GL_TRUE, (const GLfloat*)RGB);
    glUniform4f(colorLoc, r, g, b, alpha);
}
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

    perspectiveLoc = GetUniformLocation("Projection");
    viewLoc = GetUniformLocation("View");
    samplerLoc = GetUniformLocation("gSampler");

    if ( samplerLoc == 0xFFFFFFFF )
    {
        return false;
    }

    return true;
}

void InterfaceTechnique::SetViewUniform(const Matrix4f& gView)
{
    glUniformMatrix4fv(viewLoc, 1, GL_TRUE, (const GLfloat*)gView.m);
}

void InterfaceTechnique::SetProjectionUniform(const Matrix4f& gPerspective)
{
    glUniformMatrix4fv(perspectiveLoc, 1, GL_TRUE, (const GLfloat*)gPerspective.m);
}


void InterfaceTechnique::SetTextureUnit(unsigned int TextureUnit)
{
    glUniform1i(samplerLoc, TextureUnit);
}
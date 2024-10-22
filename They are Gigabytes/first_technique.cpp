#include "first_technique.hpp"


FirstTechnique::FirstTechnique()
{
}

bool FirstTechnique::Init()
{
    if (!Technique::Init()) {
        return false;
    }

    if (!AddShader(GL_VERTEX_SHADER, "shader.vs")) {
        return false;
    }

    if (!AddShader(GL_FRAGMENT_SHADER, "shader.fs")) {
        return false;
    }

    if (!Finalize()) {
        return false;
    }

    perspectiveLoc = GetUniformLocation("Projection");
    viewLoc = GetUniformLocation("View");
    worldLoc = GetUniformLocation("World");
    samplerLoc = GetUniformLocation("gSampler");

    return true;
}

void FirstTechnique::SetWorldUniform(const Matrix4f& gWorld)
{
    glUniformMatrix4fv(worldLoc, 1, GL_TRUE, (const GLfloat*)gWorld.m);
}
void FirstTechnique::SetViewUniform(const Matrix4f& gView)
{
    glUniformMatrix4fv(viewLoc, 1, GL_TRUE, (const GLfloat*)gView.m);
}

void FirstTechnique::SetProjectionUniform(const Matrix4f& gPerspective)
{
    glUniformMatrix4fv(perspectiveLoc, 1, GL_TRUE, (const GLfloat*)gPerspective.m);
}

void FirstTechnique::SetTextureUnit(unsigned int TextureUnit)
{
    glUniform1i(samplerLoc, TextureUnit);
}
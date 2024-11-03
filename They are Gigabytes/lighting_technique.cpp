#include "lighting_technique.hpp"


LightingTechnique::LightingTechnique()
{
}

bool LightingTechnique::Init()
{
    if (!Technique::Init()) {
        return false;
    }

    if (!AddShader(GL_VERTEX_SHADER, "lighting.vs")) {
        return false;
    }

    if (!AddShader(GL_FRAGMENT_SHADER, "lighting.fs")) {
        return false;
    }

    if (!Finalize()) {
        return false;
    }

    perspectiveLoc = GetUniformLocation("Projection");
    viewLoc = GetUniformLocation("View");
    worldLoc = GetUniformLocation("World");
    samplerLoc = GetUniformLocation("gSampler");
    lightColorLoc = GetUniformLocation("gLight.Color");
    lightAmbientIntensityLoc = GetUniformLocation("gLight.AmbientIntensity");
    materialAmbientColorLoc = GetUniformLocation("gMaterial.AmbientColor");

    if (lightAmbientIntensityLoc == -1 ||
        worldLoc == -1 ||
        viewLoc == -1 ||
        perspectiveLoc == -1 ||
        samplerLoc == -1 ||
        lightColorLoc == -1 ||
        materialAmbientColorLoc == 0xFFF)

    {
        return false;
    }

    return true;
}

void LightingTechnique::SetWorldUniform(const Matrix4f& gWorld)
{
    glUniformMatrix4fv(worldLoc, 1, GL_TRUE, (const GLfloat*)gWorld.m);
}
void LightingTechnique::SetViewUniform(const Matrix4f& gView)
{
    glUniformMatrix4fv(viewLoc, 1, GL_TRUE, (const GLfloat*)gView.m);
}

void LightingTechnique::SetProjectionUniform(const Matrix4f& gPerspective)
{
    glUniformMatrix4fv(perspectiveLoc, 1, GL_TRUE, (const GLfloat*)gPerspective.m);
}


void LightingTechnique::SetTextureUnit(unsigned int TextureUnit)
{
    glUniform1i(samplerLoc, TextureUnit);
}


void LightingTechnique::SetLight(const BaseLight& Light)
{
    glUniform3f(lightColorLoc, Light.Color.x, Light.Color.y, Light.Color.z);
    glUniform1f(lightAmbientIntensityLoc, Light.AmbientIntensity);
}


void LightingTechnique::SetMaterial(const Material& material)
{
    glUniform3f(materialAmbientColorLoc, material.AmbientColor.r, material.AmbientColor.g, material.AmbientColor.b);
}
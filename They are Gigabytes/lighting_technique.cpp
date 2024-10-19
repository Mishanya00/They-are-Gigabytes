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

    WVPLoc = GetUniformLocation("gWVP");
    samplerLoc = GetUniformLocation("gSampler");
    lightColorLoc = GetUniformLocation("gLight.Color");
    lightAmbientIntensityLoc = GetUniformLocation("gLight.AmbientIntensity");
    materialAmbientColorLoc = GetUniformLocation("gMaterial.AmbientColor");

    if (lightAmbientIntensityLoc == 0xFFFFFFFF ||
        WVPLoc == 0xFFFFFFFF ||
        samplerLoc == 0xFFFFFFFF ||
        lightColorLoc == 0xFFFFFFFF ||
        materialAmbientColorLoc == 0xFFF)

    {
        return false;
    }

    return true;
}

void LightingTechnique::SetWVP(const Matrix4f& WVP)
{
    glUniformMatrix4fv(WVPLoc, 1, GL_TRUE, (const GLfloat*)WVP.m);
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
    glUniform3f(materialAmbientColorLoc, material.ambient_color.r, material.ambient_color.g, material.ambient_color.b);
}
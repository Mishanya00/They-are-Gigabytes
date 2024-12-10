#include "lighting_technique.hpp"


void DirectionalLight::CalcLocalDirection(const Matrix4f& World)
{
    Matrix3f World3f(World);  // Initialize using the top left corner of matrix

    // Inverse local-to-world transformation using transpose
    // (assuming uniform scaling)
    Matrix3f WorldToLocal = World3f.Transpose();

    LocalDirection = WorldToLocal * WorldDirection;

    LocalDirection = LocalDirection.Normalize();
}

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

    samplerLoc = GetUniformLocation("gSampler");
    materialLoc.AmbientColor = GetUniformLocation("gMaterial.AmbientColor");
    materialLoc.DiffuseColor = GetUniformLocation("gMaterial.DiffuseColor");
    lightLoc.Color = GetUniformLocation("gDirectionalLight.Color");
    lightLoc.AmbientIntensity = GetUniformLocation("gDirectionalLight.AmbientIntensity");
    lightLoc.Direction = GetUniformLocation("gDirectionalLight.Direction");
    lightLoc.DiffuseIntensity = GetUniformLocation("gDirectionalLight.DiffuseIntensity");

    if (
        samplerLoc == 0xFFFFFFFF ||
        materialLoc.AmbientColor == 0xFFFFFFFF ||
        materialLoc.DiffuseColor == 0xFFFFFFFF ||
        lightLoc.Color == 0xFFFFFFFF ||
        lightLoc.DiffuseIntensity == 0xFFFFFFFF ||
        lightLoc.Direction == 0xFFFFFFFF ||
        lightLoc.AmbientIntensity == 0xFFFFFFFF)
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


void LightingTechnique::SetLight(const DirectionalLight& Light)
{
    Vector3f local_direction = Light.GetLocalDirection();

    glUniform3f(lightLoc.Color, Light.Color.x, Light.Color.y, Light.Color.z);
    glUniform3f(lightLoc.Direction, local_direction.x, local_direction.y, local_direction.z);
    glUniform1f(lightLoc.AmbientIntensity, Light.AmbientIntensity);
    glUniform1f(lightLoc.DiffuseIntensity, Light.DiffuseIntensity);
}


void LightingTechnique::SetMaterial(const Material& material)
{
    glUniform3f(materialLoc.AmbientColor, material.AmbientColor.r, material.AmbientColor.g, material.AmbientColor.b);
    glUniform3f(materialLoc.DiffuseColor, material.DiffuseColor.r, material.DiffuseColor.g, material.DiffuseColor.b);
}
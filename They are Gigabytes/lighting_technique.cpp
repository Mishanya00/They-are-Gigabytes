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
    CameraLocalPosLoc = GetUniformLocation("gCameraLocalPos");
    renderModeLoc = GetUniformLocation("gRenderMode");
    effectFlagsLoc = GetUniformLocation("gEffectFlags");

    if (
        samplerLoc == -1 ||
        materialLoc.AmbientColor == -1 ||
        materialLoc.DiffuseColor == -1 ||
        lightLoc.Color == -1 ||
        lightLoc.DiffuseIntensity == -1 ||
        lightLoc.Direction == -1 ||
        lightLoc.AmbientIntensity == -1 ||
        CameraLocalPosLoc == -1 ||
        renderModeLoc == -1 ||
        effectFlagsLoc == -1 )
    {
        return false;
    }
    return true;
}

void LightingTechnique::SetEffectStatus(LightShaderEffect effect, int status)
{
    if (status) {
        effect_flags_ |= effect;
    }
    else {
        effect_flags_ = effect_flags_ & (~effect);
    }
    glUniform1i(effectFlagsLoc, effect_flags_);
}

void LightingTechnique::InverseEffectStatus(LightShaderEffect effect) {
    effect_flags_ ^= effect;
    glUniform1i(effectFlagsLoc, effect_flags_);
}

void LightingTechnique::SetRenderMode(LightingShaderRenderMode renderMode) {
    glUniform1i(renderModeLoc, renderMode);
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

void LightingTechnique::SetCameraLocalPos(const Vector3f& LocalPosition)
{
    glUniform3fv(CameraLocalPosLoc, 1, (const GLfloat*)LocalPosition);
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
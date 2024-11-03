#pragma once

#include "technique.hpp"
#include "math_3d.h"
#include "material.hpp"


class BaseLight
{
public:
    Vector3f Color;
    float AmbientIntensity;

    BaseLight()
    {
        Color = Vector3f(1.0f, 1.0f, 1.0f);
        AmbientIntensity = 0.5f;
    }
};


class LightingTechnique : public Technique
{
public:

    LightingTechnique();

    virtual bool Init();

    void SetWorldUniform(const Matrix4f& gWorld);
    void SetViewUniform(const Matrix4f& gView);
    void SetProjectionUniform(const Matrix4f& gPerspective);
    void SetTextureUnit(unsigned int TextureUnit);
    void SetLight(const BaseLight& Light);
    void SetMaterial(const Material& material);

private:

    GLuint worldLoc, viewLoc, perspectiveLoc;
    GLuint samplerLoc;
    GLuint lightColorLoc;
    GLuint lightAmbientIntensityLoc;
    GLuint materialAmbientColorLoc;
};
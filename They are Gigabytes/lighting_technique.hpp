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
        AmbientIntensity = 0.0f;
    }
};


class LightingTechnique : public Technique
{
public:

    LightingTechnique();

    virtual bool Init();

    void SetWVP(const Matrix4f& WVP);
    void SetTextureUnit(unsigned int TextureUnit);
    void SetLight(const BaseLight& Light);
    void SetMaterial(const Material& material);

private:

    GLuint WVPLoc;
    GLuint samplerLoc;
    GLuint lightColorLoc;
    GLuint lightAmbientIntensityLoc;
    GLuint materialAmbientColorLoc;
};
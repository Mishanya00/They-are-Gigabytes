#pragma once

#include "technique.hpp"
#include "math_3d.h"
#include "material.hpp"


enum LightingShaderRenderMode {
    lsrmClassic = 0,
    lsrmSelected = 1,
    lsrmPartial = 2,
    lsrmVignette = 3,
};

enum LightShaderEffect {
    lseNoise = 1,
    lseVignette = 2,
    lseColorGrading = 4,
};

class BaseLight
{
public:
    Vector3f Color;
    float AmbientIntensity;

    BaseLight()
    {
        Color = Vector3f(1.0f, 1.0f, 1.0f);
        AmbientIntensity = 0.7f;
    }
};


class DirectionalLight : public BaseLight
{
public:
    Vector3f WorldDirection = Vector3f(0, 0, 0);
    float DiffuseIntensity = 0;

    void CalcLocalDirection(const Matrix4f& World);

    const Vector3f& GetLocalDirection() const { return LocalDirection; }
private:
    Vector3f LocalDirection = Vector3f(0, 0, 0);
};


class LightingTechnique : public Technique
{
public:

    LightingTechnique();

    virtual bool Init();

    void SetWorldUniform(const Matrix4f& gWorld);
    void SetViewUniform(const Matrix4f& gView);
    void SetProjectionUniform(const Matrix4f& gPerspective);
    void SetCameraLocalPos(const Vector3f& LocalPosition);

    void SetTextureUnit(unsigned int TextureUnit);
    void SetLight(const DirectionalLight& Light);
    void SetMaterial(const Material& material);
    void SetRenderMode(LightingShaderRenderMode renderMode);
    void SetEffectStatus(LightShaderEffect effect, int status = 1);
    void InverseEffectStatus(LightShaderEffect effect);

private:

    GLuint worldLoc, viewLoc, perspectiveLoc;
    GLuint samplerLoc;
    GLuint CameraLocalPosLoc;
    GLuint renderModeLoc;
    GLuint effectFlagsLoc;

    struct {
        GLuint AmbientColor;
        GLuint DiffuseColor;
    } materialLoc;

    struct {
        GLuint Color;
        GLuint AmbientIntensity;
        GLuint Direction;
        GLuint DiffuseIntensity;
    } lightLoc;

    GLuint effect_flags_ = 0;
};
#pragma once

#include "technique.hpp"
#include "math_3d.h"


class FirstTechnique : public Technique
{
public:

    FirstTechnique();

    virtual bool Init();
    
    void SetWorldUniform(const Matrix4f& gWorld);
    void SetViewUniform(const Matrix4f& gView);
    void SetProjectionUniform(const Matrix4f& gPerspective);

    void SetTextureUnit(unsigned int TextureUnit);
    
private:

    GLuint worldLoc, viewLoc, perspectiveLoc;
    GLuint samplerLoc;
};
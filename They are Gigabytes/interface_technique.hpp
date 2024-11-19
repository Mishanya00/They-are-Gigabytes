#pragma once

#include "technique.hpp"
#include "math_3d.h"


class InterfaceTechnique : public Technique
{
public:

    InterfaceTechnique();

    virtual bool Init();

    void SetViewUniform(const Matrix4f& gView);
    void SetProjectionUniform(const Matrix4f& gPerspective);
    void SetTextureUnit(unsigned int TextureUnit);

private:

    GLuint viewLoc, perspectiveLoc;
    GLuint samplerLoc;

};
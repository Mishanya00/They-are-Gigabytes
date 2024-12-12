#pragma once

#include "technique.hpp"
#include "math_3d.h"


class InterfaceTechnique : public Technique
{
public:

    InterfaceTechnique();

    virtual bool Init();

    void Enable();

    void SetColorUniform(GLfloat r, GLfloat g, GLfloat b, GLfloat alpha);

private:

    GLuint colorLoc;

};
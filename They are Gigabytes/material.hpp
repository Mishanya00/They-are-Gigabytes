#pragma once

#include "math_3d.h"
#include "texture.hpp"

struct PBRMaterial
{
    float Roughness = 0.0f;
    bool IsMetal = false;
    Vector3f Color = Vector3f(0.0f, 0.0f, 0.0f);
    rgl::Texture* pAlbedo = NULL;
    rgl::Texture* pRoughness = NULL;
    rgl::Texture* pMetallic = NULL;
    rgl::Texture* pNormalMap = NULL;
};


class Material {

public:
    Vector3f AmbientColor = Vector3f(0.0f, 0.0f, 0.0f);
    Vector3f DiffuseColor = Vector3f(0.0f, 0.0f, 0.0f);
    Vector3f SpecularColor = Vector3f(0.0f, 0.0f, 0.0f);

    PBRMaterial PBRmaterial;

    // TODO: need to deallocate these
    rgl::Texture* pDiffuse = NULL; // base color of the material
    rgl::Texture* pSpecularExponent = NULL;

    ~Material()
    {
        if (pDiffuse) {
            delete pDiffuse;
        }

        if (pSpecularExponent) {
            delete pSpecularExponent;
        }
    }
};
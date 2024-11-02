#pragma once

#include <glew.h>
#include "math_3d.h"
#include "world_transform.hpp"
#include "material.hpp"


class IRenderCallbacks
{
public:
    virtual void DrawStartCB(unsigned int DrawIndex) {}

    virtual void ControlSpecularExponent(bool IsEnabled) {}

    virtual void SetMaterial(const Material & material) {}

    virtual void DisableDiffuseTexture() {}
};


class MeshCommon {

public:
    MeshCommon() {}

    void SetScale(float Scale);
    void SetRotation(float x, float y, float z);
    void SetPosition(float x, float y, float z);
    void SetPosition(const Vector3f& pos) { SetPosition(pos.x, pos.y, pos.z); }

    Vector3f GetPosition() const;

    virtual void Render(IRenderCallbacks* pRenderCallbacks = NULL) = 0;

    rgl::WorldTransform & GetWorldTransform() { return m_worldTransform; }

    Matrix4f GetWorldMatrix() { return m_worldTransform.GetMatrix(); }

protected:
    rgl::WorldTransform m_worldTransform;
};

inline void MeshCommon::SetScale(float Scale)
{
    m_worldTransform.SetScale(Scale);
}


inline void MeshCommon::SetRotation(float x, float y, float z)
{
    m_worldTransform.SetRotation(Vector3f(x, y, z));
}


inline void MeshCommon::SetPosition(float x, float y, float z)
{
    m_worldTransform.SetPosition(x, y, z);
}


inline Vector3f MeshCommon::GetPosition() const
{
    return m_worldTransform.GetPosition();
}
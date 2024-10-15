#include "math_3d.h"


//--------------------------------------------//
//                  Vector3f                  //
//--------------------------------------------//

Vector3f& Vector3f::Normalize()
{
    float len = Length();

    assert(len != 0);

    x /= len;
    y /= len;
    z /= len;

    return *this;
}

Vector3f Vector3f::Cross(const Vector3f& v) const
{
    const float _x = y * v.z - z * v.y;
    const float _y = z * v.x - x * v.z;
    const float _z = x * v.y - y * v.x;

    return Vector3f(_x, _y, _z);
}

void Vector3f::Rotate(float Angle, const Vector3f& V)
{
    Quaternion RotationQ(Angle, V);

    Quaternion ConjugateQ = RotationQ.Conjugate();

    Quaternion W = RotationQ * (*this) * ConjugateQ;

    x = W.x;
    y = W.y;
    z = W.z;
}

Vector3f Vector3f::Negate() const
{
    Vector3f ret(-x, -y, -z);
    return ret;
}


//--------------------------------------------//
//                  Vector4f                  //
//--------------------------------------------//


Vector4f& Vector4f::Normalize()
{
    float len = Length();

    assert(len != 0);

    x /= len;
    y /= len;
    z /= len;
    w /= len;

    return *this;
}


//--------------------------------------------//
//                  Matrix4f                  //
//--------------------------------------------//


void Matrix4f::InitCameraTransform(const Vector3f& Target, const Vector3f& Up)
{
    Vector3f N = Target;
    N.Normalize();

    Vector3f UpNorm = Up;
    UpNorm.Normalize();

    Vector3f U;
    U = UpNorm.Cross(N);
    U.Normalize();

    Vector3f V = N.Cross(U);

    m[0][0] = U.x;   m[0][1] = U.y;   m[0][2] = U.z;   m[0][3] = 0.0f;
    m[1][0] = V.x;   m[1][1] = V.y;   m[1][2] = V.z;   m[1][3] = 0.0f;
    m[2][0] = N.x;   m[2][1] = N.y;   m[2][2] = N.z;   m[2][3] = 0.0f;
    m[3][0] = 0.0f;  m[3][1] = 0.0f;  m[3][2] = 0.0f;  m[3][3] = 1.0f;
}

void Matrix4f::InitCameraTransform(const Vector3f& Pos, const Vector3f& Target, const Vector3f& Up)
{
    Matrix4f CameraTranslation;
    CameraTranslation.InitTranslationTransform(-Pos.x, -Pos.y, -Pos.z);

    Matrix4f CameraRotateTrans;
    CameraRotateTrans.InitCameraTransform(Target, Up);

    *this = CameraRotateTrans * CameraTranslation;
}

void Matrix4f::InitScaleTransform(float ScaleX, float ScaleY, float ScaleZ)
{
    m[0][0] = ScaleX; m[0][1] = 0.0f;   m[0][2] = 0.0f;   m[0][3] = 0.0f;
    m[1][0] = 0.0f;   m[1][1] = ScaleY; m[1][2] = 0.0f;   m[1][3] = 0.0f;
    m[2][0] = 0.0f;   m[2][1] = 0.0f;   m[2][2] = ScaleZ; m[2][3] = 0.0f;
    m[3][0] = 0.0f;   m[3][1] = 0.0f;   m[3][2] = 0.0f;   m[3][3] = 1.0f;
}

void Matrix4f::InitScaleTransform(float Scale)
{
    InitScaleTransform(Scale, Scale, Scale);
}

void Matrix4f::InitScaleTransform(const Vector3f& Scale)
{
    InitScaleTransform(Scale.x, Scale.y, Scale.z);
}

void Matrix4f::InitTranslationTransform(float x, float y, float z)
{
    m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = x;
    m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = y;
    m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = z;
    m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
}

void Matrix4f::InitTranslationTransform(const Vector3f & d_translate)
{
    InitTranslationTransform(d_translate.x, d_translate.y, d_translate.z);
}

void Matrix4f::InitRotateTransform(float RotateX, float RotateY, float RotateZ)
{
    Matrix4f rx, ry, rz;

    float x = ToRadian(RotateX);
    float y = ToRadian(RotateY);
    float z = ToRadian(RotateZ);

    rx.InitRotationX(x);
    ry.InitRotationY(y);
    rz.InitRotationZ(z);

    *this = rz * ry * rx;
}

void Matrix4f::InitRotateTransformZYX(float RotateX, float RotateY, float RotateZ)
{
    Matrix4f rx, ry, rz;

    float x = ToRadian(RotateX);
    float y = ToRadian(RotateY);
    float z = ToRadian(RotateZ);

    rx.InitRotationX(x);
    ry.InitRotationY(y);
    rz.InitRotationZ(z);

    *this = rx * ry * rz;
}

void Matrix4f::InitRotateTransform(const Vector3f& Rotate)
{
    InitRotateTransform(Rotate.x, Rotate.y, Rotate.z);
}

// Left handed coordinate system

void Matrix4f::InitRotationX(float x)
{
    m[0][0] = 1.0f; m[0][1] = 0.0f;  m[0][2] = 0.0f; m[0][3] = 0.0f;
    m[1][0] = 0.0f; m[1][1] = cosf(x);  m[1][2] = sinf(x);  m[1][3] = 0.0f;
    m[2][0] = 0.0f; m[2][1] = -sinf(x); m[2][2] = cosf(x); m[2][3] = 0.0f;
    m[3][0] = 0.0f; m[3][1] = 0.0f;  m[3][2] = 0.0f; m[3][3] = 1.0f;
}

void Matrix4f::InitRotationY(float y)
{
    m[0][0] = cosf(y); m[0][1] = 0.0f; m[0][2] = -sinf(y); m[0][3] = 0.0f;
    m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = 0.0f;
    m[2][0] = sinf(y); m[2][1] = 0.0f; m[2][2] = cosf(y); m[2][3] = 0.0f;
    m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
}

void Matrix4f::InitRotationZ(float z)
{
    m[0][0] = cosf(z);  m[0][1] = sinf(z);  m[0][2] = 0.0f; m[0][3] = 0.0f;
    m[1][0] = -sinf(z); m[1][1] = cosf(z); m[1][2] = 0.0f; m[1][3] = 0.0f;
    m[2][0] = 0.0f;  m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = 0.0f;
    m[3][0] = 0.0f;  m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
}

void Matrix4f::InitPersProjTransform(const PersProjInfo& p)
{
    float ar = p.Height / p.Width;
    float zRange = p.zNear - p.zFar;
    float tanHalfFOV = tanf(ToRadian(p.FOV / 2.0f));

    m[0][0] = 1 / tanHalfFOV; m[0][1] = 0.0f;                 m[0][2] = 0.0f;                        m[0][3] = 0.0;
    m[1][0] = 0.0f;         m[1][1] = 1.0f / (tanHalfFOV * ar); m[1][2] = 0.0f;                        m[1][3] = 0.0;
    m[2][0] = 0.0f;         m[2][1] = 0.0f;                 m[2][2] = (-p.zNear - p.zFar) / zRange; m[2][3] = 2.0f * p.zFar * p.zNear / zRange;
    m[3][0] = 0.0f;         m[3][1] = 0.0f;                 m[3][2] = 1.0f;                        m[3][3] = 0.0;
}


//--------------------------------------------//
//                  Quaternion                //
//--------------------------------------------//


Quaternion::Quaternion(float angle, const Vector3f& V)
{
    float half_angle_rad = ToRadian(angle / 2);

    float sin_half_angle = sinf(half_angle_rad);
    float cos_half_angle = cosf(half_angle_rad);

    x = V.x * sin_half_angle;
    y = V.y * sin_half_angle;
    z = V.z * sin_half_angle;
    w = cos_half_angle;
}

Quaternion::Quaternion(float _x, float _y, float _z, float _w)
{
    x = _x;
    y = _y;
    z = _z;
    w = _w;
}

void Quaternion::Normalize()
{
    float length = sqrtf(x * x + y * y + z * z + w * w);

    x /= length;
    y /= length;
    z /= length;
    w /= length;
}

Quaternion Quaternion::Conjugate() const
{
    Quaternion ret(-x, -y, -z, w);
    return ret;
}

Quaternion operator*(const Quaternion& q, const Vector3f& v)
{
    float w = -(q.x * v.x) - (q.y * v.y) - (q.z * v.z);
    float x = (q.w * v.x) + (q.y * v.z) - (q.z * v.y);
    float y = (q.w * v.y) + (q.z * v.x) - (q.x * v.z);
    float z = (q.w * v.z) + (q.x * v.y) - (q.y * v.x);

    Quaternion ret(x, y, z, w);

    return ret;
}

Quaternion operator*(const Quaternion& l, const Quaternion& r)
{
    float w = (l.w * r.w) - (l.x * r.x) - (l.y * r.y) - (l.z * r.z);
    float x = (l.x * r.w) + (l.w * r.x) + (l.y * r.z) - (l.z * r.y);
    float y = (l.y * r.w) + (l.w * r.y) + (l.z * r.x) - (l.x * r.z);
    float z = (l.z * r.w) + (l.w * r.z) + (l.x * r.y) - (l.y * r.x);

    Quaternion ret(x, y, z, w);

    return ret;
}

Vector3f Quaternion::ToDegrees()
{
    float f[3];

    f[0] = atan2(x * z + y * w, x * w - y * z);
    f[1] = acos(-x * x - y * y - z * z - w * w);
    f[2] = atan2(x * z - y * w, x * w + y * z);

    f[0] = ToDegree(f[0]);
    f[1] = ToDegree(f[1]);
    f[2] = ToDegree(f[2]);

    return Vector3f(f);
}
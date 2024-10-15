#pragma once

#include "math_3d.h"

// RGL from Rapid OpenGL (Just a name for my "lib")
namespace rgl
{
	class WorldTransform
	{
	public:

		WorldTransform() {}

		void SetScale(float new_scale);
		void SetPosition(Vector3f new_position);
		void SetRotation(Vector3f new_rotation);

		void Translate(float dx, float dy, float dz);
		void Translate(Vector3f d_translation);

		void Rotate(float x, float y, float z);
		void Rotate(Vector3f d_rotation);

		void Scale(float d_scale);

		Matrix4f GetMatrix();

	protected:
		float scale_ = 1.0f;
		Vector3f position_ = Vector3f(0.0f, 0.0f, 0.0f);
		Vector3f rotation_ = Vector3f(0.0f, 0.0f, 0.0f);
	};
}

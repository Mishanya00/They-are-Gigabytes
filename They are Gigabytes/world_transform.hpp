#pragma once

#include "math_3d.h"

// RGL from Rapid OpenGL (Just a name for my "lib")
namespace rgl
{
	class WorldTransform
	{
	public:

		WorldTransform();

		void SetScale(float new_scale);
		void SetPosition(Vector3f new_position);
		void SetPosition(float x, float y, float z);
		void SetRotation(Vector3f new_rotation);
		void SetRotation(float rotX, float rotY, float rotZ);

		void Translate(float dx, float dy, float dz);
		void Translate(Vector3f d_translation);

		void Rotate(float x, float y, float z);
		void Rotate(Vector3f d_rotation);

		void Save();
		void LoadSaved();

		void Scale(float d_scale);

		Matrix4f GetMatrix();
		float GetScale() const;
		Vector3f GetPosition() const;
		Vector3f GetRotation() const;

	protected:
		float scale_ = 1.0f;
		Vector3f position_ = Vector3f(0.0f, 0.0f, 0.0f);
		Vector3f rotation_ = Vector3f(0.0f, 0.0f, 0.0f);

		//lmao, dont remember why did I create these members
		float scale_saved_ = scale_;
		Vector3f position_saved_ = position_;
		Vector3f rotation_saved_ = rotation_;
	};
}

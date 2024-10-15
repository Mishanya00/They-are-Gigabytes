#include "world_transform.hpp"

namespace rgl
{
	void WorldTransform::SetScale(float new_scale)
	{
		scale_ = new_scale;
	}
	void WorldTransform::SetPosition(Vector3f new_position)
	{
		position_ = new_position;
	}
	void WorldTransform::SetRotation(Vector3f new_rotation)
	{
		rotation_ = new_rotation;
	}

	void WorldTransform::Scale(float d_scale)
	{
		scale_ *= d_scale;
	}

	void WorldTransform::Translate(float dx, float dy, float dz)
	{
		position_.x += dx;
		position_.y += dy;
		position_.z += dz;
	}

	void WorldTransform::Translate(Vector3f d_translation)
	{
		position_.x += d_translation.x;
		position_.y += d_translation.y;
		position_.z += d_translation.z;
	}

	void WorldTransform::Rotate(Vector3f d_rotation)
	{
		rotation_.x += d_rotation.x;
		rotation_.y += d_rotation.y;
		rotation_.z += d_rotation.z;
	}

	void WorldTransform::Rotate(float x, float y, float z)
	{
		rotation_.x += x;
		rotation_.y += y;
		rotation_.z += z;
	}
	
	Matrix4f WorldTransform::GetMatrix()
	{
		Matrix4f Scale;
		Scale.InitScaleTransform(scale_, scale_, scale_);

		Matrix4f Rotation;
		Rotation.InitRotateTransform(rotation_.x, rotation_.y, rotation_.z);

		Matrix4f Translation;
		Translation.InitTranslationTransform(position_.x, position_.y, position_.z);

		Matrix4f WorldTransformation = Translation * Rotation * Scale;

		return WorldTransformation;
	}
}
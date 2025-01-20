#include "world_transform.hpp"

namespace rgl
{
	WorldTransform::WorldTransform() {}

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
	void WorldTransform::SetPosition(float x, float y, float z)
	{
		position_.x = x;
		position_.y = y;
		position_.z = z;
	}
	void WorldTransform::SetRotation(float rotX, float rotY, float rotZ)
	{
		rotation_.x = rotX;
		rotation_.y = rotY;
		rotation_.z = rotZ;
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

	void WorldTransform::Save()
	{
		scale_saved_ = scale_;
		position_saved_ = position_;
		rotation_saved_ = rotation_;
	}

	void WorldTransform::LoadSaved()
	{
		scale_ = scale_saved_;
		position_ = position_saved_;
		rotation_ = rotation_saved_;
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

	Matrix4f WorldTransform::GetReversedTranslationMatrix() const
	{
		Matrix4f ReversedTranslation;
		ReversedTranslation.InitTranslationTransform(position_.Negate());
		return ReversedTranslation;
	}

	Matrix4f WorldTransform::GetReversedRotationMatrix() const
	{
		Matrix4f ReversedRotation;
		ReversedRotation.InitRotateTransformZYX(-rotation_.x, -rotation_.y, -rotation_.z);
		return ReversedRotation;
	}

	float WorldTransform::GetScale() const { return scale_; }
	Vector3f WorldTransform::GetPosition() const { return position_; }
	Vector3f WorldTransform::GetRotation() const { return rotation_; }
}
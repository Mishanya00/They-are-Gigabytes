#include "basic_model.hpp"


BasicModel::BasicModel(std::shared_ptr<BasicMesh> mesh, Vector3f coords) : mesh_(mesh)
{
	world_matrix_.SetPosition(coords);
	world_matrix_.SetRotation(0, 0, 0);
	world_matrix_.SetScale(1.0f);		// default scale
}

BasicModel::BasicModel(std::shared_ptr<BasicMesh> mesh, float x, float y, float z) : mesh_(mesh)
{
	world_matrix_.SetPosition(x, y, z);
	world_matrix_.SetRotation(0, 0, 0);
	world_matrix_.SetScale(1.0f);		// default scale
}

void BasicModel::SetScale(float new_scale)
{
	world_matrix_.SetScale(new_scale);
}

void BasicModel::Scale(float new_scale)
{
	world_matrix_.Scale(new_scale);
}

void BasicModel::SetCoords(Vector3f new_coords)
{
	world_matrix_.SetPosition(new_coords);
}

void BasicModel::SetCoords(float x, float y, float z)
{
	world_matrix_.SetPosition(x, y, z);
}

void BasicModel::Move(Vector3f d_move)
{
	world_matrix_.Translate(d_move);
}

void BasicModel::Move(float x, float y, float z)
{
	world_matrix_.Translate(x, y, z);
}

void BasicModel::Render(LightingTechnique& shader, DirectionalLight& light)
{
	Matrix4f model_matrix = world_matrix_.GetMatrix();

	light.CalcLocalDirection(model_matrix);
	shader.SetLight(light);
	shader.SetWorldUniform(world_matrix_.GetMatrix());
	shader.SetMaterial(mesh_->GetMaterial());

	model_matrix = world_matrix_.GetReversedTranslationMatrix();
	shader.SetCameraLocalPos(Vector3f(model_matrix.m[3][0], model_matrix.m[3][1], model_matrix.m[3][2]));

	mesh_->Render();
}

Vector3f BasicModel::GetPosition()
{
	return world_matrix_.GetPosition();
}
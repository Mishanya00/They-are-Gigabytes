#include "basic_model.hpp"

#include "world_transform.hpp"


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

void BasicModel::Render(FirstTechnique& shader)
{
	shader.SetWorldUniform(world_matrix_.GetMatrix());
	mesh_->Render();
}
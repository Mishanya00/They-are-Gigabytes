#include "basic_model.hpp"

#include "world_transform.hpp"


BasicModel::BasicModel(std::shared_ptr<BasicMesh> mesh, Vector3f coords) : mesh_(mesh), coords_(coords) {}
BasicModel::BasicModel(std::shared_ptr<BasicMesh> mesh, float x, float y, float z) : mesh_(mesh)
{
	coords_.x = x;
	coords_.y = y;
	coords_.z = z;
}

void BasicModel::Render(FirstTechnique& shader)
{
	shader.SetWorldUniform(Matrix4f(coords_.x, coords_.y, coords_.z, 1.0f));
}
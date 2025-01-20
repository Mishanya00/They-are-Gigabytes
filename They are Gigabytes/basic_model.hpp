#pragma once

#include "basic_mesh.hpp"

#include <memory>
#include <string>

#include "math_3d.h"
#include "technique.hpp"
#include "lighting_technique.hpp"
#include "world_transform.hpp"


class BasicModel
{
public:

	// shared pointer not to duplicate the same meshes for each existing model
	BasicModel(std::shared_ptr<BasicMesh> mesh, Vector3f coords);
	BasicModel(std::shared_ptr<BasicMesh> mesh, float x, float y, float z);

	void SetScale(float new_scale);
	void Scale(float scale_by);

	void SetCoords(Vector3f new_coords);
	void SetCoords(float x, float y, float z);
	void Move(Vector3f d_move);
	void Move(float x, float y, float z);

	void Render(LightingTechnique& shader, DirectionalLight& light);

	Vector3f GetPosition();

private:

	rgl::WorldTransform world_matrix_;   // position, rotation and scale of model
	std::shared_ptr<BasicMesh> mesh_;
};
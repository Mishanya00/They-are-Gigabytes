#pragma once

#include <memory>

#include "basic_mesh.hpp"
#include "basic_model.hpp"


extern std::shared_ptr<BasicMesh> tower_mesh;
extern std::shared_ptr<BasicMesh> cpu_mesh;
extern std::shared_ptr<BasicMesh> zigg_mesh;
extern std::shared_ptr<BasicMesh> tile_mesh;
extern std::shared_ptr<BasicMesh> energy_tile_mesh;
extern std::shared_ptr<BasicMesh> extractor_mesh;
extern std::shared_ptr<BasicMesh> science_mesh;
extern std::shared_ptr<BasicMesh> antivirus_mesh;

void LoadMeshes();
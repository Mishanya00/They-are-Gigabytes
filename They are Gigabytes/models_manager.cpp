#include "models_manager.hpp"

#include <iostream>

std::shared_ptr<BasicMesh> tower_mesh;
std::shared_ptr<BasicMesh> zigg_mesh;
std::shared_ptr<BasicMesh> cpu_mesh;


void LoadMeshes()
{
    tower_mesh = std::make_shared<BasicMesh>();
    if (!tower_mesh->LoadMesh("../contents/buildings/tower/tower2.obj")) {
        std::cerr << "Tower mesh not loaded!\n";
    }

    zigg_mesh = std::make_shared<BasicMesh>();
    if (!zigg_mesh->LoadMesh("../contents/buildings/ziggurat/Pyramid.obj")) {
        std::cerr << "Ziggurat mesh not loaded!\n";
    }

    cpu_mesh = std::make_shared<BasicMesh>();
    if (!cpu_mesh->LoadMesh("../contents/buildings/cpu/cpu.obj")) {
        std::cerr << "CPU mesh not loaded!\n";
    }
}
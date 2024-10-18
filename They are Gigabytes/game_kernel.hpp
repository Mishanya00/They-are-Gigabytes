#pragma once

#include "world_transform.hpp"
#include "camera.hpp"


extern int ClientWidth;
extern int ClientHeight;

extern rgl::WorldTransform WorldMatrix;
extern PersProjInfo ProjectionInfo;

//rgl::Camera GameCamera;
extern rgl::Camera GameCamera;


void InitGameKernel();
void UpdateGameWindowSize(int width, int height);
void GameFrame();
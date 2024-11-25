#pragma once

#include "world_transform.hpp"
#include "camera.hpp"
#include <glew.h>
#include "texture.hpp"


extern int ClientWidth;
extern int ClientHeight;
extern rgl::WorldTransform WorldMatrix;
extern PersProjInfo ProjectionInfo;
extern rgl::Texture* pTexture;
extern rgl::Camera GameCamera;


void GameKernelInit();
void UpdateGameWindowSize(int width, int height);
void GameFrame();
void DrawGameFrame();
void DrawSubsystemInit();
void DrawInterface();
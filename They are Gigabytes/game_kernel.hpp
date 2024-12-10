#pragma once

#include "world_transform.hpp"
#include "camera.hpp"
#include <glew.h>
#include "texture.hpp"


extern int ClientWidth;
extern int ClientHeight;

void PassiveMouseComponentsHandler(int x, int y);
void GameKernelInit();
void UpdateGameWindowSize(int width, int height);
void GameFrame();
void DrawGameFrame();
void GameInterfaceInit();
void DrawInterface();

void GameMouseHandler(int button, int state, int x, int y);
void KeyboardHandler(unsigned char key, int x, int y);
void PassiveMotionHandler(int x, int y);
void KeyboardSpecialHandler(int key, int x, int y);
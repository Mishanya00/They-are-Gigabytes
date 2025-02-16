#pragma once

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
void GameKeyboardHandler(int key, int action);
void GamePassiveMotionHandler(int x, int y);
void GameKeyboardSpecialHandler(int key, int x, int y);
void GameMouseScrollHandler(double yoffset);
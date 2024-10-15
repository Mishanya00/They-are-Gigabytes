#pragma once

#include <glew.h>
#include "texture.hpp"


extern GLuint CubeVBO;
extern GLuint CubeEBO;
extern GLuint CubeVAO;
extern GLuint PyramidVBO;
extern GLuint PyramidEBO;
extern GLuint PyramidVAO;
extern rgl::Texture * pTexture;


void CreateVertexBuffers();
void CreateVertexIndexes();
void DrawGameFrame();
void DrawSubsystemInit();
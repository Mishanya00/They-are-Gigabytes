#include "draw_subsystem.hpp"

#include <iostream>
#include <glew.h>
#include "math_3d.h"
#include "game_kernel.hpp"
#include "shaders.hpp"


struct Vertex
{
    Vector3f pos;
    Vector2f tex_coord;

    Vertex() {}

    Vertex(const Vector3f& position, const Vector2f& texture_coord)
    {
        this->pos = position;
        this->tex_coord = texture_coord;
    }
};


GLuint CubeVBO;
GLuint CubeEBO;
GLuint CubeVAO;
GLuint PyramidVBO;
GLuint PyramidEBO;
GLuint PyramidVAO;
rgl::Texture* pTexture = NULL;


void CreateVertexBuffers()
{

}

void CreateCubeVAO()
{
    glGenVertexArrays(1, &CubeVAO);
    glBindVertexArray(CubeVAO);

    Vertex vertices[8];

    Vector2f t00 = Vector2f(0.0f, 0.0f);
    Vector2f t01 = Vector2f(0.0f, 1.0f);
    Vector2f t10 = Vector2f(1.0f, 0.0f);
    Vector2f t11 = Vector2f(1.0f, 1.0f);

    vertices[0] = Vertex(Vector3f(0.5f, 0.5f, 0.5f), t11);
    vertices[1] = Vertex(Vector3f(-0.5f, 0.5f, -0.5f), t10);
    vertices[2] = Vertex(Vector3f(-0.5f, 0.5f, 0.5f), t01);
    vertices[3] = Vertex(Vector3f(0.5f, -0.5f, -0.5f), t00);
    vertices[4] = Vertex(Vector3f(-0.5f, -0.5f, -0.5f), t11);
    vertices[5] = Vertex(Vector3f(0.5f, 0.5f, -0.5f), t10);
    vertices[6] = Vertex(Vector3f(0.5f, -0.5f, 0.5f), t01);
    vertices[7] = Vertex(Vector3f(-0.5f, -0.5f, 0.5f), t00);

    glGenBuffers(1, &CubeVBO);
    glBindBuffer(GL_ARRAY_BUFFER, CubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));

    unsigned int Indices[] = {
                          0, 1, 2,
                          1, 3, 4,
                          5, 6, 3,
                          7, 3, 6,
                          2, 4, 7,
                          0, 7, 6,
                          0, 5, 1,
                          1, 5, 3,
                          5, 0, 6,
                          7, 4, 3,
                          2, 1, 4,
                          0, 2, 7
    };

    glGenBuffers(1, &CubeEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, CubeEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);

    glBindVertexArray(0);   
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void CreatePyramidVAO()
{
    glGenVertexArrays(1, &PyramidVAO);
    glBindVertexArray(PyramidVAO);

    Vector2f t00 = Vector2f(0.0f, 0.0f);
    Vector2f t050 = Vector2f(0.5f, 0.0f);
    Vector2f t10 = Vector2f(1.0f, 0.0f);
    Vector2f t051 = Vector2f(0.5f, 1.0f);

    Vertex Vertices[4] = { Vertex(Vector3f(-1.0f, -1.0f, 0.5773f), t00),
                           Vertex(Vector3f(0.0f, -1.0f, -1.15475f), t050),
                           Vertex(Vector3f(1.0f, -1.0f, 0.5773f), t10),
                           Vertex(Vector3f(0.0f, 1.0f, 0.0f), t051) };

    glGenBuffers(1, &PyramidVBO);
    glBindBuffer(GL_ARRAY_BUFFER, PyramidVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

    // position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

    // tex coords
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));

    unsigned int Indices[] = { 0, 3, 1,
                               1, 3, 2,
                               2, 3, 0,
                               0, 1, 2 };

    glGenBuffers(1, &PyramidEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, PyramidEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);

    glBindVertexArray(0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void DrawGameFrame()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GameCamera.OnRender();

    Matrix4f ProjectionMatrix;
    ProjectionMatrix.InitPersProjTransform(ProjectionInfo);

    Matrix4f ViewMatrix = GameCamera.GetMatrix();

    glUniformMatrix4fv(gWorld, 1, GL_TRUE, &WorldMatrix.GetMatrix().m[0][0]);
    glUniformMatrix4fv(gProjectionLocation, 1, GL_TRUE, &ProjectionMatrix.m[0][0]);
    glUniformMatrix4fv(gViewLocation, 1, GL_TRUE, &ViewMatrix.m[0][0]);

    //Texture
    pTexture->Bind(GL_TEXTURE0);
    glUniform1i(gSamplerLocation, 0);

    GLint CurrentVAO;
    glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &CurrentVAO);

    if (CurrentVAO == CubeVAO)
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, NULL);
    else
        glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, NULL);
    
    
}

void DrawSubsystemInit()
{
    pTexture = new rgl::Texture(GL_TEXTURE_2D, "../contents/texture1.jpg");
   
    if (!pTexture->Load())
    {
        std::cerr << "Texture not loaded\n";
        exit(1);
    }

    CreateCubeVAO();
    CreatePyramidVAO();

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    glBindVertexArray(PyramidVAO);
}
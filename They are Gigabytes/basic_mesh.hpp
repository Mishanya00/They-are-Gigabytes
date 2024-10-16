#pragma once

#include <map>
#include <vector>
#include <glew.h>
#include <assimp/Importer.hpp>      
#include <assimp/scene.h>       
#include <assimp/postprocess.h>

#include "mishanya_utils.hpp"
#include "math_3d.h"
#include "texture.hpp"
#include "world_transform.hpp"


#define ASSIMP_LOAD_FLAGS (aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices)


class BasicMesh
{
public:
    BasicMesh() {};

    ~BasicMesh();

    bool LoadMesh(const std::string& Filename);

    void Render();

    void Render(unsigned int NumInstances, const Matrix4f* WVPMats, const Matrix4f* WorldMats);

    rgl::WorldTransform& GetWorldTransform() { return m_worldTransform; }

private:
    void Clear();

    bool InitFromScene(const aiScene* pScene, const std::string& Filename);

    void CountVerticesAndIndices(const aiScene* pScene, unsigned int& NumVertices, unsigned int& NumIndices);

    void ReserveSpace(unsigned int NumVertices, unsigned int NumIndices);

    void InitAllMeshes(const aiScene* pScene);

    void InitSingleMesh(const aiMesh* paiMesh);

    bool InitMaterials(const aiScene* pScene, const std::string& Filename);

    void PopulateBuffers();

#define INVALID_MATERIAL 0xFFFFFFFF


    enum BUFFER_TYPE {
        INDEX_BUFFER = 0,
        POS_VB = 1,
        TEXCOORD_VB = 2,
        NORMAL_VB = 3,
        WVP_MAT_VB = 4,
        WORLD_MAT_VB = 5,
        NUM_BUFFERS = 6
    };

    rgl::WorldTransform m_worldTransform;
    GLuint m_VAO = 0;
    GLuint m_Buffers[NUM_BUFFERS] = { 0 };

    struct BasicMeshEntry {
        BasicMeshEntry()
        {
            NumIndices = 0;
            BaseVertex = 0;
            BaseIndex = 0;
            MaterialIndex = INVALID_MATERIAL;
        }

        unsigned int NumIndices;
        unsigned int BaseVertex;
        unsigned int BaseIndex;
        unsigned int MaterialIndex;
    };

    std::vector<BasicMeshEntry> m_Meshes;
    std::vector<rgl::Texture*> m_Textures;

    // Temporary space for vertex stuff before we load them into the GPU
    std::vector<Vector3f> m_Positions;
    std::vector<Vector3f> m_Normals;
    std::vector<Vector2f> m_TexCoords;
    std::vector<unsigned int> m_Indices;
};

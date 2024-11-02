#pragma once

#include <vector>
#include <glew.h>
#include <assimp/Importer.hpp>      
#include <assimp/scene.h>       
#include <assimp/postprocess.h>

#include "mishanya_utils.hpp"
#include "math_3d.h"
#include "texture.hpp"
#include "world_transform.hpp"
#include "mesh_common.hpp"

// | aiProcess_FlipUVs
#define ASSIMP_LOAD_FLAGS (aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices)
#define INVALID_MATERIAL 0xFFFFFFFF
typedef unsigned int uint;

//#define USE_MESH_OPTIMIZER


class BasicMesh : public MeshCommon
{
public:
    BasicMesh() {};

    ~BasicMesh();

    bool LoadMesh(const std::string& Filename);

    void Render(IRenderCallbacks* pRenderCallbacks = NULL);

    void Render(uint DrawIndex, uint PrimID);

    void Render(uint NumInstances, const Matrix4f* WVPMats, const Matrix4f* WorldMats);

    const Material& GetMaterial();

    PBRMaterial& GetPBRMaterial() { return m_Materials[0].PBRmaterial; };

    void GetLeadingVertex(uint DrawIndex, uint PrimID, Vector3f& Vertex);

    void SetPBR(bool IsPBR) { m_isPBR = IsPBR; }

protected:

    void Clear();
    virtual void ReserveSpace(uint NumVertices, uint NumIndices);
    virtual void InitSingleMesh(uint MeshIndex, const aiMesh* paiMesh);
    //virtual void InitSingleMeshOpt(uint MeshIndex, const aiMesh* paiMesh);
    virtual void PopulateBuffers();
    virtual void PopulateBuffersNonDSA();
    virtual void PopulateBuffersDSA();

    struct BasicMeshEntry {
        BasicMeshEntry()
        {
            NumIndices = 0;
            BaseVertex = 0;
            BaseIndex = 0;
            MaterialIndex = INVALID_MATERIAL;
        }

        uint NumIndices;
        uint BaseVertex;
        uint BaseIndex;
        uint MaterialIndex;
    };

    std::vector<BasicMeshEntry> m_Meshes;

    const aiScene* m_pScene;

    Matrix4f m_GlobalInverseTransform;

    std::vector<uint> m_Indices;

    enum BUFFER_TYPE {
        INDEX_BUFFER = 0,
        VERTEX_BUFFER = 1,
        WVP_MAT_BUFFER = 2,  // required only for instancing
        WORLD_MAT_BUFFER = 3,  // required only for instancing
        NUM_BUFFERS = 4
    };

    GLuint m_VAO = 0;

    GLuint m_Buffers[NUM_BUFFERS] = { 0 };

private:
    struct Vertex {
        Vector3f Position;
        Vector2f TexCoords;
        Vector3f Normal;
    };

    bool InitFromScene(const aiScene* pScene, const std::string& Filename);
    void CountVerticesAndIndices(const aiScene* pScene, uint& NumVertices, uint& NumIndices);
    void InitAllMeshes(const aiScene* pScene);
    //void OptimizeMesh(int MeshIndex, std::vector<uint>& Indices, std::vector<Vertex>& Vertices);
    bool InitMaterials(const aiScene* pScene, const std::string& Filename);
    void LoadTextures(const std::string& Dir, const aiMaterial* pMaterial, int index);

    void LoadDiffuseTexture(const std::string& Dir, const aiMaterial* pMaterial, int index);
    void LoadDiffuseTextureEmbedded(const aiTexture* paiTexture, int MaterialIndex);
    void LoadDiffuseTextureFromFile(const std::string& dir, const aiString& Path, int MaterialIndex);

    void LoadSpecularTexture(const std::string& Dir, const aiMaterial* pMaterial, int index);
    void LoadSpecularTextureEmbedded(const aiTexture* paiTexture, int MaterialIndex);
    void LoadSpecularTextureFromFile(const std::string& dir, const aiString& Path, int MaterialIndex);

    void LoadAlbedoTexture(const std::string& Dir, const aiMaterial* pMaterial, int index);
    void LoadAlbedoTextureEmbedded(const aiTexture* paiTexture, int MaterialIndex);
    void LoadAlbedoTextureFromFile(const std::string& dir, const aiString& Path, int MaterialIndex);

    void LoadMetalnessTexture(const std::string& Dir, const aiMaterial* pMaterial, int index);
    void LoadMetalnessTextureEmbedded(const aiTexture* paiTexture, int MaterialIndex);
    void LoadMetalnessTextureFromFile(const std::string& dir, const aiString& Path, int MaterialIndex);

    void LoadRoughnessTexture(const std::string& Dir, const aiMaterial* pMaterial, int index);
    void LoadRoughnessTextureEmbedded(const aiTexture* paiTexture, int MaterialIndex);
    void LoadRoughnessTextureFromFile(const std::string& dir, const aiString& Path, int MaterialIndex);

    void LoadColors(const aiMaterial* pMaterial, int index);

    void SetupRenderMaterialsPhong(unsigned int MeshIndex, unsigned int MaterialIndex, IRenderCallbacks* pRenderCallbacks);
    void SetupRenderMaterialsPBR();

    std::vector<Material> m_Materials;

    // Temporary space for vertex stuff before we load them into the GPU
    std::vector<Vertex> m_Vertices;

    Assimp::Importer m_Importer;

    bool m_isPBR = false;
};

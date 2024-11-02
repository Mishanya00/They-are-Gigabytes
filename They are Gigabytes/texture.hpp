#pragma once

#include <string>
#include <glew.h>
#include "math_3d.h"


#define COLOR_TEXTURE_UNIT              GL_TEXTURE0
#define COLOR_TEXTURE_UNIT_INDEX        0
#define SHADOW_TEXTURE_UNIT             GL_TEXTURE1
#define SHADOW_TEXTURE_UNIT_INDEX       1
#define NORMAL_TEXTURE_UNIT             GL_TEXTURE2
#define NORMAL_TEXTURE_UNIT_INDEX       2
#define RANDOM_TEXTURE_UNIT             GL_TEXTURE3
#define RANDOM_TEXTURE_UNIT_INDEX       3
#define DISPLACEMENT_TEXTURE_UNIT       GL_TEXTURE4
#define DISPLACEMENT_TEXTURE_UNIT_INDEX 4
#define ALBEDO_TEXTURE_UNIT             GL_TEXTURE5
#define ALBEDO_TEXTURE_UNIT_INDEX       5          
#define ROUGHNESS_TEXTURE_UNIT          GL_TEXTURE6
#define ROUGHNESS_TEXTURE_UNIT_INDEX    6
#define MOTION_TEXTURE_UNIT             GL_TEXTURE7
#define MOTION_TEXTURE_UNIT_INDEX       7
#define SPECULAR_EXPONENT_UNIT             GL_TEXTURE8
#define SPECULAR_EXPONENT_UNIT_INDEX       8
#define CASCACDE_SHADOW_TEXTURE_UNIT0       SHADOW_TEXTURE_UNIT
#define CASCACDE_SHADOW_TEXTURE_UNIT0_INDEX SHADOW_TEXTURE_UNIT_INDEX
#define CASCACDE_SHADOW_TEXTURE_UNIT1       GL_TEXTURE9
#define CASCACDE_SHADOW_TEXTURE_UNIT1_INDEX 9
#define CASCACDE_SHADOW_TEXTURE_UNIT2       GL_TEXTURE10
#define CASCACDE_SHADOW_TEXTURE_UNIT2_INDEX 10
#define SHADOW_CUBE_MAP_TEXTURE_UNIT        GL_TEXTURE11
#define SHADOW_CUBE_MAP_TEXTURE_UNIT_INDEX  11
#define SHADOW_MAP_RANDOM_OFFSET_TEXTURE_UNIT       GL_TEXTURE12
#define SHADOW_MAP_RANDOM_OFFSET_TEXTURE_UNIT_INDEX 12
#define DETAIL_MAP_TEXTURE_UNIT                     GL_TEXTURE13
#define DETAIL_MAP_TEXTURE_UNIT_INDEX               13
#define METALLIC_TEXTURE_UNIT                       GL_TEXTURE14
#define METALLIC_TEXTURE_UNIT_INDEX                 14
#define HEIGHT_TEXTURE_UNIT                         GL_TEXTURE15
#define HEIGHT_TEXTURE_UNIT_INDEX                   15


namespace rgl
{
    class Texture
    {
    public:
        Texture(GLenum TextureTarget, const std::string& FileName);

        Texture(GLenum TextureTarget);

        // Should be called once to load the texture
        bool Load();

        void Load(unsigned int BufferSize, void* pImageData);

        void Load(const std::string& Filename);

        void LoadRaw(int Width, int Height, int BPP, const unsigned char* pImageData);

        void LoadF32(int Width, int Height, const float* pImageData);

        // Must be called at least once for the specific texture unit
        void Bind(GLenum TextureUnit);

        void GetImageSize(int& ImageWidth, int& ImageHeight)
        {
            ImageWidth = m_imageWidth;
            ImageHeight = m_imageHeight;
        }

        GLuint GetTexture() const { return m_textureObj; }

    private:
        void LoadInternal(const void* pImageData);
        void LoadInternalNonDSA(const void* pImageData);
        void LoadInternalDSA(const void* pImageData);

        void BindInternalNonDSA(GLenum TextureUnit);
        void BindInternalDSA(GLenum TextureUnit);

        std::string m_fileName;
        GLenum m_textureTarget;
        GLuint m_textureObj;
        int m_imageWidth = 0;
        int m_imageHeight = 0;
        int m_imageBPP = 0;
    };
}

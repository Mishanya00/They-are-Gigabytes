#pragma once

#include <glew.h>
#include "font-manager.h"
#include "markup.h"
#include "texture-font.h"
#include "text-buffer.h"
#include "mat4.h"
#include "shader.h"

#include <vector>


using namespace ftgl;

namespace rgl {

    static vec4 clWhite = { {1.0f,1.0f,1.0f,1.0f} };
    static vec4 clBlue = { {0.0f,0.0f,1.0f,1.0f} };
    static vec4 clRed = { {1.0f,0.0f,0.0f,1.0f} };
    static vec4 clBlack = { {0.0f,0.0f,0.0f,1.0f} };
    static vec4 clYellow = { {1.0f, 1.0f, 0.0f, 1.0f} };
    static vec4 clOrange1 = { {1.0f, 0.9f, 0.0f, 1.0f} };
    static vec4 clOrange2 = { {1.0f, 0.6f, 0.0f, 1.0f} };
    static vec4 clGreen = { {0.0f,1.0f,0.0f,1.0f} };
    static vec4 clGray = { {0.5f,0.5f,0.5f,1.0f} };
    static vec4 clCyan = { {0.0f,1.0f,1.0f,1.0f} };
    static vec4 clPurple = { {0.5f,0.0f,0.5f,1.0f} };
    static vec4 clNone = { {0.0f,0.0f,1.0f,0.0f} };


    enum FONT_TYPE {
        FONT_TYPE_OLD_STANDARD_30,
        FONT_TYPE_OLD_STANDARD_46,
        FONT_TYPE_SOURCE_CODE_PRO_30,
        FONT_TYPE_SOURCE_CODE_PRO_46,
        FONT_TYPE_SOURCE_SANS_PRO_30,
        FONT_TYPE_SOURCE_SANS_PRO_46,
        NUM_FONTS
    };


    class FontRenderer
    {
    public:
        FontRenderer();

        ~FontRenderer();

        void InitFontRenderer(int WindowWidth, int WindowHeight);

        void RenderText(FONT_TYPE FontType,
            const vec4& TopColor,
            const vec4& BottomColor,
            unsigned int x,
            unsigned int y,
            const char* pText);

        void RenderText(texture_font_t & active_font,
            const vec4& TopColor,
            const vec4& BottomColor,
            unsigned int x,
            unsigned int y,
            const char* pText);

        void RenderText(FONT_TYPE FontType,
            const vec4& Color,
            unsigned int x,
            unsigned int y,
            const char* pText)
        {
            RenderText(FontType, Color, Color, x, y, pText);
        }

        void LoadFont(FONT_TYPE type, int size);

    private:

        void LoadFonts();

        texture_atlas_t* m_pAtlas = NULL;
        vertex_buffer_t* m_pBuffer = NULL;
        std::vector<texture_font_t*> m_pFonts;
        GLuint m_shaderProg = -1;
        mat4 m_model, m_view, m_projection;
    };
}

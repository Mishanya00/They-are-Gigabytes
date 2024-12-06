#include <stdio.h>
#include <stdlib.h>
#include <glew.h>
#include <assert.h>


#ifdef _WIN64

#include "freetypeGL.h"

extern "C" {
#include "mat4.c"
#include "shader.c"
}

using namespace ftgl;
using namespace rgl;

#define MAX_STRING_LEN 128


typedef struct {
    float x, y, z;
    float u, v;
    vec4 color;
} vertex_t;

static const char* FontPaths[] = {
    "../contents/fonts/amiri-regular.ttf",
    "../contents/fonts/Liberastika-regular.ttf",
    "../contents/fonts/Lobster-regular.ttf",    
    "../contents/fonts/LuckiestGuy.ttf",
    "../contents/fonts/OldStandard-regular.ttf",
    "../contents/fonts/SourceCodePro-regular.ttf",
    "../contents/fonts/SourceSansPro-regular.ttf",
    "../contents/fonts/Vera.ttf",
    "../contents/fonts/VeraMoBd.ttf",
    "../contents/fonts/VeraMoBI.ttf",
    "../contents/fonts/VeraMono.ttf"
};

void add_text(vertex_buffer_t* m_pBuffer, texture_font_t * pFont, char* text, vec2 pen, vec4 fg_color_1, vec4 fg_color_2)
{
    for (size_t i = 0; i < strlen(text); ++i)
    {
        texture_glyph_t* glyph = texture_font_get_glyph(pFont, text + i);
        float kerning = 0.0f;
        if (i > 0)
        {
            kerning = texture_glyph_get_kerning(glyph, text + i - 1);
        }
        pen.x += kerning;

        /* Actual glyph */
        float x0 = (pen.x + glyph->offset_x);
        float y0 = (float)((int)(pen.y + glyph->offset_y));
        float x1 = (x0 + glyph->width);
        float y1 = (float)((int)(y0 - glyph->height));
        float s0 = glyph->s0;
        float t0 = glyph->t0;
        float s1 = glyph->s1;
        float t1 = glyph->t1;
        GLuint index = (GLuint)m_pBuffer->vertices->size;
        GLuint indices[] = { index, index + 1, index + 2,
                            index, index + 2, index + 3 };
        vertex_t vertices[] = {
            { (float)((int)x0),y0,0,  s0,t0,  fg_color_1 },
            { (float)((int)x0),y1,0,  s0,t1,  fg_color_2 },
            { (float)((int)x1),y1,0,  s1,t1,  fg_color_2 },
            { (float)((int)x1),y0,0,  s1,t0,  fg_color_1 } };
        vertex_buffer_push_back_indices(m_pBuffer, indices, 6);
        vertex_buffer_push_back_vertices(m_pBuffer, vertices, 4);
        pen.x += glyph->advance_x;
    }
}


FontRenderer::FontRenderer()
{
}

FontRenderer::~FontRenderer()
{
}


void FontRenderer::InitFontRenderer(int WindowWidth, int WindowHeight)
{
    m_pAtlas = texture_atlas_new(1024, 1024, 1);
    m_pBuffer = vertex_buffer_new("vertex:3f,tex_coord:2f,color:4f");
    
    LoadFonts();

    glGenTextures(1, &m_pAtlas->id);
    glBindTexture(GL_TEXTURE_2D, m_pAtlas->id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, (GLsizei)m_pAtlas->width, (GLsizei)m_pAtlas->height, 0, GL_RED, GL_UNSIGNED_BYTE, m_pAtlas->data);

    m_shaderProg = shader_load("Include/FreetypeGL/font_shader.vert", "Include/FreetypeGL/font_shader.frag");

    mat4_set_identity(&m_model);
    mat4_set_identity(&m_view);
    mat4_set_orthographic(&m_projection, 0, (float)WindowWidth, 0, (float)WindowHeight, -1, 1);
}

void FontRenderer::LoadFont(FONT_TYPE type, int size)
{
    if (type < 0 || type > NUM_FONTS) {
        printf("Error loading font!\n");
        exit(0);
    }

    m_pFonts.push_back(texture_font_new_from_file(m_pAtlas, size, FontPaths[type]));
}

void FontRenderer::LoadFonts()
{
    m_pFonts.push_back(texture_font_new_from_file(m_pAtlas, 30, "../contents/fonts/OldStandard-regular.ttf"));
    m_pFonts.push_back(texture_font_new_from_file(m_pAtlas, 46, "../contents/fonts/OldStandard-regular.ttf"));
    m_pFonts.push_back(texture_font_new_from_file(m_pAtlas, 30, "../contents/fonts/SourceCodePro-regular.ttf"));
    m_pFonts.push_back(texture_font_new_from_file(m_pAtlas, 46, "../contents/fonts/SourceCodePro-regular.ttf"));
    m_pFonts.push_back(texture_font_new_from_file(m_pAtlas, 30, "../contents/fonts/SourceSansPro-regular.ttf"));
    m_pFonts.push_back(texture_font_new_from_file(m_pAtlas, 46, "../contents/fonts/SourceSansPro-regular.ttf"));

    /*
    for (int i = 0; i < NUM_FONTS; i++) {
        m_pFonts.push_back(texture_font_new_from_file(m_pAtlas, 30, FontPaths[i]));

        if (!m_pFonts[i]) {
            printf("Error loading fonts '%s'\n", FontPaths[i]);
            exit(0);
        }
    }
    */
}

void FontRenderer::RenderText(FONT_TYPE FontType,
                              const vec4& TopColor, const vec4& BottomColor,
                              unsigned int x, unsigned int y, const char* pText)
{
    vec2 pen = { {(float)x, (float)y} };

    if (FontType >= NUM_FONTS) {
        printf("Invalid font type index %d\n", FontType);
        exit(0);
    }

    texture_font_t* pFont = m_pFonts[FontType];

    pFont->rendermode = RENDER_NORMAL;
    pFont->outline_thickness = 0;
    vertex_buffer_clear(m_pBuffer);
    add_text(m_pBuffer, pFont, (char*)pText, pen, TopColor, BottomColor);    

    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_pAtlas->id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, (GLsizei)m_pAtlas->width, (GLsizei)m_pAtlas->height, 0, GL_RED, GL_UNSIGNED_BYTE, m_pAtlas->data);

    glUseProgram(m_shaderProg);

    glUniform1i(glGetUniformLocation(m_shaderProg, "texture"), 0);
    glUniformMatrix4fv(glGetUniformLocation(m_shaderProg, "model"), 1, 0, m_model.data);
    glUniformMatrix4fv(glGetUniformLocation(m_shaderProg, "view"), 1, 0, m_view.data);
    glUniformMatrix4fv(glGetUniformLocation(m_shaderProg, "projection"), 1, 0, m_projection.data);
    vertex_buffer_render(m_pBuffer, GL_TRIANGLES);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}

#endif

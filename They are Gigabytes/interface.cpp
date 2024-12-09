#include "interface.hpp"

#include <iostream>

using namespace rgl;

// Actually, there are some bad code, may be I should not manually create "components library"

Selection::Selection()
{
    color_ = Vector3f(0, 1.0f, 0);

    vertices_[0] = Vector3f(0.0f, 0.0f, 0.0f);
    vertices_[1] = Vector3f(0.0f, 0.0f, 0.0f);
    vertices_[2] = Vector3f(0.0f, 0.0f, 0.0f);
    vertices_[3] = Vector3f(0.0f, 0.0f, 0.0f);
    vertices_[4] = Vector3f(0.0f, 0.0f, 0.0f);
    vertices_[5] = Vector3f(0.0f, 0.0f, 0.0f);

    isVisible_ = false;
    color_ = Vector3f(0.0f, 0.0f, 0.0f); // black

    glGenBuffers(1, &VBO_);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_), vertices_, GL_STATIC_DRAW);
}

void Selection::SetColor(Vector3f color)
{
    color_ = color;
}

void Selection::Render(InterfaceTechnique& shader)
{
    shader.SetColorUniform(color_.x, color_.y, color_.z, 1.0f);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDisableVertexAttribArray(0);
}

Panel::Panel()
{
    color_ = Vector4f(0.0f, 0.0f, 0.0f, 1.0f); // black
    left_ = 0;
    right_ = 0;
    bottom_ = 0;
    top_ = 0;
    vertices_[0] = Vector3f(left_, bottom_, 0.0f);
    vertices_[1] = Vector3f(right_, bottom_, 0.0f);
    vertices_[2] = Vector3f(right_, top_, 0.0f);
    vertices_[3] = Vector3f(left_, bottom_, 0.0f);
    vertices_[4] = Vector3f(right_, top_, 0.0f);
    vertices_[5] = Vector3f(left_, top_, 0.0f);

    glGenBuffers(1, &VBO_);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_), vertices_, GL_STATIC_DRAW);
}

void Panel::SetRect(int left, int bottom, int right, int top)
{
    left_ = left;
    bottom_ = bottom;
    right_ = right;
    top_ = top;

    vertices_[0] = Vector3f(left, bottom, 0.0f);
    vertices_[1] = Vector3f(right, bottom, 0.0f);
    vertices_[2] = Vector3f(right, top, 0.0f);
    vertices_[3] = Vector3f(left, bottom, 0.0f);
    vertices_[4] = Vector3f(right, top, 0.0f);
    vertices_[5] = Vector3f(left, top, 0.0f);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices_), vertices_);
}

bool Panel::isHover()
{
	return isHover_;
}

bool Panel::isVisible()
{
    return isVisible_;
}

void Panel::Render(InterfaceTechnique& shader)
{
    shader.SetColorUniform(color_.x, color_.y, color_.z, color_.w);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDisableVertexAttribArray(0);
}

void Panel::SetColor(Vector4f new_color)
{
    color_ = new_color;
}

void Panel::SetHover(int mouseX, int mouseY)
{
    if (mouseX > left_ && mouseX < right_ && mouseY > bottom_ && mouseY < top_)
        isHover_ = true;
    else
        isHover_ = false;
}

void Panel::Click()
{
    std::cout << "Panel is clicked!\n";
}

UpperPanel::UpperPanel() : Panel()
{
    SetRect(0, 0, 1920, 150);
    SetColor(Vector4f(0.0f, 0.0, 0.0f, 0.75f));
}

void UpperPanel::Click()
{
    std::cout << "UpperPanel is clicked!\n";
}

LowerPanel::LowerPanel() : Panel()
{
    SetRect(0, 1000, 1920, 1080);
    SetColor(Vector4f(0.0f, 0.0, 0.0f, 0.75f));
}

void LowerPanel::Click()
{
    std::cout << "UpperPanel is clicked!\n";
}

Label1::Label1(std::shared_ptr<FontRenderer> font) : Panel()
{
    font_ = font;
    left_ = 500;
    bottom_ = 500;
}

void Label1::Render(InterfaceTechnique& shader)
{
    font_->RenderText(FONT_TYPE_OLD_STANDARD_30, rgl::clBlack, rgl::clBlack, 500, 500, "text.c_str()");
}
/*
TextPanel::TextPanel(std::shared_ptr<rgl::FontRenderer> font_renderer, int xCoord, int yCoord) : Panel(0, 0, 0, 0)
{
    text = "text";
    x = xCoord;
    y = yCoord;
    isVisible = true;
    color = rgl::clBlack;
    font_ = font_renderer;
}

TextPanel::TextPanel(std::shared_ptr<rgl::FontRenderer> font_renderer, std::string label_text, int xCoord, int yCoord) : TextPanel(font_renderer, xCoord, yCoord)
{
    text = label_text;
}

void TextPanel::Render(rgl::FONT_TYPE type)
{
    font_->RenderText(type, color, color, x, y, text.c_str());
}
*/
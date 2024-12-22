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
    color_.x = 0.0f;
    color_.y = 0.0f;
    color_.z = 0.0f;
    color_.w = 1.0f;

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

void Panel::SetComponentType(ComponentType new_type)
{
    type_ = new_type;
}

ComponentType Panel::GetComponentType()
{
    return type_;
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
    shader.Enable();

    if (isHover_)
        shader.SetColorUniform(color_.x+0.1, color_.y+0.1, color_.z + 0.1, color_.w);
    else
        shader.SetColorUniform(color_.x, color_.y, color_.z, color_.w);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDisableVertexAttribArray(0);
}

void Panel::SetColor(Vector4f new_color)
{
    color_.x = new_color.x;
    color_.y = new_color.y;
    color_.z = new_color.z;
    color_.w = new_color.w;
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

Label::Label(int xCoord, int yCoord, std::shared_ptr<FontRenderer> font) : Panel()
{
    font_ = font;
    left_ = xCoord;
    bottom_ = yCoord;
}

void Label::Render(InterfaceTechnique& shader)
{
    font_->RenderText(FONT_TYPE_OLD_STANDARD_30, rgl::clBlack, rgl::clBlack, left_, bottom_, "text.c_str()");
}

TextPanel::TextPanel(std::shared_ptr<FontRenderer> font) : Panel()
{
    font_ = font;
    SetRect(500, 700, 1500, 800);
    SetColor(Vector4f(0.482, 0.698, 0.91, 1.0f));
}

void TextPanel::SetFontType(FONT_TYPE new_font_type)
{
    font_type_ = new_font_type;
}

void TextPanel::SetText(std::string new_text)
{
    text_ = new_text;
}

void TextPanel::Render(InterfaceTechnique& shader)
{
    Panel::Render(shader);
    font_->RenderText(font_type_, rgl::clBlack, rgl::clBlack, (left_+right_)/2 - 100, (top_+bottom_)/2 - 20, text_.c_str());
}

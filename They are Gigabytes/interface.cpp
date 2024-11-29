#include "interface.hpp"

#include <iostream>

using namespace rgl;

Panel::Panel(float left, float bottom, float right, float top)
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

    color_ = Vector3f(0.0f, 0.0f, 0.0f); // black

    glGenBuffers(1, &VBO_);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_), vertices_, GL_STATIC_DRAW);
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
    shader.SetColorUniform(color_.x, color_.y, color_.z, 1.0f);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDisableVertexAttribArray(0);
}

void Panel::SetColor(Vector3f new_color)
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

UpperPanel::UpperPanel(float left, float bottom, float right, float top) : Panel(left, bottom, right, top)
{
}

void UpperPanel::Click()
{
    std::cout << "UpperPanel is clicked!\n";
}
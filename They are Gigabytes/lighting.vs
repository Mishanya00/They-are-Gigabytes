#version 330 core

layout (location = 0) in vec3 Position;
layout (location = 1) in vec2 TexCoord;

uniform mat4 World;
uniform mat4 Projection;
uniform mat4 View;

out vec2 TexCoord0;

void main()
{
    gl_Position = Projection * View * World * vec4(Position, 1.0);
    TexCoord0 = TexCoord;
}
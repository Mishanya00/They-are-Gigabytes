#version 330 core

layout (location = 0) in vec3 Position;
layout (location = 1) in vec2 TexCoord;
layout (location = 2) in vec3 Normal;

uniform mat4 World;
uniform mat4 Projection;
uniform mat4 View;

uniform int gRenderMode; // 0 - usual, 1 - selected, 2 - Partial vertices 

out vec2 TexCoord0;
out vec3 Normal0;
flat out int RenderMode;

void main()
{   
    gl_Position = Projection * View * World * vec4(Position, 1.0);
    TexCoord0 = TexCoord;
    Normal0 = Normal;
    RenderMode = gRenderMode;
}
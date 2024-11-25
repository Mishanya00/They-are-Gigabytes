#version 330 core

layout(location = 0) in vec3 position;

uniform vec4 BtnColor;

out vec4 color;

void main() {
    float koef = 1.0f;
	vec3 new_pos = position;
	new_pos.x = ( (koef * 2 * new_pos.x) / 1920) - 1.0f;
	new_pos.y = ( (koef * 2 * new_pos.y) / 1080) - 1.0f;
	
    gl_Position = vec4(new_pos, 1.0);
	color = BtnColor;
}
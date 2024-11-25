#version 330 core

in vec4 color;
out vec4 FragColor;

void main() {

    FragColor = color;
    //FragColor = vec4(0.0f, 1.0f, 1.0f, 0.0f);
}
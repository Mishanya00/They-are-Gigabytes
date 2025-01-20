#version 330 core

layout(location = 0) in vec3 aPos;             
layout(location = 1) in vec2 aTexCoord;   
layout(location = 2) in vec3 aNormal; 

out vec3 FragPos;                          
out vec3 Normal;                          
out vec2 TexCoords;                       

uniform mat4 u_ModelMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjectionMatrix;

void main() {
    
    mat4 u_ModelViewMatrix = u_ViewMatrix * u_ModelMatrix;
    
    gl_Position = u_ProjectionMatrix * u_ModelViewMatrix * vec4(aPos, 1.0);

   
    FragPos = vec3(u_ModelViewMatrix * vec4(aPos, 1.0));

    
    Normal = normalize(transpose(inverse(mat3(u_ModelMatrix))) * aNormal);


    
    TexCoords = aTexCoord;
}
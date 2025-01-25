#version 330 core

#define NOISE_EFFECT 1
#define VIGNETTE_EFFECT 2
#define COLOR_GRADING_EFFECT 4
#define SHININESS_EFFECT 16

in vec2 TexCoord0;
in vec3 Normal0;
in vec3 WorldPos0;
flat in int RenderMode;

out vec4 FragColor;

struct DirectionalLight
{
    vec3 Color;
    float AmbientIntensity;
    float DiffuseIntensity;
    vec3 Direction;
};

struct Material
{
    vec3 AmbientColor;
    vec3 DiffuseColor;
};

uniform int gEffectFlags;
uniform DirectionalLight gDirectionalLight;
uniform Material gMaterial;
uniform sampler2D gSampler;
uniform mat4 View;

float random(vec2 st) {
    return fract(sin(dot(st.xy, vec2(12.9898, 78.233))) * 43758.5453);
}

void main()
{
    vec4 AmbientColor = vec4(gDirectionalLight.Color, 1.0f) *
                        gDirectionalLight.AmbientIntensity *
                        vec4(gMaterial.AmbientColor, 1.0f);

    float DiffuseFactor = dot(normalize(Normal0), -gDirectionalLight.Direction);

    vec4 DiffuseColor = vec4(0, 0, 0, 0);

    if (DiffuseFactor > 0) {
        DiffuseColor = vec4(gDirectionalLight.Color, 1.0f) *
                       gDirectionalLight.DiffuseIntensity *
                       vec4(gMaterial.DiffuseColor, 1.0f) *
                       DiffuseFactor;
    }

    FragColor = texture(gSampler, TexCoord0.xy);

    if ( (gEffectFlags & SHININESS_EFFECT) != 0) {
        mat4 invView = inverse(View);

        vec3 cameraPos = invView[3].xyz;
        vec3 viewDir = normalize(cameraPos - WorldPos0); // Направление взгляда
        vec3 reflectDir = reflect(-gDirectionalLight.Direction, Normal0);

        float specularFactor = pow(max(dot(viewDir, reflectDir), 0.0), 32.0); // Shininess level (32 — is "shininess")

        vec4 specular = vec4(gDirectionalLight.Color * specularFactor, 1.0);

        FragColor.xyz *= (AmbientColor + DiffuseColor + specular).xyz;
    }
    else {
        FragColor.xyz *= (AmbientColor + DiffuseColor).xyz;
    }

    vec4 color = FragColor;

    if (RenderMode == 1) {
        color = mix(color, vec4(0.0, 1.0, 0.0, 1.0), 0.5);
    }
    
    else if (RenderMode == 2) {
        float randomValue = fract(sin(dot(gl_FragCoord.xy, vec2(12.9898, 78.233))) * 43758.5453);
        if (randomValue < 0.9) {
            discard;
        }
        color = mix(color, vec4(0.0, 0.0, 1.0, 1.0), 0.5);
    }
    
    if ( (gEffectFlags & VIGNETTE_EFFECT) != 0) {
        vec2 uv = TexCoord0 * 2.0 - 1.0;
        float vignette = 1.0 - dot(uv, uv) * 0.5;
        color = color * vignette; 
    }
    
    if ( (gEffectFlags & NOISE_EFFECT) != 0) {
        vec2 uv = TexCoord0;
        float grain = random(uv * 100.0) * 0.1; // Генерация зернистости
        color = color + vec4(grain); // Добавьте зернистость
    }

    if ( (gEffectFlags & COLOR_GRADING_EFFECT) != 0) {
        color.rgb = pow(color.rgb, vec3(1.2));
    }

    FragColor = color;
}

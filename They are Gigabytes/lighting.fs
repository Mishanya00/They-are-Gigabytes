#version 330 core

#define NOISE_EFFECT 1
#define VIGNETTE_EFFECT 2
#define COLOR_GRADING_EFFECT 4

in vec2 TexCoord0;
in vec3 Normal0;
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
    FragColor.xyz *= (AmbientColor + DiffuseColor).xyz;

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

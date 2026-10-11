#version 120

varying vec2 v_texCoord;

uniform sampler2D u_textureFrom;
uniform sampler2D u_textureTo;

uniform vec2 u_center;
uniform float u_elapsedTime;
uniform float u_aspectRatio;
uniform int u_isWaveActive;

const float WAVE_SPEED = 0.5;
const float WAVE_WIDTH = 0.04;

float GetDistanceToCenter(vec2 uv)
{
    vec2 delta = uv - u_center;
    delta.x *= u_aspectRatio;

    return length(delta);
}

float GetWaveRadius()
{
    return WAVE_SPEED * u_elapsedTime;
}

vec2 DistortUv(vec2 uv, float distanceToCenter, float radius)
{
    float distanceToRing = abs(distanceToCenter - radius);

    float intensity = 1.0 - smoothstep(
        0.0,
        WAVE_WIDTH,
        distanceToRing
    );

    vec2 direction = uv - u_center;

    return uv + direction * intensity;
}

float GetTransition(float distanceToCenter, float radius)
{
    return 1.0 - smoothstep(
        radius - WAVE_WIDTH,
        radius + WAVE_WIDTH,
        distanceToCenter
    );
}

void main()
{
    vec2 uv = v_texCoord;
    float transition = 0.0;

    if (u_isWaveActive == 1)
    {
        float distanceToCenter = GetDistanceToCenter(uv);
        float radius = GetWaveRadius();

        uv = DistortUv(uv, distanceToCenter, radius);
        transition = GetTransition(distanceToCenter, radius);
    }

    vec4 colorFrom = texture2D(u_textureFrom, uv);
    vec4 colorTo = texture2D(u_textureTo, uv);

    gl_FragColor = mix(colorFrom, colorTo, transition);
}
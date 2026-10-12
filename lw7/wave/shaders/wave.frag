#version 120

varying vec2 v_texCoord;

uniform sampler2D u_textureFrom;
uniform sampler2D u_textureTo;

uniform vec2 u_center;
uniform float u_elapsedTime;
uniform float u_aspectRatio;
uniform int u_isWaveActive;

const float WAVE_SPEED = 0.5;
const float WAVE_INITIAL_WIDTH = 0.05;
const float WAVE_WIDTH_GROWTH = 0.3;
const float WAVE_FREQUENCY = 50.0;
const float WAVE_ATTENUATION = 6.0;

const float FADE_IN_WIDTH_PERCENTAGE = 0.2;

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

float GetWaveWidth()
{
    return WAVE_INITIAL_WIDTH + WAVE_WIDTH_GROWTH * u_elapsedTime;
}

float GetWaveEnvelope(float distanceBehindFront, float width)
{
    float fadeInWidth = width * FADE_IN_WIDTH_PERCENTAGE;

    float fadeIn = smoothstep(
        0.0,
        fadeInWidth,
        distanceBehindFront
    );

    float fadeOut = 1.0 - smoothstep(
        fadeInWidth,
        width,
        distanceBehindFront
    );

    return fadeIn * fadeOut;
}

float GetWaveOscillation(float distanceBehindFront)
{
    float phase = distanceBehindFront * WAVE_FREQUENCY;

    return sin(phase);
}

float GetWaveAttenuation(float distanceBehindFront)
{
    return exp(-WAVE_ATTENUATION * max(distanceBehindFront, 0.0));
}

vec2 DistortUv(vec2 uv, float distanceToCenter, float radius, float width)
{
    float distanceBehindFront = radius - distanceToCenter;

    float envelope = GetWaveEnvelope(distanceBehindFront, width);
    float oscillation = GetWaveOscillation(distanceBehindFront);
    float attenuation = GetWaveAttenuation(distanceBehindFront);

    float displacement = envelope * attenuation * oscillation;

    vec2 direction = uv - u_center;

    return uv + direction * displacement;
}

float GetTransition(float distanceToCenter, float radius, float width)
{
    return 1.0 - smoothstep(
        radius - width,
        radius + width,
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
        float width = GetWaveWidth();

        uv = DistortUv(uv, distanceToCenter, radius, width);
        transition = GetTransition(distanceToCenter, radius, width);
    }

    vec4 colorFrom = texture2D(u_textureFrom, uv);
    vec4 colorTo = texture2D(u_textureTo, uv);

    gl_FragColor = mix(colorFrom, colorTo, transition);
}
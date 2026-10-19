#version 120

varying vec2 v_uv;

uniform vec3 u_backgroundColor;
uniform vec3 u_ringColor;
uniform float u_innerRadius;
uniform float u_outerRadius;
uniform float u_viewportAspectRatio;
uniform vec2 u_center;

float GetDistanceFromCenter(vec2 uv)
{
    vec2 offset = uv - u_center;

    offset.x *= u_viewportAspectRatio;

    float fitScale = max(1.0, 1.0 / u_viewportAspectRatio);
    offset *= fitScale;

    return length(offset);
}

void main()
{
    float distanceFromCenter = GetDistanceFromCenter(v_uv);

    vec3 color = u_backgroundColor;

    if (distanceFromCenter >= u_innerRadius &&
        distanceFromCenter <= u_outerRadius)
    {
        color = u_ringColor;
    }

    gl_FragColor = vec4(color, 1.0);
}
#version 120

varying vec2 v_texCoord;

uniform float u_time;

void main()
{
    float value = 0.5 + 0.5 * sin(u_time);

    gl_FragColor = vec4(value, 0.0, 0.0, 1.0);
}
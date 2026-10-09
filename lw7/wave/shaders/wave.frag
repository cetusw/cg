#version 120

varying vec2 v_texCoord;

uniform sampler2D u_texture;
uniform float u_time;

void main()
{
    vec2 uv = v_texCoord;

    float amplitude = 0.02;
    float frequency = 30.0;
    float speed = 3.0;

    float offset = amplitude * sin(
        frequency * uv.y - speed * u_time
    );

    uv.x += offset;

    gl_FragColor = texture2D(u_texture, uv);
}
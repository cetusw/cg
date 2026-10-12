
#version 120

uniform float u_morph;

void main()
{
    float x = gl_Vertex.x;
    float y = gl_Vertex.y;

    float z = x * x + (1.0 - 2.0 * u_morph) * y * y;

    vec3 position = vec3(x, y, z);

    gl_Position = gl_ModelViewProjectionMatrix * vec4(position, 1.0);
}

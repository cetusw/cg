#version 120

uniform sampler2D image;
uniform vec2 texelOffset;

varying vec2 v_texCoord;

const int BLUR_RADIUS = 4;
const float SIGMA = 2.0;

float GaussianWeight(float distance)
{
    return exp(-(distance * distance) / (2.0 * SIGMA * SIGMA));
}

void main()
{
    vec4 color = vec4(0.0);
    float totalWeight = 0.0;

    for (int i = -BLUR_RADIUS; i <= BLUR_RADIUS; ++i)
    {
        float weight = GaussianWeight(float(i));

        vec2 uv = v_texCoord + texelOffset * float(i);

        color += texture2D(image, uv) * weight;
        totalWeight += weight;
    }

    gl_FragColor = color / totalWeight;
}
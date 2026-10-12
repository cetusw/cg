#version 120

uniform sampler2D currentImage;
uniform sampler2D previousImage;
uniform float previousDecay;

varying vec2 v_texCoord;

void main()
{
	vec4 currentColor = texture2D(currentImage, v_texCoord);
    vec4 previousColor = texture2D(previousImage, v_texCoord);

    gl_FragColor = max(currentColor, previousColor * previousDecay);
}

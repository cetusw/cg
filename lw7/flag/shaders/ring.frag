#version 120

varying vec2 v_uv;

const vec3 BackgroundColor = vec3(0.0, 0.0, 0.0);
const vec3 RingColor = vec3(1.0, 0.82, 0.0);
const float InnerRadius = 0.25;
const float OuterRadius = 0.40;
const float ViewportAspectRatio = 2.0;

void main()
{
	vec2 offsetFromCenter = v_uv - vec2(0.5);
	offsetFromCenter.x *= ViewportAspectRatio;
	float distanceFromCenter = length(offsetFromCenter);
	vec3 color = BackgroundColor;

	if (distanceFromCenter >= InnerRadius && distanceFromCenter <= OuterRadius)
	{
		color = RingColor;
	}

	gl_FragColor = vec4(color, 1.0);
}

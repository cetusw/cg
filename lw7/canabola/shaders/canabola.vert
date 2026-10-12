#version 120

void main()
{
	float x = gl_Vertex.x;
	float radius = (1.0 + sin(x)) * (1.0 + 0.9 * cos(8.0 * x))
		* (1.0 + 0.1 * cos(24.0 * x)) * (0.5 + 0.05 * cos(140.0 * x));

	vec3 position = vec3(radius * cos(x), radius * sin(x), gl_Vertex.z);

	gl_Position = gl_ModelViewProjectionMatrix * vec4(position, 1.0);
}

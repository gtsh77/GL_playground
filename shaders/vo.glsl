#version 330

in vec3 pos;
uniform mat4 view, proj;

void main()
{
	gl_Position = view * proj * vec4(pos, 1.0);
} 
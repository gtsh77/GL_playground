#version 330

in vec3 vp;
uniform mat4 view, proj;

void main()
{
	gl_Position = view * proj * vec4(vp, 1.0);
}

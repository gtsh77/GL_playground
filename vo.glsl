#version 330

in vec3 vp;
uniform mat4 matrix;

void main()
{
	gl_Position = matrix * vec4(vp, 1.0);
}

#version 330

in vec3 pos_vb;
in vec3 color_vb;
uniform mat4 PVM;

out vec3 color;

void main()
{
	color = color_vb;
	gl_Position = PVM * vec4(pos_vb, 1.0);
}
#version 330

in vec3 pos_vb;
in vec3 color_vb;
uniform mat4 MVP;

out vec3 color;

void main()
{
	color = color_vb;
	gl_Position = MVP * vec4(pos_vb, 1.0);
}
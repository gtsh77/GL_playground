#version 300

in vec3 pos_vb;
in vec3 color_vb;
uniform mat4 view, proj;

out vec3 color;

void main()
{
	color = color_vb;
	gl_Position = vec4(pos_vb, 1.0);
}
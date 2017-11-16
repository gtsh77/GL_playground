#version 330

in vec3 color;
out vec4 cur_color;

void main()
{
	cur_color = vec4(color, 1.0);
}

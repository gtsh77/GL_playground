void drawTriangle(void)
{
	//triangle
	float points[] = {
		0.0f,  0.5f,  0.0f,
		0.5f, -0.5f,  0.0f,
		-0.5f, -0.5f,  0.0f
	};

	//vertex buffer
	glGenBuffers(1, &vb);
	glBindBuffer(GL_ARRAY_BUFFER, vb);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

	//vertex array (store pointers to our vbs)
	glGenVertexArrays(1, &va);
	glBindVertexArray(va);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vb);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	//tmp hardcoded shaders
	const char *vertex_shader =
	"#version 330\n" //330 for gl3.3, 150 for gl3.2, 400 for gl4+
	"in vec3 vp;"
	"void main() {"
	"  gl_Position = vec4(vp.x, vp.y, vp.z, 1.0);"
	"}";

	const char *fragment_shader =
	"#version 330\n"
	"out vec4 frag_colour;"
	"void main() {"
	"  frag_colour = vec4(0.7, 0.0, 0.0, 1.0);"
	"}";

	//compile shaders
	vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader, NULL);
	glCompileShader(vs);
	fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, NULL);
	glCompileShader(fs);

	//combine compiled shader objects into single executable GPU prog
	GLuint shader_programme = glCreateProgram();
	glAttachShader(shader_programme, fs);
	glAttachShader(shader_programme, vs);
	glLinkProgram(shader_programme);

	//draw loop
	while(!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.8f,0.8f,0.8f,1.0f);
		glUseProgram(shader_programme);
		glBindVertexArray(va);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	return;
}
#include "lib.c"

extern void drawTriangle(void)
{
	//triangle
	float points[] = 
	{
		0.0f,  0.5f,  0.0f,
		0.5f, -0.5f,  0.0f,
		-0.5f, -0.5f,  0.0f
	};
	//translation matrix
	// float T[] =
	// {
	// 	1.0f,0.0f,0.0f,0.0f,
	// 	0.0f,1.0f,0.0f,0.0f,
	// 	0.0f,0.0f,1.0f,0.0f,
	// 	0.5f,0.0f,0.0f,1.0f
	// };
	//scale matrix
	float T[] =
	{
		2.0f,0.0f,0.0f,0.0f,
		0.0f,2.0f,0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,
		0.0f,0.0f,0.0f,1.0f
	};
	//compile debug
	int gsi_params;
	//load shaders from files
	const char *vertex_shader = readFile("vo.glsl");
	const char *fragment_shader = readFile("frag.glsl");	

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

	if(!vertex_shader || !fragment_shader)
	{
		printf("not all shaders are loaded\n");
		return;
	}

	// const char *fragment_shader =
	// "#version 330\n"
	// "out vec4 frag_colour;"
	// "void main() {"
	// "  frag_colour = vec4(0.7, 0.0, 0.0, 1.0);"
	// "}";

	//compile shaders
	vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader, NULL);
	glCompileShader(vs);
	gsi_params = -1;
	glGetShaderiv(vs,GL_COMPILE_STATUS, &gsi_params);
	if(GL_TRUE != gsi_params)
	{
		printf("shader compile error:\n");
		debugSC(vs);
	}
	fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, NULL);
	glCompileShader(fs);
	gsi_params = -1;
	glGetShaderiv(vs,GL_COMPILE_STATUS, &gsi_params);
	if(GL_TRUE != gsi_params)
	{
		printf("shader compile error:\n");
		debugSC(fs);
	}
	//combine compiled shader objects into single executable GPU prog
	GLuint shader_programme = glCreateProgram();
	glAttachShader(shader_programme, fs);
	glAttachShader(shader_programme, vs);
	glLinkProgram(shader_programme);

	//remember about T-matrix
	int tLoc = glGetUniformLocation(shader_programme,"matrix");
	glUseProgram(shader_programme);
	glUniformMatrix4fv(tLoc,1,GL_FALSE,T);

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

uint64_t getCycles(void)
{
	uint64_t lo,hi;
	__asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
	return ((uint64_t)hi << 32) | lo;
}
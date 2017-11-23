#include "lib.c"
#include "mat.c"

extern void drawTriangle(void)
{
	//triangle
	float tr_points[] = 
	{
		0.0f,  0.5f,  0.0f,
		0.5f, -0.5f,  0.0f,
		-0.5f, -0.5f,  0.0f
	};
	//color
	float tr_color[] = 
	{
		1.0f,  0.0f,  0.0f,
		0.0f,  0.0f,  0.0f,
		0.0f,  0.0f,  0.0f
	};

	//compile debug
	int gsi_params;
	//load shaders from files
	const char *vertex_shader = readFile("shaders/vo.glsl");
	const char *fragment_shader = readFile("shaders/frag.glsl");	

	if(!vertex_shader || !fragment_shader)
	{
		printf("not all shaders are loaded\n");
		return;
	}	

	//vertex buffer tr_points
	glGenBuffers(1, &tr_vb);
	glBindBuffer(GL_ARRAY_BUFFER, tr_vb);
	glBufferData(GL_ARRAY_BUFFER, sizeof(tr_points), tr_points, GL_STATIC_DRAW);

	//vertex buffer tr_colors
	glGenBuffers(1, &tr_c_vb);
	glBindBuffer(GL_ARRAY_BUFFER, tr_c_vb);
	glBufferData(GL_ARRAY_BUFFER, sizeof(tr_color), tr_color, GL_STATIC_DRAW);

	//vertex array (store pointers to our vbs)
	glGenVertexArrays(1, &va);
	glBindVertexArray(va);
	glBindBuffer(GL_ARRAY_BUFFER, tr_vb);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, tr_c_vb);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	//enable
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

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
	GLuint shader_bin = glCreateProgram();
	glAttachShader(shader_bin, fs);
	glAttachShader(shader_bin, vs);

	//binds for gl 3.2 second vb
	glBindAttribLocation(shader_bin, 0, "pos_vb");
	glBindAttribLocation(shader_bin, 1, "color_vb");
	//cr link
	glLinkProgram(shader_bin);

	//C++ GLM matrix calc test

	//pepspective
	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), (float)WW/(float)WH,0.1f,100.0f);

	//camera
	glm::mat4 View = glm::lookAt(
	    glm::vec3(4,3,3), // Camera is at (4,3,3), in World Space
	    glm::vec3(0,0,0), // and looks at the origin
	    glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
	    );
	  
	//model
	glm::mat4 Model = glm::mat4(1.0f);
	//PVM
	glm::mat4 PVM = Projection * View * Model;

	//C++ GLM matrix calc test	

	int pvmI = glGetUniformLocation(shader_bin,"PVM");
	// int pLoc = glGetUniformLocation(shader_bin,"proj");
	glUseProgram(shader_bin);
	glUniformMatrix4fv(pvmI,1,GL_FALSE,&PVM[0][0]);
	// glUniformMatrix4fv(pLoc,1,GL_FALSE,(float *)proj_m);111

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);

	//draw loop
	while(!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.8f,0.8f,0.8f,1.0f);
		glViewport(0,0,WW,WH);
		glUseProgram(shader_bin);
		glBindVertexArray(va);
		glDrawArrays(GL_TRIANGLES,0,3);
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
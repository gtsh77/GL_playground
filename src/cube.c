extern void cookCube(void)
{
	float cube_model[] =
	{
	    -1.0f,-1.0f,-1.0f, // triangle 1 : begin
	    -1.0f,-1.0f, 1.0f,
	    -1.0f, 1.0f, 1.0f, // triangle 1 : end
	    1.0f, 1.0f,-1.0f, // triangle 2 : begin
	    -1.0f,-1.0f,-1.0f,
	    -1.0f, 1.0f,-1.0f, // triangle 2 : end
	    1.0f,-1.0f, 1.0f,
	    -1.0f,-1.0f,-1.0f,
	    1.0f,-1.0f,-1.0f,
	    1.0f, 1.0f,-1.0f,
	    1.0f,-1.0f,-1.0f,
	    -1.0f,-1.0f,-1.0f,
	    -1.0f,-1.0f,-1.0f,
	    -1.0f, 1.0f, 1.0f,
	    -1.0f, 1.0f,-1.0f,
	    1.0f,-1.0f, 1.0f,
	    -1.0f,-1.0f, 1.0f,
	    -1.0f,-1.0f,-1.0f,
	    -1.0f, 1.0f, 1.0f,
	    -1.0f,-1.0f, 1.0f,
	    1.0f,-1.0f, 1.0f,
	    1.0f, 1.0f, 1.0f,
	    1.0f,-1.0f,-1.0f,
	    1.0f, 1.0f,-1.0f,
	    1.0f,-1.0f,-1.0f,
	    1.0f, 1.0f, 1.0f,
	    1.0f,-1.0f, 1.0f,
	    1.0f, 1.0f, 1.0f,
	    1.0f, 1.0f,-1.0f,
	    -1.0f, 1.0f,-1.0f,
	    1.0f, 1.0f, 1.0f,
	    -1.0f, 1.0f,-1.0f,
	    -1.0f, 1.0f, 1.0f,
	    1.0f, 1.0f, 1.0f,
	    -1.0f, 1.0f, 1.0f,
	    1.0f,-1.0f, 1.0f		
	};

	float cubes_part_color[] = 
	{
		
	    1.0f,  0.0f,  0.0f,		
	    1.0f,  0.0f,  0.0f,		
	    1.0f,  0.0f,  0.0f,		
	    1.0f,  0.0f,  0.0f,		
	    1.0f,  0.0f,  0.0f,		
	    1.0f,  0.0f,  0.0f,		
	    1.0f,  0.0f,  0.0f,		
	    1.0f,  0.0f,  0.0f,		
	    1.0f,  0.0f,  0.0f,		
	    1.0f,  0.0f,  0.0f,		
	    1.0f,  0.0f,  0.0f,		
	    1.0f,  0.0f,  0.0f,		
	    1.0f,  0.0f,  0.0f,		
	    1.0f,  0.0f,  0.0f,		
	    1.0f,  0.0f,  0.0f,		
	    1.0f,  0.0f,  0.0f,		
	    1.0f,  0.0f,  0.0f,		
	    1.0f,  0.0f,  0.0f,		
	    1.0f,  0.0f,  0.0f,		
	    1.0f,  0.0f,  0.0f,		
	    1.0f,  0.0f,  0.0f,		
	    1.0f,  0.0f,  0.0f,		
	    1.0f,  0.0f,  0.0f,		
	    1.0f,  0.0f,  0.0f,		
	    1.0f,  0.0f,  0.0f,		
	    1.0f,  0.0f,  0.0f,		
	    1.0f,  0.0f,  0.0f,		
	    1.0f,  0.0f,  0.0f,		
	    1.0f,  0.0f,  0.0f,		
	    1.0f,  0.0f,  0.0f,		
	    1.0f,  0.0f,  0.0f,		
	    1.0f,  0.0f,  0.0f,		
	    1.0f,  0.0f,  0.0f,		
	    1.0f,  0.0f,  0.0f,
	    1.0f,  0.0f,  0.0f,
	    1.0f,  0.0f,  0.0f
	};

	//vertex
	glGenBuffers(1, &tr_vb);
	glBindBuffer(GL_ARRAY_BUFFER, tr_vb);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_model), cube_model, GL_STATIC_DRAW);

	glGenBuffers(1, &tr_c_vb);
	glBindBuffer(GL_ARRAY_BUFFER, tr_c_vb);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubes_part_color), cubes_part_color, GL_STATIC_DRAW);

	glGenVertexArrays(1, &va);
	glBindVertexArray(va);
	glBindBuffer(GL_ARRAY_BUFFER, tr_vb);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, tr_c_vb);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	//shaders
	int gsi_params;
	const char *vertex_shader = readFile("shaders/vo.glsl");
	const char *fragment_shader = readFile("shaders/frag.glsl");
	if(!vertex_shader || !fragment_shader)
	{
		printf("not all shaders are loaded\n");
		return;
	}

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

	GLuint shader_bin = glCreateProgram();
	glAttachShader(shader_bin, fs);
	glAttachShader(shader_bin, vs);

	glBindAttribLocation(shader_bin, 0, "pos_vb");
	glBindAttribLocation(shader_bin, 1, "color_vb");
	glLinkProgram(shader_bin);

	//GLM
	glm::mat4 Projection = glm::perspective(glm::radians(65.0f), (float)WW/(float)WH,0.1f,100.0f);

	//new code
	gsl_matrix *Pro = m_new(4,4);
	glmPerspective(RAD(65.0f),(double)WW/(double)WH,0.1f,100.0f,Pro);

	//m_print(Pro,4,4);

	//test v-len
	double vector[] = {4,3,3};
	//printf("%f\n",getVectorLength(vector,3));

	//test normalize
	double *normal;
	normalize(vector, 3, normal);
	
	//end of new

	glm::mat4 View = glm::lookAt(
	    glm::vec3(4,3,3), // Camera is at (4,3,3), in World Space
	    glm::vec3(0,0,0), // and looks at the origin 
	    glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
	    );

	glm::mat4 Model = glm::mat4(1.0f);
	glm::mat4 MVP = Projection * View * Model;

	int MVPI = glGetUniformLocation(shader_bin,"MVP");
	glUseProgram(shader_bin);
	glUniformMatrix4fv(MVPI,1,GL_FALSE,&MVP[0][0]);

	//draw loop
	while(!glfwWindowShouldClose(window)) {

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.8f,0.8f,0.8f,1.0f);
		glViewport(0,0,WW,WH);
		glUseProgram(shader_bin);
		glBindVertexArray(va);
		glDrawArrays(GL_TRIANGLE_STRIP,0,12*3);
		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	return;
}
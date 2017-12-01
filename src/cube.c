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

	//new code
	//timer[2] = getCycles();

	gsl_matrix *ProjectionNew = m_new(4,4);
	glmPerspective(RAD(65.0f),(double)WW/(double)WH,0.1f,100.0f,ProjectionNew);

	gsl_matrix *ViewNew = m_new(4,4);
	double eye[] = {4,3,3};
	double center[] = {0,0,0};
	double up[] = {0,1,0};
	glmLookAt(eye,center,up,ViewNew);

	gsl_matrix *ModelNew = m_new_diag(4);

	//MVP
	gsl_matrix *MV = m_new(4,4);
	gsl_matrix *MVP = m_new(4,4);
	
	m_mul(ModelNew,ViewNew,MV);
	m_mul(MV,ProjectionNew,MVP);
	float MVPA[16];
	m_array(MVP,4,4,MVPA);

	//timer[3] = getCycles();

	//printf("C GSL: %.9f (%d cycles)\n",(double)(timer[3]-timer[2])/3.5e9,timer[3]-timer[2]);
	//m_print(MVP,4,4);



	//GLM C++ debugger
	#if 0

	timer[0] = getCycles();

	glm::mat4 View = glm::lookAt(
	    glm::vec3(4,3,3), // Camera is at (4,3,3), in World Space
	    glm::vec3(0,0,0), // and looks at the origin 
	    glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
	    );	

	glm::mat4 Projection = glm::perspective(glm::radians(65.0f), (float)WW/(float)WH,0.1f,100.0f);
	glm::mat4 Model = glm::mat4(1.0f);
	glm::mat4 MVP2 = Projection * View * Model;

	timer[1] = getCycles();

	printf("C++ GLM: %.9f (%d cycles)\n",(double)(timer[1]-timer[0])/3.5e9,timer[1]-timer[0]);

	const float *pSource = (const float*)glm::value_ptr(MVP2);
	//const float *pSource = (const float*)MVPA;
	printf("\n\n%f\n",(float)pSource[0]);
	printf("%f\n",(float)pSource[1]);
	printf("%f\n",(float)pSource[2]);
	printf("%f\n",(float)pSource[3]);

	printf("\n\n%f\n",(float)pSource[4]);
	printf("%f\n",(float)pSource[5]);
	printf("%f\n",(float)pSource[6]);
	printf("%f\n",(float)pSource[7]);

	printf("\n\n%f\n",(float)pSource[8]);
	printf("%f\n",(float)pSource[9]);
	printf("%f\n",(float)pSource[10]);
	printf("%f\n",(float)pSource[11]);

	printf("\n\n%f\n",(float)pSource[12]);
	printf("%f\n",(float)pSource[13]);
	printf("%f\n",(float)pSource[14]);
	printf("%f\n",(float)pSource[15]);	

	#endif

	int MVPI = glGetUniformLocation(shader_bin,"MVP");
	glUseProgram(shader_bin);
	glUniformMatrix4fv(MVPI,1,GL_FALSE,MVPA);

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
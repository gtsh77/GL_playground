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
	    0.583f,  0.771f,  0.014f,
	    0.609f,  0.115f,  0.436f,
	    0.327f,  0.483f,  0.844f,
	    0.822f,  0.569f,  0.201f,
	    0.435f,  0.602f,  0.223f,
	    0.310f,  0.747f,  0.185f,
	    0.597f,  0.770f,  0.761f,
	    0.559f,  0.436f,  0.730f,
	    0.359f,  0.583f,  0.152f,
	    0.483f,  0.596f,  0.789f,
	    0.559f,  0.861f,  0.639f,
	    0.195f,  0.548f,  0.859f,
	    0.014f,  0.184f,  0.576f,
	    0.771f,  0.328f,  0.970f,
	    0.406f,  0.615f,  0.116f,
	    0.676f,  0.977f,  0.133f,
	    0.971f,  0.572f,  0.833f,
	    0.140f,  0.616f,  0.489f,
	    0.997f,  0.513f,  0.064f,
	    0.945f,  0.719f,  0.592f,
	    0.543f,  0.021f,  0.978f,
	    0.279f,  0.317f,  0.505f,
	    0.167f,  0.620f,  0.077f,
	    0.347f,  0.857f,  0.137f,
	    0.055f,  0.953f,  0.042f,
	    0.714f,  0.505f,  0.345f,
	    0.783f,  0.290f,  0.734f,
	    0.722f,  0.645f,  0.174f,
	    0.302f,  0.455f,  0.848f,
	    0.225f,  0.587f,  0.040f,
	    0.517f,  0.713f,  0.338f,
	    0.053f,  0.959f,  0.120f,
	    0.393f,  0.621f,  0.362f,
	    0.673f,  0.211f,  0.457f,
	    0.820f,  0.883f,  0.371f,
	    0.982f,  0.099f,  0.879f
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
	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), (float)WW/(float)WH,0.1f,100.0f);

	//camera
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
		glDrawArrays(GL_TRIANGLES,0,12*3);
		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	return;
}
#include "lib.c"
#include "mat.c"

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
	float T[] =
	{
		1.0f,0.0f,0.0f,0.0f,
		0.0f,1.0f,0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,
		0.5f,0.0f,0.0f,1.0f
	};
	//scale matrix
	// float T[] =
	// {
	// 	2.0f,0.0f,0.0f,0.0f,
	// 	0.0f,2.0f,0.0f,0.0f,
	// 	0.0f,0.0f,1.0f,0.0f,
	// 	0.0f,0.0f,0.0f,1.0f
	// };
	//compile debug
	int gsi_params;
	//load shaders from files
	const char *vertex_shader = readFile("shaders/vo.glsl");
	const char *fragment_shader = readFile("shaders/frag.glsl");	

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

	//camera
	double mov_speed = 1.0f;
	double rot_speed = 10.0f;
	double cam_pos[] = {-0.0f, -0.0f, -2.0f};
	double cam_rot = -0.0f;

	gsl_matrix *CT = m_new_diag(4,4);
	m_setT(CT,cam_pos,1);
	printf("\nCT\n");
	m_print(CT,4,4);

	gsl_matrix *CR = m_new_diag(4,4);
	m_setRy(CR,cam_rot,1);
	printf("\nCR\n");
	m_print(CR,4,4);
	
	gsl_matrix *M = m_new(4,4);
	m_mul(CT,CR,M);
	printf("\nM\n");
	m_print(CT,4,4);
	
	double *view_m = m_array(CT,4,4);

	float near = 0.1f;
	float far = 100.0f;
	float fov = RAD(67.0f);
	float aspect = (float)WW/(float)WH;
	float range = tan(fov*0.5f)*near;
	float Sx = (2.0f*near)/(range*aspect+range*aspect);
	float Sy = near/range;
	float Sz = -(far + near)/(far - near);
	float Pz = -(2.0f*far*near)/(far-near);

	double proj_m[] = {
		Sx,0.0f,0.0f,0.0f,
		0.0f,Sy,0.0f,0.0f,	
		0.0f,0.0f,Sz,-1.0f,
		0.0f,0.0f,Pz,0.0f
	};

	//debug proj_M
	gsl_matrix_view PM = gsl_matrix_view_array(proj_m,4,4);

	printf("\nPM\n");
	m_print(&PM.matrix,4,4);
	//end of debug proj_M

	int vLoc = glGetUniformLocation(shader_programme,"view");
	int pLoc = glGetUniformLocation(shader_programme,"proj");
	glUseProgram(shader_programme);
	glUniformMatrix4fv(vLoc,1,GL_FALSE,(float *)view_m);
	glUniformMatrix4fv(pLoc,1,GL_FALSE,(float *)proj_m);

	printf("\n%d\n",vLoc);
	printf("\n%d\n",pLoc);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);	

	//draw loop
	while(!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.8f,0.8f,0.8f,1.0f);
		glViewport(0,0,WW,WH);
		glUseProgram(shader_programme);
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
#include "main.h"

GLFWwindow *window;

int main(void)
{
	glfwInit();
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow( WW, WH, "Tutorial 01", NULL, NULL);
	glfwMakeContextCurrent(window);
	
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	do
	{
		//...
	    glfwSwapBuffers(window);
	    glfwPollEvents();

	}
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
	glfwWindowShouldClose(window) == 0 );

	return 0;
}
#include "main.h"
#include "triangle.c"

GLFWwindow *window;
const GLubyte *renderer;
const GLubyte *version;
GLuint tr_vb, tr_c_vb, va, vs, fs;

int main() {
	glfwInit();

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(WW, WH, "Hello Triangle", NULL, NULL);
	glfwMakeContextCurrent(window);
	                              
	glewExperimental = GL_TRUE;
	glewInit();

	renderer = glGetString(GL_RENDERER);
	version = glGetString(GL_VERSION);
	printf("Renderer: %s\n", renderer);
	printf("OpenGL version supported %s\n", version);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	drawTriangle();

	glfwTerminate();
	return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define WW 640
#define WH 480

extern GLFWwindow *window;
extern GLuint vb;
extern GLuint va;
extern GLuint vs;
extern GLuint fs;

void drawTriangle(void);
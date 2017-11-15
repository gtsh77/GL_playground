#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <gsl/gsl_linalg.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define WW 640
#define WH 480

extern GLFWwindow *window;
extern GLuint vb;
extern GLuint va;
extern GLuint vs;
extern GLuint fs;

extern void drawTriangle(void);
extern uint64_t getCycles(void);
extern char * readFile(char *);
extern void debugSC(GLuint);
extern gsl_matrix * m4init(void);
extern void m_translate(gsl_matrix *, double *);
extern void m_print(gsl_matrix *, uint8_t, uint8_t);
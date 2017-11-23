#ifndef _H_MAIN
#define _H_MAIN

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <gsl/gsl_linalg.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define WW 640
#define WH 480
#define RAD(d) (d) * (M_PI/180)
#define ZEROCHK(i) ((i) == 0)?0:i

#include "lib.c"
#include "mat.c"

extern GLFWwindow *window;
extern GLuint tr_vb;
extern GLuint tr_c_vb;
extern GLuint va;
extern GLuint vs;
extern GLuint fs;
extern GLuint shader_bin;

extern void cookTriangle(void);
extern void cookCube(void);
extern uint64_t getCycles(void);
extern char * readFile(char *);
extern void debugSC(GLuint);

extern gsl_matrix * m_new_diag(uint32_t, uint32_t);
extern gsl_matrix * m_new(uint32_t, uint32_t);
extern void m_setT(gsl_matrix *, double, double, double, uint8_t);
extern void m_setRy(gsl_matrix *, double, uint8_t);
extern void m_mul(gsl_matrix *, gsl_matrix *, gsl_matrix *);
extern void m_print(gsl_matrix *, uint8_t, uint8_t);
extern double * m_array(gsl_matrix *, uint8_t, uint8_t);

#endif
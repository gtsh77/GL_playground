all: 
	gcc src/main.c -o main -lgsl -lm -lgslcblas -lglfw -lGL -lGLU -lGLEW

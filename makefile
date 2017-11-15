all: 
	gcc src/main.c -o main -lgsl -lgslcblas -lglfw -lGL -lGLU -lGLEW

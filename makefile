all: 
	gcc src/main.c -Wall -o main -lgsl -lm -lgslcblas -lglfw -lGL -lGLU -lGLEW
cpp:
	g++ src/main.c -Wall -o main -lgsl -lm -lgslcblas -lglfw -lGL -lGLU -lGLEW
debug:
	gcc src/main.c -Wall -o main -lgsl -lm -lgslcblas -lglfw -lGL -lGLU -lGLEW -gdwarf-2
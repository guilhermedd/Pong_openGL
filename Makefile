all:
	gcc pong.c Bar.c Cube.c -o myprogram.out -lGL -lGLU -lglut -lm -lglfw -lfreetype
	./myprogram.out

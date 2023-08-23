all:
	gcc pong.c Bar.c -o myprogram.out -lGL -lGLU -lglut -lm -lglfw
	./myprogram.out

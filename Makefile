all:
	gcc pong.c Pieces.c -o pong.out -lGL -lGLU -lglut -lm -lglfw -lfreetype
	./pong.out

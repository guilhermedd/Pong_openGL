all:
	gcc pong.c Pieces.c -o pong.out -lGL -lGLU -lglut -lm -lglfw -lfreetype -lSDL2 -lSDL2_mixer -lSOIL
	./pong.out

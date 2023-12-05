all:
	gcc pong.c Pieces.c -o pong.out -lGL -lGLU -lglut -lm  -lfreetype -lSDL2 -lSDL2_mixer -lSOIL
	./pong.out

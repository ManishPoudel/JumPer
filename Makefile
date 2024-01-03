all: compile run
compile:
	gcc sdlFuncs.c gameFuncs.c jumper.c -o ./build/jumper -lSDL2 -lSDL2_image -lm
run:
	./build/jumper

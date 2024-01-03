all: compile run
compile:
	gcc ./src/sdlFuncs.c ./src/gameFuncs.c ./src/jumper.c -o ./build/jumper -lSDL2 -lSDL2_image -lm
run:
	./build/jumper

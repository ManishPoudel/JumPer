all: compile run
compile:
	gcc ./src/sdlFuncs.c ./src/gameFuncs.c ./src/jumper.c -o ./build/jumper -lSDL2 -lSDL2_image -lSDL2_ttf -lm
run:
	./build/jumper

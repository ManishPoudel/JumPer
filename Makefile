all: compile run
compile:
	gcc jumper.c functions.c -o ./build/jumper -lSDL2 -lSDL2_image -lm
run:
	./build/jumper

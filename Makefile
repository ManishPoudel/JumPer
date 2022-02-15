all: compile run
compile:
	gcc jumper.c -o jumper -lSDL2 -lSDL2_image -lm
run:
	./jumper
	
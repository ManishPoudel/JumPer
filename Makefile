all:
	gcc jumper.c -o jumper -lSDL2 -lSDL2_image -lm
run:
	./jumper
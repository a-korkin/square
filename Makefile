build:
	gcc -Wall ./*.c -lSDL2 -o game
run:
	./game
clean:
	rm -rf ./game


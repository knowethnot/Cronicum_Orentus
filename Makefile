compile:
	clang++ -ggdb -std=gnu++11 -Wall -Werror *.cpp -o wavplayer -lSDL2

run:
	./wavplayer

valgrind:
	valgrind ./wavplayer

gdb:
	gdb ./wavplayer

clean:
	rm -f *.o wavplayer

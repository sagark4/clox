build/cloxc : build/cloxc.o
	gcc -std=c99 build/cloxc.o -o build/cloxc

build/cloxc.o : src/cloxc.c
	gcc -c src/cloxc.c -o build/cloxc.o

.PHONY : clean

clean :
	rm -f build/*

CC          := clang -std=c99
CFLAGS      := -g -Wall -Wextra -Werror

build/cloxc : build/cloxc.o build/asm.o build/value.o
	$(CC) build/cloxc.o build/asm.o build/value.o -o build/cloxc

build/cloxc.o : src/cloxc.c src/include/common.h src/include/asm.h src/include/value.h 
	$(CC) -c src/cloxc.c -o build/cloxc.o

build/asm.o : src/asm.c src/include/asm.h src/include/common.h src/include/dyn_arr.h src/include/value.h 
	$(CC) -c src/asm.c -o build/asm.o

build/value.o : src/value.c src/include/value.h src/include/common.h src/include/dyn_arr.h
	$(CC) -c src/value.c -o build/value.o

build/assembled : build/cloxc
	./build/cloxc
	mv asem.asm build/
	nasm -f elf64 -o build/asem.o build/asem.asm
	ld build/asem.o -lc -I /lib64/ld-linux-x86-64.so.2 -o build/assembled

.PHONY : clean

clean :
	rm -f build/*

test: 

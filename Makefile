build/cloxc : build/cloxc.o build/asm.o
	gcc -std=c99 build/cloxc.o build/asm.o -o build/cloxc

build/cloxc.o : src/cloxc.c src/include/common.h
	gcc -c src/cloxc.c -o build/cloxc.o

build/asm.o : src/asm.c src/include/asm.h src/include/common.h
	gcc -c src/asm.c -o build/asm.o

build/assembled : build/cloxc
	./build/cloxc
	mv asem.asm build/
	nasm -f elf64 -o build/asem.o build/asem.asm
	ld build/asem.o -lc -I /lib64/ld-linux-x86-64.so.2 -o build/assembled

.PHONY : clean

clean :
	rm -f build/*

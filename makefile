# CC = compiler
CC=gcc
#CFLAGS	= flags for compiler
CFLAGS=-c -Wall

.PHONY: clean

all: bin build build/a build/o bin/test.exe 

bin/test.exe: build/o/main.o build/o/ALU_CU.o build/a/MSC.a build/a/BC.a build/a/MRK.a
	$(CC) -o bin/test.exe  build/o/main.o build/o/ALU_CU.o -L. build/a/MSC.a build/a/BC.a build/a/MRK.a


build/a/MSC.a: build/o/MSC.o 
	ar cr build/a/MSC.a build/o/MSC.o

build/a/BC.a: build/o/BC.o build/o/View.o
	ar cr build/a/BC.a build/o/BC.o build/o/View.o

build/a/MRK.a: build/o/MRK.o 
	ar cr build/a/MRK.a build/o/MRK.o


build/o/main.o: main.c 
	$(CC) $(CFLAGS)  main.c -o build/o/main.o

build/o/MSC.o: src/mySimpleComputer.c 
	$(CC) $(CFLAGS) src/mySimpleComputer.c -o build/o/MSC.o

build/o/View.o: src/View.c 
	$(CC) $(CFLAGS) src/View.c -o build/o/View.o

build/o/BC.o: src/BigChar.c
	$(CC) $(CFLAGS) src/BigChar.c -o build/o/BC.o

build/o/MRK.o: src/MyReadKey.c
	$(CC) $(CFLAGS) src/MyReadKey.c -o build/o/MRK.o
build/o/ALU_CU.o: src/ALU_CU.c
	$(CC) $(CFLAGS) src/ALU_CU.c -o build/o/ALU_CU.o 

build:
	mkdir build 

build/o: 
	mkdir build/o

build/a:
	mkdir build/a

bin:
	mkdir bin 

clean:
	rm -rf build bin

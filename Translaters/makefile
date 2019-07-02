# CC = compiler
CC=gcc
#CFLAGS	= flags for compiler
CFLAGS=-c -Wall

all: sat sbt

sat: A.o
	$(CC) -Wall A.o -o sat -lm
sbt: B.o
	$(CC) -Wall B.o -o sbt 

A.o: A.c
	$(CC) $(CFLAGS) A.c 

B.o: B.c
	$(CC) $(CFLAGS) B.c 
clean:
	rm -rf *.o sat *.bin sbt as.txt

	

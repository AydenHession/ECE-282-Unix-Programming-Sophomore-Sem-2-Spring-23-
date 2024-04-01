#
# Makefile for Chapter 04
#
# Type  make    to compile all the programs
# in the chapter 
#
all: spwd.o
	gcc spwd.o -o spwd

clean:
	rm -rf spwd
	rm -rf *.o

spwd.o:
	gcc -c spwd.c

run: all

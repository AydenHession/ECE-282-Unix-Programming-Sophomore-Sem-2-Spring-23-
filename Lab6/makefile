all: labsix.o
	gcc labsix.o -o locker

labsix.o:
	gcc -c labsix.c

clean:
	rm -rf *.o
	rm -rf locker

run: all

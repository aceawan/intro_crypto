HEADERS = main.h
LIBS = -lgmp

default: main

main.o: main.c $(HEADERS)
	gcc -c main.c $(LIBS) -o main.o

main: main.o
	gcc main.o -o main

clean:
	-rm -f main.o
	-rm -f main
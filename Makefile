HEADERS = main.h
LINKING = -lgmp

default: main

program.o: main.c $(HEADERS)
    gcc $(LINKING) -c main.c -o main.o

program: program.o
    gcc main.o -o main

clean:
    -rm -f main.o
    -rm -f main
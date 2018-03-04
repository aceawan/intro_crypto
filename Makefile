CC=gcc
HEADERS = main.h
LIBS = -lgmp -lsodium
FLAGS =
OBJECTS = main.o
EXEC = main

default: $(EXEC)


%.o: %.c $(HEADERS)
	$(CC) $(FLAGS) -c $< -o $@

$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) $(LIBS) -o $@


run: $(EXEC)
	./$(EXEC)

clean:
	rm -f $(OBJECTS)
	rm -f $(EXEC)
	rm -f test.txt

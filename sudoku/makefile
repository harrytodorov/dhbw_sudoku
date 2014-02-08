CC = gcc -Wall
Objectfiles = main.o helpers.o

sudoku: $(Objectfiles)
	$(CC) -o $@ $^
$(Objectfiles): 
	$(CC) -c $<
main.o: main.c helpers.h
helpers.o: helpers.c	

all: clean sudoku run
	
clean:
	rm -f *.o sudoku
run: 
	./sudoku
CC = gcc -Wall
Objectfiles = main.o helpers.o backtracking.o

sudoku: $(Objectfiles)
	$(CC) -o $@ $^
$(Objectfiles): 
	$(CC) -c $<
main.o: main.c helpers.h
helpers.o: helpers.c backtracking.h
backtracking.o: backtracking.c

all: clean sudoku run
	
clean:
	rm -f *.o sudoku
run: 
	./sudoku
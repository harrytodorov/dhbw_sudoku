sudoku: main.o
	gcc -Wall -o $< $^
main.o: main.c
	gcc -Wall -c $<

all: clear sudoku run
	
clear:
	rm -f *.o sudoku
run: 
	./sudoku
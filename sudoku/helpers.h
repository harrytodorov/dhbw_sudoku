/* 
 * File:   helpers.h
 * Author: haralambitodorov
 *
 * Created on February 8, 2014, 3:04 PM
 */

#ifndef HELPERS_H
#define	HELPERS_H

#define START_POS_X 0
#define START_POS_Y 0
#define CLEAR printf("\033[2J")
#define POSITION(Ze, Sp) printf("\033[%d;%dH",Ze,Sp)

/**
 * 
 * read unbuffered characters from stdin     
 * sets the terminal into non-canonical mode, disables line buffering
 * 
 * @return ASCII Code of input
 */
int getch();

/**
 * The function takes 2 parameters column and row. 
 * Positions the cursor there and prints an empty Sudoku field.
 * 
 * 
 */
void printSudokuField();

/**
 * Prints the Sudoku welcome screen.
 */
void printWelcomeScreen();


#endif	/* HELPERS_H */


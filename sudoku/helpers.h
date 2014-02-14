/* 
 * File:   helpers.h
 * Author: haralambitodorov
 *
 * Created on February 8, 2014, 3:04 PM
 */

#ifndef HELPERS_H
#define	HELPERS_H

#include <stdbool.h>

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

/**
 * 
 * @param sudoku
 */
void printSudoku(int sudoku[9][9]);

void printDigitToField(int y, int x, int c, int sudoku[9][9]);

void loadSudokuFromFile(int sudoku[9][9]);

void generateSudoku(int grid[9][9]);

void startNewGame(int grid[9][9]);

void aboutSudoku();

void sudokuExit(void);

void removeRandomNumber(int grid[9][9], int complexity, bool notEditable[9][9]);

void printUserData(char name[20]);

void setArrayToZero(bool notEditable[9][9]);

void newGame(int grid[9][9], bool notEditable[9][9]);

void printUserData(char name[20]);

void copySudokuToSolved(int grid[9][9], int solvedSudoku[9][9]);

bool isSudokuSolved(int grid[9][9], int solvedSudoku[9][9]);

void notEditables(int sudoku[9][9], bool notEditables[9][9]);

void finalScreen();

void saveSudoku(int sudoku[9][9]);

#endif	/* HELPERS_H */


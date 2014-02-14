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

/**
 * Prints pressed key (number on the sudoku game field)
 * 
 * @param y The current column position of th cursor 
 * @param x The current column position of th cursor 
 * @param c The ASCII code of the number pressed
 * @param sudoku The sudoku matrix itself, where the number is also added
 */
void printDigitToField(int y, int x, int c, int sudoku[9][9]);

/**
 * Clears the command line view and let the user select a sudoku, he wants to play with.
 * Let the user enter a user name and starts the sudoku game. The solving algorithm has 
 * already solved the sudoku, if it could be solved, else it prints, that the sudoku is 
 * unsolvable.
 * 
 * @param sudoku Sudoku wihr some filled quadrats.
 */
void loadSudokuFromFile(int sudoku[9][9]);

/**
 * Backtracking algorithm, which solves the sudoku.
 * 
 * @param grid
 */
void generateSudoku(int grid[9][9]);

/**
 * Prints a small about the project.
 */
void aboutSudoku();

/**
 * Exit function
 */
void sudokuExit(void);

/**
 * Removes random numbers from solved sudoku
 * 
 * @param grid a completely solved sudoku
 * @param complexity the complexity level
 * @param notEditable Decides, which cells from sudoku are not editable(these, which are filled)
 */
void removeRandomNumber(int grid[9][9], int complexity, bool notEditable[9][9]);

/**
 * Print user data
 * @param name username
 */
void printUserData(char name[20]);

/**
 * Set the array for not editables cells to zero.
 * @param notEditable Unassigned boolean matrix
 */
void setArrayToZero(bool notEditable[9][9]);

/**
 * The function takes a solved sudoku and removes numbers on 
 * random principle. Then let the user enter a username and starts
 * a sudoku game.
 * 
 * @param grid a completely solved sudoku
 * @param notEditable which of the cells cannot be filled
 */

void newGame(int grid[9][9], bool notEditable[9][9]);

/**
 * Makes a copy of the sudoku.
 * @param grid filled sudoku
 * @param solvedSudoku empty sudoku
 */
void copySudokuToSolved(int grid[9][9], int solvedSudoku[9][9]);

/**
 * Checks if the sudoku is solved
 * @param grid filled from user sudoku
 * @param solvedSudoku generated solved sudoku from algorithm
 * @return if sudoku is solved or not
 */
bool isSudokuSolved(int grid[9][9], int solvedSudoku[9][9]);

/**
 * Prints the final screen, when the sudoku is solved
 */
void finalScreen();

/**
 * Saves the sudoku.
 * @param sudoku
 */
void saveSudoku(int sudoku[9][9]);

/**
 * Assigns which cells from sudoku cannot be edited on a boolean array.
 * @param sudoku sudoku
 * @param notEditables empty boolean field
 */
void notEditables(int sudoku[9][9], bool notEditables[9][9]);

void printMenu();

#endif	/* HELPERS_H */


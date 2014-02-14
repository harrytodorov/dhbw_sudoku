/* 
 * File:   backtracking.h
 * Author: haralambitodorov
 *
 * Created on February 12, 2014, 12:47 PM
 */

#ifndef BACKTRACKING_H
#define	BACKTRACKING_H

void generateSudoku(int grid[9][9]);

int isSafe(int grid[9][9], int row, int col, long num);

int SolveSudoku(int grid[9][9]);

#endif	/* BACKTRACKING_H */


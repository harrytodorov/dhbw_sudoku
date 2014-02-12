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

#endif	/* BACKTRACKING_H */


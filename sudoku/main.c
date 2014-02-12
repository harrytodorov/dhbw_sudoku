/* 
 * File:   main.c
 * Author: haralambitodorov
 *
 * Created on February 8, 2014, 2:52 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "helpers.h"



/*
 * 
 */
int main(int argc, char** argv) {

    int x = 0, y = 0, c;
    printWelcomeScreen(c);
    
    printSudokuField();
         int grid[9][9] = {{3, 0, 6, 5, 0, 8, 4, 0, 0},
                       {5, 2, 0, 0, 0, 0, 0, 0, 0},
                       {0, 8, 7, 0, 0, 0, 0, 3, 1},
                       {0, 0, 3, 0, 1, 0, 0, 8, 0},
                       {9, 0, 0, 8, 6, 3, 0, 0, 5},
                       {0, 5, 0, 0, 9, 0, 6, 0, 0},
                       {1, 3, 0, 0, 0, 0, 2, 5, 0},
                       {0, 0, 0, 0, 0, 0, 0, 7, 4},
                       {0, 0, 5, 2, 0, 6, 3, 0, 0}};

         printSudoku(grid);
        POSITION(2,2);
    while((c = getch()) != EOF) {
        if(isalpha(c)) {
            if(c == 'w' || c == 'W' || c == 'A' || c == 'a' || c == 'S' || c == 's' || c == 'D' || c == 'd')
                moveInSudokuField(&y, &x, c);
            else if(c == 'q') 
                break;
        } else if(isdigit(c)) {
                printDigitToField(y, x, c, grid);
        }
    }
        printSudoku(grid);
    
    return (EXIT_SUCCESS);
}


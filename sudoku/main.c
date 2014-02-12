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
    int grid[9][9];
    printWelcomeScreen(c);
    CLEAR;
    printMenu(c, grid);
    
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
//        printSudoku(grid);
//    
    return (EXIT_SUCCESS);
}


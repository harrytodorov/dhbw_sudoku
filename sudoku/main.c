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
    atexit(sudokuExit);
    printWelcomeScreen();
    CLEAR;
    printMenu();
    
//        printSudoku(grid);
//    
    return (EXIT_SUCCESS);
}


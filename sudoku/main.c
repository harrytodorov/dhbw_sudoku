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
    printWelcomeScreen();
    printf("\n\n\nPress any key to continue...");
    c = getch();
    printSudokuField();
    POSITION(2,2);
    while((c = getch()) != EOF) {
        moveInSudokuField(&y, &x, c);
    }
    
    return (EXIT_SUCCESS);
}


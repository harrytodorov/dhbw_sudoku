#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>
#include "helpers.h"
#include "backtracking.h"

#define MAXCHAR 200

int allowedPosX[9] = {2, 5, 8, 13, 16, 19, 23, 26, 29};
int allowedPosY[9] = {2, 3, 4, 6, 7, 8, 10, 11, 12};

int getch() {
    int ch;
    struct termios oldt, newt;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return ch;
}

void printSudokuField() {
    CLEAR;
    int i, j;
    POSITION(START_POS_Y, START_POS_X);
    for (i = 0; i <= 12; i++) {
        if ((i % 4) == 0)
            printf("+");
        else
            printf("|");
        for (j = 1; j <= 29; j++) {
            if (((j % 10) == 0) && ((i % 4) != 0)) {
                printf("|");
            } else if ((i % 4) == 0) {
                if ((j % 10) == 0)
                    printf("+");
                else
                    printf("-");
            } else
                printf(" ");
        }
        if ((i % 4) == 0)
            printf("+");
        else
            printf("|");
        printf("\n");
    }
}

void moveInSudokuField(int *y, int *x, int c) {
    POSITION(allowedPosY[*y], allowedPosX[*x]);
        switch (c) {
            case 'w':
            case 'W':
                if(*y == 0)
                    *y = 8;
                else if(*y > 0 && *y <= 8)
                    *y = *y - 1;
                break;
            case 's':
            case 'S':
                if(*y == 8)
                    *y = 0;
                else if(*y >= 0 && *y < 8)
                    *y = *y + 1;
                break;
            case 'a':
            case 'A':
                if(*x == 0)
                    *x = 8;
                else if(*x > 0 && *x <= 8) {
                    *x = *x - 1;
                }
                break;
            case 'd':
            case 'D':
                if(*x == 8)
                    *x = 0;
                else if(*x >= 0 && *x < 8) {
                    *x = *x + 1;
                }
                break;
            default:
                break;
        }
        POSITION(allowedPosY[*y], allowedPosX[*x]);
}

void printWelcomeScreen(int c) {
    printf("+++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("+   ***   *   *  ****    ***   *   *  *   *   +\n");
    printf("+  *      *   *  *   *  *   *  *  *   *   *   +\n");
    printf("+  *      *   *  *   *  *   *  * *    *   *   +\n");
    printf("+   ***   *   *  *   *  *   *  **     *   *   +\n");
    printf("+      *  *   *  *   *  *   *  * *    *   *   +\n");
    printf("+      *  *   *  *   *  *   *  *  *   *   *   +\n");
    printf("+   ***    ***   ****    ***   *   *   ***    +\n");
    printf("+++++++++++++++++++++++++++++++++++++++++++++++\n");   
    
    printf("\n\n\nPress any key to continue...");
    c = getch();
}

void printSudoku(int sudoku[9][9]) {
    int i, j;
    for(i = 0; i < 9; i++) {
        for(j = 0; j < 9; j++) {
            POSITION(allowedPosY[i], allowedPosX[j]);
            printf("%d", sudoku[i][j]);
        }
    }
}

void printDigitToField(int y, int x, int c, int sudoku[9][9]) {
        POSITION(allowedPosY[y], allowedPosX[x]);
        printf("%d", c - '0');
        sudoku[y][x] = c - '0';
}

void printMenu(int c, int grid[9][9]) {
    POSITION(1,1);
    printf("+++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("+   ***   *   *  ****    ***   *   *  *   *   +\n");
    printf("+  *      *   *  *   *  *   *  *  *   *   *   +\n");
    printf("+  *      *   *  *   *  *   *  * *    *   *   +\n");
    printf("+   ***   *   *  *   *  *   *  **     *   *   +\n");
    printf("+      *  *   *  *   *  *   *  * *    *   *   +\n");
    printf("+      *  *   *  *   *  *   *  *  *   *   *   +\n");
    printf("+   ***    ***   ****    ***   *   *   ***    +\n");
    printf("+++++++++++++++++++++++++++++++++++++++++++++++\n\n\n\n");
    printf("\tn - New game\n\n");
    printf("\tl - Load game\n\n");
    printf("\tb - About\n\n");
    printf("\tq - quit\n\n");
    printf("Choose: ");
    c = getch();
    switch(c) {
        case 'n':
        case 'N':
            generateSudoku(grid);
            printSudokuField();
            printSudoku(grid);
            break;
        case 'l':
        case 'L':
            loadSudokuFromFile(grid);
            break;
        case 'b':
        case 'B':
            aboutSudoku();
            printMenu(c, grid);
            break;
        case 'q':
        case 'Q':
            CLEAR;
            POSITION(1,1);
            exit(EXIT_SUCCESS);
            break;
        default:
            break;
    }
}

void aboutSudoku() {
   POSITION(0, 0);
   CLEAR;
   printf("\n\n\n\tSudoku\n\t by Jonas Kratschmann && Haralambi Todorov\n\t DHBW Stuttgart, 2014");
   printf("\n\nPress any key to go back to menu...");
   int c = getch();
}


int loadSudokuFromFile(int sudoku[9][9]) {
    FILE *fp;
    char str[MAXCHAR];
    char filename[MAXCHAR];
    extern int errno;
    int i, j;
    CLEAR;
    POSITION(1,1);
    printf("\tLoad Sudoku from FILE\n\n\n");
    printf("Sudoku file has to look like:\n"
            "1..456789\n132132132\n231..2323\n231...133\n231..2133\n231234431\n23431..44\n232..2133\n21343..34\n\n");
    printf("With '.' are marked empty fields.");
    printf("Please give path to file: ");
    scanf("%s", filename);
    fp = fopen(filename, "r");
    if(fp == NULL) {
        perror(strerror(errno));
        return 0;
    }
    i = 0;
    while (fgets(str, MAXCHAR, fp)) {
        for(j = 0; j < 9; j++) {
            if(str[j] == '.')
                sudoku[i][j] = 0;
            else
                sudoku[i][j] = str[j] - '0';
        }
        i++;
    }
    return 1;
}


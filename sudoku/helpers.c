#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include "helpers.h"
#include "backtracking.h"

#define MAXCHAR 200
#define USER_DATA_POS(x) POSITION(x, 35)

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
            if (*y == 0)
                *y = 8;
            else if (*y > 0 && *y <= 8)
                *y = *y - 1;
            break;
        case 's':
        case 'S':
            if (*y == 8)
                *y = 0;
            else if (*y >= 0 && *y < 8)
                *y = *y + 1;
            break;
        case 'a':
        case 'A':
            if (*x == 0)
                *x = 8;
            else if (*x > 0 && *x <= 8) {
                *x = *x - 1;
            }
            break;
        case 'd':
        case 'D':
            if (*x == 8)
                *x = 0;
            else if (*x >= 0 && *x < 8) {
                *x = *x + 1;
            }
            break;
        default:
            break;
    }
    POSITION(allowedPosY[*y], allowedPosX[*x]);
}

void printWelcomeScreen() {
    CLEAR;
    int c;
    printf("+++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("+   ***   *   *  ****    ***   *   *  *   *   +\n");
    printf("+  *      *   *  *   *  *   *  *  *   *   *   +\n");
    printf("+  *      *   *  *   *  *   *  * *    *   *   +\n");
    printf("+   ***   *   *  *   *  *   *  **     *   *   +\n");
    printf("+      *  *   *  *   *  *   *  * *    *   *   +\n");
    printf("+      *  *   *  *   *  *   *  *  *   *   *   +\n");
    printf("+   ***    ***   ****    ***   *   *   ***    +\n");
    printf("+++++++++++++++++++++++++++++++++++++++++++++++\n");

    printf("\n\n\nPressstartNewGame any key to continue...");
    c = getch();
}

void printSudoku(int sudoku[9][9]) {
    int i, j;
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            POSITION(allowedPosY[i], allowedPosX[j]);
            if (sudoku[i][j] == 0) {
                printf(" ");
            } else {
                printf("%d", sudoku[i][j]);
            }
        }
    }
}

void printDigitToField(int y, int x, int c, int sudoku[9][9]) {
    POSITION(allowedPosY[y], allowedPosX[x]);
    printf("%d", c);
    sudoku[y][x] = c;
    
}

void printMenu() {
    POSITION(1, 1);
    int grid[9][9];
    bool notEditable[9][9];
    int c;
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
    switch (c) {
        case 'n':
        case 'N':
            newGame(grid, notEditable);
            break;
        case 'l':
        case 'L':
            loadSudokuFromFile(grid);
            break;
        case 'b':
        case 'B':
            aboutSudoku();
            printMenu(c, grid, notEditable);
            break;
        case 'q':
        case 'Q':
            CLEAR;
            POSITION(1, 1);
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

void loadSudokuFromFile(int sudoku[9][9]) {
    FILE *fp;
    char str[MAXCHAR];
    char filename[MAXCHAR];
    extern int errno;
    int i, j;
    CLEAR;
    POSITION(1, 1);
    printf("\tLoad Sudoku from FILE\n\n\n");
    printf("Sudoku file has to look like:\n"
            "1..456789\n132132132\n231..2323\n231...133\n231..2133\n231234431\n23431..44\n232..2133\n21343..34\n\n");
    printf("With '.' are marked empty fields.");
    printf("Please give path to file: ");
    scanf("%s", filename);
    fp = fopen(filename, "r");
    if (fp == NULL) {
        perror(strerror(errno));
    }
    i = 0;
    while (fgets(str, MAXCHAR, fp)) {
        for (j = 0; j < 9; j++) {
            if (str[j] == '.')
                sudoku[i][j] = 0;
            else
                sudoku[i][j] = str[j] - '0';
        }
        i++;
    }
    int solvedSudoku[9][9];
    bool notEditable[9][9];
    char name[20];
    int c, num, x, y;
    copySudokuToSolved(sudoku, solvedSudoku);
    if(SolveSudoku(solvedSudoku)) {
        CLEAR;
        POSITION(0, 0);
        printf("\nGive a username: ");
        scanf("%s", name);
        notEditables(sudoku, notEditable);
        printSudokuField();
        printSudoku(sudoku);
        printUserData(name);
        POSITION(2, 2);
        while ((c = getch()) != EOF) {
            if (isalpha(c)) {
                if (c == 'w' || c == 'W' || c == 'A' || c == 'a' || c == 'S' || c == 's' || c == 'D' || c == 'd')
                    moveInSudokuField(&y, &x, c);
                else if (c == 'q')
                    break;
                else if(c == 'y' || c == 'Y') 
                        saveSudoku(sudoku);
            } else if (isdigit(c)) {
                if (notEditable[y][x]) {
                    num = c - '0';
                    printDigitToField(y, x, num, sudoku);
                    if (isSudokuSolved(sudoku, solvedSudoku)) {
                        finalScreen();
                    }
                }
            }
        }
    } else {
        POSITION(0, 0);
        CLEAR;
        printf("\n\n\nThis sudoku cannot be solved.");
    }
}

void sudokuExit(void) {
    CLEAR;
    printf("Bey!\n");
}

void removeRandomNumber(int grid[9][9], int complexity, bool notEditable[9][9]) {
    int i, j;
    int removed = 0;
    srand(time(NULL));
    do{
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
                if((rand() % 2) == 1) {
                    if(grid[i][j] != 0) {
                        grid[i][j] = 0;
                        removed++;
                    }
                    notEditable[i][j] = grid[i][j] == 0;
            }
        }
    }
    } while (removed <= complexity);
}

void newGame(int grid[9][9], bool notEditable[9][9]) {
    int c, y = 0, x = 0;
    int num;
    int solvedSudoku[9][9];
    char name[20];
    CLEAR;
    POSITION(0, 0);
    printf("\nGive a username: ");
    scanf("%s", name);
    generateSudoku(grid);
    copySudokuToSolved(grid, solvedSudoku);
    setArrayToZero(notEditable);
    removeRandomNumber(grid, 2, notEditable);
    printSudokuField();
    printSudoku(grid);
    printUserData(name);
    POSITION(2,2);
    while((c = getch()) != EOF) {
        if(isalpha(c)) {
            if(c == 'w' || c == 'W' || c == 'A' || c == 'a' || c == 'S' || c == 's' || c == 'D' || c == 'd')
                moveInSudokuField(&y, &x, c);
            else if(c == 'q' || c == 'Q') 
                break;
            else if(c == 'y' || c == 'Y') 
                saveSudoku(grid);
        } else if(isdigit(c)) {
            if(notEditable[y][x]) {
                num = c - '0';
                printDigitToField(y, x, num, grid);
                if (isSudokuSolved(grid, solvedSudoku)) {
                    finalScreen();
                }
            }
        }
    }
}

void printUserData(char name[20]) {
    USER_DATA_POS(5);
    printf("User: %s", name);
    USER_DATA_POS(6);
    printf("Good luck!");
    USER_DATA_POS(7);
    printf("Press q to quit.");
    USER_DATA_POS(8);
    printf("Press y to save.");
}

void setArrayToZero(bool notEditable[9][9]) {
    int i, j;
    for(i = 0; i < 9; i++) {
        for(j = 0; j < 9; j++)
            notEditable[i][j] = false;
    }
}

void copySudokuToSolved(int grid[9][9], int solvedSudoku[9][9]) {
    int i, j;
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            solvedSudoku[i][j] = grid[i][j];
        }
    }
}

bool isSudokuSolved(int grid[9][9], int solvedSudoku[9][9]) {
    int i, j;
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            if(grid[i][j] != solvedSudoku[i][j])
                return false;
        }
    }
    return true;
}

void finalScreen() {
    POSITION(1, 1);
    CLEAR;
    printf("\n\n\n\n\n\t\t");
    printf("You've won!");
    printf("\n\n\nPress any key to go to menu...");
    int c = getch();
    printMenu();
}

void notEditables(int sudoku[9][9], bool notEditables[9][9]) {
    int i, j;
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            if (isdigit(sudoku[i][j])) {
                notEditables[i][j] = true;
            }
        }
    }
}

void saveSudoku(int sudoku[9][9]) {
    POSITION(0,0);
    CLEAR;
    FILE *fp;
    char fileName[MAXCHAR];
    extern int errno;
    printf("\n\n\nSave sudoku as: ");
    scanf("%s", fileName);
    fp = fopen(fileName, "w");
    if(fp == NULL) {
        perror(strerror(errno));
    }
    int i, j;
    for(i = 0; i < 9; i++) {
        for(j = 0; j < 9; j++) {
            if(sudoku[i][j] == 0) {
                putc('.', fp);
            } else
                putc(sudoku[i][j], fp);
        }       
    }
    fclose(fp);
    printf("\nSudoku saved successfully!\n\n");
    int c;
    printf("Press any key to go back to menu...");
    c = getch();
    printMenu();
} 
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include "helpers.h"

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

void printWelcomeScreen() {
    printf("\033[32m+++++++++++++++++++++++++++++++++++++++++++++++\033[32m\n");
    printf("+   ***   *   *  ****    ***   *   *  *   *   +\033[32m\n");
    printf("+  *      *   *  *   *  *   *  *  *   *   *   +\033[32m\n");
    printf("+  *      *   *  *   *  *   *  * *    *   *   +\033[32m\n");
    printf("+   ***   *   *  *   *  *   *  **     *   *   +\033[32m\n");
    printf("+      *  *   *  *   *  *   *  * *    *   *   +\033[32m\n");
    printf("+      *  *   *  *   *  *   *  *  *   *   *   +\033[32m\n");
    printf("+   ***    ***   ****    ***   *   *   ***    +\033[32m\n");
    printf("+++++++++++++++++++++++++++++++++++++++++++++++\033[0m \n");    
}



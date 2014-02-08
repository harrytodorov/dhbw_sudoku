#include <termios.h>
#include <unistd.h>
#include <stdio.h>

#define CLEAR printf("\033[2J")
#define POSITION(Ze, Sp) printf("\033[%d;%dH",Ze,Sp)

int getch()
{
	int ch;
	struct termios oldt, newt;
    
	tcgetattr (STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr (STDIN_FILENO, TCSANOW, &newt);
	ch = getchar();
	tcsetattr (STDIN_FILENO, TCSANOW, &oldt);
    
	return ch;
}

void printSudokuField(int y, int x) {
    CLEAR;
    POSITION(y, x);
    int i = y, j = x;
    int endOfY = y + 11;
    int endOfX = x + 29;
    for(i; i <= endOfY; i++) {
        for(j; j <= endOfX; j++) {
            if((((j - x) % 10) == 0) && (((i - y) % 4) != 0)) {
                printf("|");
            }
            else if(((i - y) % 4) == 0) {
                if(((j - x) % 10) == 0)
                    printf("+");
                else
                    printf("-");
            }
            else
                printf(" ");
        }
        printf("\n");
    }
}
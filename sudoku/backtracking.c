#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>

#define UNASSIGNED 0
#define true 1
#define false 0
 
#define N 9
 
int FindUnassignedLocation(int grid[N][N], int *row, int *col);
 
int isSafe(int grid[N][N], int row, int col, long num);

void printGrid(int grind[N][N]);

void setCandidates(int *ptr[N])
{
  int r;
  for(int i = 0; i < 9; i++) 
  {
    int a = 0;
    do
    {
      r = (rand() % 9)+1;
      for(int j = 0; j <= i; j++) 
      {        
        a = 0;
        if(ptr[j] == r)
          break;
        a = 1;
      }
      
    }while(a != 1);
    ptr[i] = r;
    
  }
}

int SolveSudoku(int grid[N][N])
{
    int row, col;
    if (!FindUnassignedLocation(grid, &row, &col))
       return true; 
 
    long num[N] = {0,0,0,0,0,0,0,0,0};
    setCandidates(&num);

    for (int i = 0; i <= 8; i++)
    {
        if (isSafe(grid, row, col, num[i]))
        {
            grid[row][col] = num[i];

            if (SolveSudoku(grid))
                return true;
 
            grid[row][col] = UNASSIGNED;
        }
    }
    return false; 
}
 
int FindUnassignedLocation(int grid[N][N], int *row, int *col)
{
    for (*row = 0; *row < N; *row = *row+1)
        for (*col = 0; *col < N; *col = *col+1)
            if (grid[*row][*col] == UNASSIGNED)
                return true;
    return false;
}
 
int UsedInRow(int grid[N][N], int row, long num)
{
    for (int col = 0; col < N; col++)
        if (grid[row][col] == num)
            return true;
    return false;
}
 
int UsedInCol(int grid[N][N], int col, long num)
{
    for (int row = 0; row < N; row++)
        if (grid[row][col] == num)
            return true;
    return false;
}
 
int UsedInBox(int grid[N][N], int boxStartRow, int boxStartCol, long num)
{
    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
            if (grid[row+boxStartRow][col+boxStartCol] == num)
                return true;
    return false;
}
 
int isSafe(int grid[N][N], int row, int col, long num)
{
    return !UsedInRow(grid, row, num) &&
           !UsedInCol(grid, col, num) &&
           !UsedInBox(grid, row - row%3 , col - col%3, num);
}
 
void printGrid(int grid[N][N])
{
    for (int row = 0; row < N; row++)
    {
       for (int col = 0; col < N; col++)
             printf("%2d", grid[row][col]);
        printf("\n");
    }
    printf("\n\n");
}

void startingGrid(int grid[N][N])
{
  srand(time(NULL));
  
  int all = 0;

  for(int row = 0; row < N; row++)
  {
    for (int col = 0; col < N; col++)
    {
      int r = rand() % 100;

      if(r <= 5)
          grid[row][col] = (rand() % N)+1;
      else
          grid[row][col] = 0;  

      all++;
    }
  }
}

void generateSudoku(int grid[N][N]) {
  startingGrid(grid);
  SolveSudoku(grid);
}
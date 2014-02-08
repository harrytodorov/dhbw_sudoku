// A Backtracking program  in C++ to solve Sudoku problem
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>

 
// UNASSIGNED is used for empty cells in sudoku grid
#define UNASSIGNED 0
#define true 1
#define false 0
 
// N is used for size of Sudoku grid. Size will be NxN
#define N 9
 
// This function finds an entry in grid that is still unassigned
int FindUnassignedLocation(int grid[N][N], int *row, int *col);
 
// Checks whether it will be legal to assign num to the given row,col
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
        if(*ptr[j] == r)
          break;
        a = 1;
      }
      
    }while(a != 1);
    *ptr[i] = r;
    
  }
}

/* Takes a partially filled-in grid and attempts to assign values to
  all unassigned locations in such a way to meet the requirements
  for Sudoku solution (non-duplication across rows, columns, and boxes) */
int SolveSudoku(int grid[N][N])
{
    int row, col;
    // printGrid(grid);
    // If there is no unassigned location, we are done
    if (!FindUnassignedLocation(grid, &row, &col))
       return true; // success!
 
    // consider digits 1 to 9
    long num[N] = {0,0,0,0,0,0,0,0,0};
    setCandidates(&num);

    for (int i = 0; i <= 8; i++)
    {
        // printf("%d %d %d\n", row, col, num[i]);
        // if looks promising
        if (isSafe(grid, row, col, num[i]))
        {
            // make tentative assignment
            grid[row][col] = num[i];
 
            // return, if success, yay!
            if (SolveSudoku(grid))
                return true;
 
            // failure, unmake & try again
            grid[row][col] = UNASSIGNED;
        }
    }
    return false; // this triggers backtracking
}
 
/* Searches the grid to find an entry that is still unassigned. If
   found, the reference parameters row, col will be set the location
   that is unassigned, and true is returned. If no unassigned entries
   remain, false is returned. */
int FindUnassignedLocation(int grid[N][N], int *row, int *col)
{
    for (*row = 0; *row < N; *row = *row+1)
        for (*col = 0; *col < N; *col = *col+1)
            if (grid[*row][*col] == UNASSIGNED)
                return true;
    return false;
}
 
/* Returns a intean which indicates whether any assigned entry
   in the specified row matches the given number. */
int UsedInRow(int grid[N][N], int row, long num)
{
    for (int col = 0; col < N; col++)
        if (grid[row][col] == num)
            return true;
    return false;
}
 
/* Returns a intean which indicates whether any assigned entry
   in the specified column matches the given number. */
int UsedInCol(int grid[N][N], int col, long num)
{
    for (int row = 0; row < N; row++)
        if (grid[row][col] == num)
            return true;
    return false;
}
 
/* Returns a intean which indicates whether any assigned entry
   within the specified 3x3 box matches the given number. */
int UsedInBox(int grid[N][N], int boxStartRow, int boxStartCol, long num)
{
    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
            if (grid[row+boxStartRow][col+boxStartCol] == num)
                return true;
    return false;
}
 
/* Returns a intean which indicates whether it will be legal to assign
   num to the given row,col location. */
int isSafe(int grid[N][N], int row, int col, long num)
{
    /* Check if 'num' is not already placed in current row,
       current column and current 3x3 box */
    return !UsedInRow(grid, row, num) &&
           !UsedInCol(grid, col, num) &&
           !UsedInBox(grid, row - row%3 , col - col%3, num);
}
 
/* A utility function to print grid  */
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

void startingGrid(int *grid[N][N])
{
  

  int all = 0;

  for(int row = 0; row < N; row++)
  {
    for (int col = 0; col < N; col++)
    {
      int r = rand() % 100;

      if(all == 0 || all == 17 || all == 75)
          *grid[row][col] = (rand() % N)+1;
      else
        *grid[row][col] = 0;  

      all++;
    }
  }
}
 
/* Driver Program to test above functions */
int main()
{
  srand(time(NULL));
    // 0 means unassigned cells
    // int grid[N][N] = {{3, 0, 6, 5, 0, 8, 4, 0, 0},
    //                   {5, 2, 0, 0, 0, 0, 0, 0, 0},
    //                   {0, 8, 7, 0, 0, 0, 0, 3, 1},
    //                   {0, 0, 3, 0, 1, 0, 0, 8, 0},
    //                   {9, 0, 0, 8, 6, 3, 0, 0, 5},
    //                   {0, 5, 0, 0, 9, 0, 6, 0, 0},
    //                   {1, 3, 0, 0, 0, 0, 2, 5, 0},
    //                   {0, 0, 0, 0, 0, 0, 0, 7, 4},
    //                   {0, 0, 5, 2, 0, 6, 3, 0, 0}};

  int grid[N][N];
  startingGrid(&grid);
  printGrid(grid);
  

  if (SolveSudoku(grid) == true)
        printGrid(grid);
  else
       printf("No solution exists");

  return 0;
}

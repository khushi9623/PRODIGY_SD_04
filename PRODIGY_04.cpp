#include <iostream>
using namespace std;

const int N = 9;

// Function to print the Sudoku grid
void printGrid(int grid[N][N])
{
  for (int row = 0; row < N; row++)
  {
    for (int col = 0; col < N; col++)
      cout << grid[row][col] << " ";
    cout << endl;
  }
}

// Function to check if a number can be placed in a given cell
bool isSafe(int grid[N][N], int row, int col, int num)
{
  // Check if the number is not present in the current row and column
  for (int x = 0; x < N; x++)
    if (grid[row][x] == num || grid[x][col] == num)
      return false;

  // Check if the number is not present in the current 3x3 subgrid
  int startRow = row - row % 3, startCol = col - col % 3;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      if (grid[i + startRow][j + startCol] == num)
        return false;

  return true;
}

// Function to find an empty cell in the grid
bool findEmptyCell(int grid[N][N], int &row, int &col)
{
  for (row = 0; row < N; row++)
    for (col = 0; col < N; col++)
      if (grid[row][col] == 0)
        return true;
  return false;
}

// Function to solve the Sudoku puzzle using backtracking
bool solveSudoku(int grid[N][N])
{
  int row, col;

  // If no empty cell is found, the Sudoku is solved
  if (!findEmptyCell(grid, row, col))
    return true;

  // Try filling the empty cell with numbers 1 to 9
  for (int num = 1; num <= 9; num++)
  {
    if (isSafe(grid, row, col, num))
    {
      // Place the number in the current cell
      grid[row][col] = num;

      // Recursively attempt to solve the rest of the puzzle
      if (solveSudoku(grid))
        return true;

      // If placing the number leads to an invalid solution, backtrack
      grid[row][col] = 0;
    }
  }

  // No valid number can be placed, backtrack to the previous cell
  return false;
}

int main()
{
  int grid[N][N];

  cout << "Enter the Sudoku grid (9x9) with 0 for empty cells:" << endl;
  for (int row = 0; row < N; row++)
    for (int col = 0; col < N; col++)
      cin >> grid[row][col];

  cout << "Sudoku Puzzle:" << endl;
  printGrid(grid);

  if (solveSudoku(grid))
  {
    cout << "\nSolved Sudoku:" << endl;
    printGrid(grid);
  }
  else
  {
    cout << "\nNo solution exists for the given Sudoku." << endl;
  }

  return 0;
}

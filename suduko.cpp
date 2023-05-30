#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>

const int N = 9;

void initializeGrid(int grid[N][N])
{
    // Initialize the grid with zeroes
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            grid[i][j] = 0;
        }
    }
}

bool isSafe(int grid[N][N], int row, int col, int num)
{
    // Check if the number already exists in the row
    for (int i = 0; i < N; i++) {
        if (grid[row][i] == num) {
            return false;
        }
    }

    // Check if the number already exists in the column
    for (int i = 0; i < N; i++) {
        if (grid[i][col] == num) {
            return false;
        }
    }

    // Check if the number already exists in the 3x3 grid
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }

    return true;
}

bool fillGrid(int grid[N][N])
{
    // Find the next empty cell
    int row, col;
    bool isEmptyCell = false;
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (grid[row][col] == 0) {
                isEmptyCell = true;
                break;
            }
        }
        if (isEmptyCell) {
            break;
        }
    }

    // If there are no empty cells, the grid is filled completely
    if (!isEmptyCell) {
        return true;
    }

    // Generate a random order of numbers from 1 to 9
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::random_shuffle(numbers.begin(), numbers.end());

    // Try filling the cell with the shuffled numbers
    for (int i = 0; i < N; i++) {
        int num = numbers[i];
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;

            // Recursively fill the rest of the grid
            if (fillGrid(grid)) {
                return true;
            }

            // If filling the rest of the grid leads to an invalid solution,
            // backtrack and try the next number
            grid[row][col] = 0;
        }
    }

    return false;
}

void generateSudoku(int grid[N][N])
{
    // Initialize the random seed
    std::srand(std::time(nullptr));

    // Generate a Sudoku grid
    fillGrid(grid);
}

void displayGrid(int grid[N][N])
{
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            std::cout << grid[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
int main()
{
    int grid[N][N];

    // Generate a Sudoku puzzle
    generateSudoku(grid);

    // Display the generated puzzle
    displayGrid(grid);

    return 0;
}
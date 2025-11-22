#include <iostream>
#include <vector>
using namespace std;

// Function to print the chessboard
void printBoard(const vector<vector<int>>& board, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << (board[i][j] ? "Q " : ". ");
        cout << endl;
    }
    cout << endl;
}

// Check if placing a queen at board[row][col] is safe
bool isSafe(const vector<vector<int>>& board, int row, int col, int n) {
    // Check column
    for (int i = 0; i < row; i++)
        if (board[i][col])
            return false;

    // Check upper left diagonal
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return false;

    // Check upper right diagonal
    for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++)
        if (board[i][j])
            return false;

    return true;
}

// Recursive function to solve N-Queen problem
bool solveNQueen(vector<vector<int>>& board, int row, int n) {
    // Base case: All queens are placed
    if (row == n) {
        printBoard(board, n);
        return true;  // Found a solution
    }

    bool res = false;
    for (int col = 0; col < n; col++) {
        if (isSafe(board, row, col, n)) {
            board[row][col] = 1; // Place queen
            res = solveNQueen(board, row + 1, n) || res; // Recurse for next row
            board[row][col] = 0; // Backtrack
        }
    }
    return res;
}

int main() {
    int n;
    cout << "Enter the number of queens: ";
    cin >> n;

    vector<vector<int>> board(n, vector<int>(n, 0));

    if (!solveNQueen(board, 0, n))
        cout << "No solution exists for " << n << " queens." << endl;

    return 0;
}

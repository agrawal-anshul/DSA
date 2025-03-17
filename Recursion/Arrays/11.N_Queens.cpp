// https://leetcode.com/problems/n-queens/
#include <iostream>
#include <vector>
using namespace std;

int N;

bool isSafe(vector<vector<int>>& board, int row, int col) {
    for (int i = 0; i < row; i++)  // Check column
        if (board[i][col]) return false;
    
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) // Check left diagonal
        if (board[i][j]) return false;

    for (int i = row, j = col; i >= 0 && j < N; i--, j++) // Check right diagonal
        if (board[i][j]) return false;

    return true;
}

void printBoard(vector<vector<int>>& board, int r){
   for (const auto& r : board) {
      for (int cell : r) cout << (cell ? "Q " : ". ");
      cout << endl;
  }
  cout << endl;
}
void solveNQueens(vector<vector<int>>& board, int row) {
    if (row == N) {  // Base case: all queens placed
        printBoard(board, row);
        return;
    }

    for (int col = 0; col < N; col++) {
        if (isSafe(board, row, col)) {
            board[row][col] = 1;  // Place queen
            solveNQueens(board, row + 1); // Recur to next row
            board[row][col] = 0;  // Backtrack
        }
    }
}

int main() {
   //  cout << "Enter board size (N): ";
    cin >> N;
    vector<vector<int>> board(N, vector<int>(N, 0));

    solveNQueens(board, 0);

    return 0;
}

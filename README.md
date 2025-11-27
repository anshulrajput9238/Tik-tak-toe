// tictactoe.cpp
#include <bits/stdc++.h>
using namespace std;

// Clear screen by printing fewer newlines
void clearScreen() {
    cout << string(10, '\n'); // reduced from 50 to 10
}

// Display the 3x3 board
void displayBoard(const array<char,9>& board) {
    cout << "\n";
    cout << " " << board[0] << " | " << board[1] << " | " << board[2] << "\n";
    cout << "---+---+---\n";
    cout << " " << board[3] << " | " << board[4] << " | " << board[5] << "\n";
    cout << "---+---+---\n";
    cout << " " << board[6] << " | " << board[7] << " | " << board[8] << "\n\n";
}

// Check if move is valid
bool isValidMove(const array<char,9>& board, int pos) {
    return pos >= 1 && pos <= 9 && board[pos-1] != 'X' && board[pos-1] != 'O';
}

// Get player move with input validation
int getPlayerMove(const array<char,9>& board, char player) {
    int pos;
    while (true) {
        cout << "Player " << player << ", enter position (1-9): ";
        if (!(cin >> pos)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Enter a number from 1 to 9.\n";
            continue;
        }
        if (isValidMove(board, pos)) return pos;
        cout << "Position not available or out of range. Try again.\n";
    }
}

// Check winning condition
bool checkWin(const array<char,9>& b, char p) {
    static const int wins[8][3] = {
        {0,1,2}, {3,4,5}, {6,7,8}, // rows
        {0,3,6}, {1,4,7}, {2,5,8}, // cols
        {0,4,8}, {2,4,6}           // diagonals
    };
    for (auto &w : wins) {
        if (b[w[0]] == p && b[w[1]] == p && b[w[2]] == p) return true;
    }
    return false;
}

// Check draw condition
bool isDraw(const array<char,9>& board) {
    for (char c : board)
        if (c != 'X' && c != 'O') return false;
    return true;
}

int main() {
    cout << "Tic-Tac-Toe (2 players)\n";
    bool playAgain = true;

    while (playAgain) {
        // Initialize board with positions 1..9
        array<char,9> board;
        for (int i = 0; i < 9; ++i) board[i] = '1' + i;

        char current = 'X';
        bool gameOver = false;

        while (!gameOver) {
            clearScreen();
            cout << "Current board:\n";
            displayBoard(board);

            int move = getPlayerMove(board, current);
            board[move-1] = current;

            if (checkWin(board, current)) {
                clearScreen();
                displayBoard(board);
                cout << "Player " << current << " wins! 🎉\n";
                gameOver = true;
            } else if (isDraw(board)) {
                clearScreen();
                displayBoard(board);
                cout << "It's a draw! 🤝\n";
                gameOver = true;
            } else {
                current = (current == 'X') ? 'O' : 'X';
            }
        }

        char ans;
        cout << "Play again? (yes/no): ";
        cin >> ans;
        playAgain = (ans == 'y' || ans == 'Y');
    }

    cout << "Thanks for playing! 👋\n";
    return 0;
}

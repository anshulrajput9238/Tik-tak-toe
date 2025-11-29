#include <iostream>
using namespace std;

char board[9] = {'1','2','3','4','5','6','7','8','9'};

void showBoard() {
    cout << "\n";
    cout << " " << board[0] << " | " << board[1] << " | " << board[2] << "\n";
    cout << "---|---|---\n";
    cout << " " << board[3] << " | " << board[4] << " | " << board[5] << "\n";
    cout << "---|---|---\n";
    cout << " " << board[6] << " | " << board[7] << " | " << board[8] << "\n\n";
}

bool checkWin() {
    int wins[8][3] = {
        {0,1,2},{3,4,5},{6,7,8},
        {0,3,6},{1,4,7},{2,5,8},
        {0,4,8},{2,4,6}
    };
    for (auto &w : wins)
        if (board[w[0]] == board[w[1]] && board[w[1]] == board[w[2]])
            return true;
    return false;
}

int main() {
    char player = 'X';
    int move;
    
    while (true) {
        showBoard();
        cout << "Player " << player << ", enter position (1-9): ";
        cin >> move;

        if (move < 1 || move > 9 || board[move-1] == 'X' || board[move-1] == 'O') {
            cout << "Invalid! Try again.\n";
            continue;
        }

        board[move-1] = player;
        if (checkWin()) {
            showBoard();
            cout << "Player " << player << " wins!\n";
            break;
        }

        player = (player == 'X') ? 'O' : 'X';
    }
}
// tictactoe_ai.cpp
// Console Tic-Tac-Toe with optional AI (Minimax)
// Compile: g++ tictactoe_ai.cpp -o tictactoe.exe -mconsole

#include <bits/stdc++.h>
using namespace std;

const char HUMAN = 'X';
const char AI = 'O';
const char EMPTY = ' ';

void clearScreen() {
    // keep it simple and portable (just print some newlines)
    cout << string(20, '\n');
}

void displayBoard(const array<char,9>& board) {
    cout << "\n";
    cout << " " << board[0] << " | " << board[1] << " | " << board[2] << "    1 | 2 | 3\n";
    cout << "---+---+---" << "    ---+---+---\n";
    cout << " " << board[3] << " | " << board[4] << " | " << board[5] << "    4 | 5 | 6\n";
    cout << "---+---+---" << "    ---+---+---\n";
    cout << " " << board[6] << " | " << board[7] << " | " << board[8] << "    7 | 8 | 9\n";
    cout << "\n";
}

// Check for a win or tie
char checkWinner(const array<char,9>& b) {
    const int wins[8][3] = {
        {0,1,2},{3,4,5},{6,7,8}, // rows
        {0,3,6},{1,4,7},{2,5,8}, // cols
        {0,4,8},{2,4,6}          // diags
    };
    for (auto &w : wins) {
        if (b[w[0]] != EMPTY && b[w[0]] == b[w[1]] && b[w[1]] == b[w[2]])
            return b[w[0]];
    }
    // tie?
    bool anyEmpty = false;
    for (char c : b) if (c == EMPTY) { anyEmpty = true; break; }
    if (!anyEmpty) return 'T'; // Tie
    return 'N'; // None yet
}

// Minimax evaluation: +10 for AI win, -10 for human win, 0 otherwise
int evaluate(const array<char,9>& board) {
    char w = checkWinner(board);
    if (w == AI) return +10;
    if (w == HUMAN) return -10;
    return 0;
}

bool movesLeft(const array<char,9>& board) {
    for (char c : board) if (c == EMPTY) return true;
    return false;
}

int minimax(array<char,9>& board, int depth, bool isMax) {
    int score = evaluate(board);
    if (score == 10) return score - depth;   // prefer faster wins
    if (score == -10) return score + depth;  // prefer slower losses
    if (!movesLeft(board)) return 0;

    if (isMax) {
        int best = -1000;
        for (int i=0;i<9;i++) {
            if (board[i] == EMPTY) {
                board[i] = AI;
                int val = minimax(board, depth+1, false);
                board[i] = EMPTY;
                best = max(best, val);
            }
        }
        return best;
    } else {
        int best = 1000;
        for (int i=0;i<9;i++) {
            if (board[i] == EMPTY) {
                board[i] = HUMAN;
                int val = minimax(board, depth+1, true);
                board[i] = EMPTY;
                best = min(best, val);
            }
        }
        return best;
    }
}

int findBestMove(array<char,9>& board) {
    int bestVal = -1000;
    int bestMove = -1;
    for (int i=0;i<9;i++) {
        if (board[i] == EMPTY) {
            board[i] = AI;
            int moveVal = minimax(board, 0, false);
            board[i] = EMPTY;
            if (moveVal > bestVal) {
                bestMove = i;
                bestVal = moveVal;
            }
        }
    }
    return bestMove;
}

int getHumanMove(const array<char,9>& board) {
    while (true) {
        cout << "Enter your move (1..9): ";
        string s;
        if (!getline(cin, s)) return -1;
        if (s.empty()) continue;
        // support if user types spaces
        int pos = 0;
        try {
            pos = stoi(s);
        } catch(...) { cout << "Invalid input. Type a number 1..9.\n"; continue; }
        if (pos < 1 || pos > 9) { cout << "Enter number between 1 and 9.\n"; continue; }
        if (board[pos-1] != EMPTY) { cout << "Cell already used. Choose another.\n"; continue; }
        return pos-1;
    }
}

void playTwoPlayer() {
    array<char,9> board;
    board.fill(EMPTY);
    char turn = HUMAN; // X starts
    while (true) {
        clearScreen();
        cout << "Tic-Tac-Toe (2 players)\n";
        displayBoard(board);
        char state = checkWinner(board);
        if (state == HUMAN) { cout << "X wins!\n"; break; }
        if (state == AI) { cout << "O wins!\n"; break; }
        if (state == 'T') { cout << "It's a tie!\n"; break; }

        cout << (turn == HUMAN ? "Player X's turn\n" : "Player O's turn\n");
        int mv = getHumanMove(board);
        if (mv < 0) { cout << "Input error. Exiting.\n"; return; }
        board[mv] = turn;
        turn = (turn == HUMAN ? AI : HUMAN);
    }
    displayBoard(board);
    cout << "Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void playVsAI(bool humanFirst) {
    array<char,9> board;
    board.fill(EMPTY);
    char turn = humanFirst ? HUMAN : AI;
    while (true) {
        clearScreen();
        cout << "Tic-Tac-Toe (You vs Computer)\n";
        displayBoard(board);
        char state = checkWinner(board);
        if (state == HUMAN) { cout << "You (X) win! Nice!\n"; break; }
        if (state == AI) { cout << "Computer (O) wins.\n"; break; }
        if (state == 'T') { cout << "It's a tie!\n"; break; }

        if (turn == HUMAN) {
            cout << "Your (X) move.\n";
            int mv = getHumanMove(board);
            if (mv < 0) { cout << "Input error. Exiting.\n"; return; }
            board[mv] = HUMAN;
            turn = AI;
        } else {
            cout << "Computer is thinking...\n";
            int best = findBestMove(board);
            if (best == -1) {
                // fallback - shouldn't happen
                for (int i=0;i<9;i++) if (board[i] == EMPTY) { best = i; break; }
            }
            board[best] = AI;
            turn = HUMAN;
        }
    }
    displayBoard(board);
    cout << "Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (true) {
        clearScreen();
        cout << "=========================\n";
        cout << "   Tic-Tac-Toe (Console)\n";
        cout << "=========================\n";
        cout << "1) 2-player (Local)\n";
        cout << "2) Play vs Computer (You are X)\n";
        cout << "3) Play vs Computer (Computer starts as X)\n";
        cout << "4) Exit\n";
        cout << "Choose (1-4): ";
        string line;
        if (!getline(cin, line)) break;
        if (line.empty()) continue;
        int choice = 0;
        try { choice = stoi(line); } catch(...) { choice = 0; }
        if (choice == 1) playTwoPlayer();
        else if (choice == 2) playVsAI(true);
        else if (choice == 3) playVsAI(false);
        else if (choice == 4) { cout << "Goodbye!\n"; break; }
        else { cout << "Invalid choice. Press Enter to retry..."; cin.ignore(numeric_limits<streamsize>::max(), '\n'); }
    }
    return 0;
}

// tictactoe.cpp
// Compile: g++ -std=c++17 tictactoe.cpp -o tictactoe.exe
// Run:
//  - Two player:  ./tictactoe.exe
//  - Play vs AI:  ./tictactoe.exe ai

#include <bits/stdc++.h>
using namespace std;

#ifdef _WIN32
const string CLEAR_CMD = "cls";
#else
const string CLEAR_CMD = "clear";
#endif

void clearScreen() {
    // Prefer system("cls") on Windows because it prevents the blank-lines confusion.
    system(CLEAR_CMD.c_str());
}

void drawBoard(const array<char,9>& b) {
    cout << "\n";
    cout << " " << b[0] << " | " << b[1] << " | " << b[2] << "    1 | 2 | 3\n";
    cout << "---+---+---" << "    ---+---+---\n";
    cout << " " << b[3] << " | " << b[4] << " | " << b[5] << "    4 | 5 | 6\n";
    cout << "---+---+---" << "    ---+---+---\n";
    cout << " " << b[6] << " | " << b[7] << " | " << b[8] << "    7 | 8 | 9\n\n";
}

char checkWinner(const array<char,9>& b) {
    const int wins[8][3] = {
        {0,1,2},{3,4,5},{6,7,8}, // rows
        {0,3,6},{1,4,7},{2,5,8}, // cols
        {0,4,8},{2,4,6}          // diags
    };
    for (auto &w : wins) {
        if (b[w[0]] != ' ' && b[w[0]] == b[w[1]] && b[w[1]] == b[w[2]])
            return b[w[0]];
    }
    for (char c : b) if (c == ' ') return 'N'; // None yet
    return 'T'; // Tie
}

// Minimax for AI (X = human player, O = AI by default)
int minimax(array<char,9>& board, bool isMax) {
    char res = checkWinner(board);
    if (res == 'O') return +10;
    if (res == 'X') return -10;
    if (res == 'T') return 0;

    if (isMax) {
        int best = -1000;
        for (int i=0;i<9;++i) if (board[i]==' ') {
            board[i] = 'O';
            best = max(best, minimax(board, false));
            board[i] = ' ';
        }
        return best;
    } else {
        int best = 1000;
        for (int i=0;i<9;++i) if (board[i]==' ') {
            board[i] = 'X';
            best = min(best, minimax(board, true));
            board[i] = ' ';
        }
        return best;
    }
}

int findBestMove(array<char,9>& board) {
    int bestVal = -1000, bestMove = -1;
    for (int i=0;i<9;++i) if (board[i]==' ') {
        board[i] = 'O';
        int moveVal = minimax(board, false);
        board[i] = ' ';
        if (moveVal > bestVal) { bestMove = i; bestVal = moveVal; }
    }
    return bestMove;
}

int getIntFromUser(const string &prompt) {
    while (true) {
        cout << prompt;
        string s;
        if (!getline(cin, s)) return -1;
        // trim
        while (!s.empty() && isspace(s.back())) s.pop_back();
        if (s.empty()) continue;
        // allow digits only
        bool ok = true;
        for (char c : s) if (!isdigit((unsigned char)c)) { ok = false; break; }
        if (!ok) { cout << "Please enter a number.\n"; continue; }
        try {
            int v = stoi(s);
            return v;
        } catch(...) { cout << "Invalid number.\n"; }
    }
}

int main(int argc, char** argv) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    bool useAI = false;
    if (argc > 1) {
        string arg = argv[1];
        transform(arg.begin(), arg.end(), arg.begin(), ::tolower);
        if (arg == "ai" || arg == "bot" || arg == "computer") useAI = true;
    }

    array<char,9> board;
    board.fill(' ');
    char player = 'X'; // X always starts (human)
    clearScreen();
    cout << "Tic-Tac-Toe\n";
    cout << "Controls: choose position 1-9 from the keypad mapping shown on the right.\n";
    cout << (useAI ? "You play X vs AI (O).\n" : "Two-player mode (X and O).\n");
    cout << "Press Enter to start...";
    string tmp; getline(cin, tmp);

    while (true) {
        clearScreen();
        drawBoard(board);
        char res = checkWinner(board);
        if (res == 'X' || res == 'O') {
            cout << "Player " << res << " wins!\n";
            break;
        } else if (res == 'T') {
            cout << "It's a tie!\n";
            break;
        }

        if (useAI && player == 'O') {
            cout << "AI is thinking...\n";
            int mv = findBestMove(board);
            if (mv >= 0) board[mv] = 'O';
            player = 'X';
            continue;
        }

        cout << "Player " << player << "'s turn.\n";
        int pos = getIntFromUser("Enter position (1-9): ");
        if (pos < 1 || pos > 9) {
            cout << "Invalid position, try again.\n";
            cout << "Press Enter to continue..."; getline(cin,tmp);
            continue;
        }
        int idx = pos - 1;
        if (board[idx] != ' ') {
            cout << "Cell already taken, try again.\n";
            cout << "Press Enter to continue..."; getline(cin,tmp);
            continue;
        }
        board[idx] = player;
        player = (player == 'X') ? 'O' : 'X';
    }

    cout << "\nFinal board:\n";
    drawBoard(board);
    cout << "Thanks for playing!\n";
    return 0;
}
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

const int ROWS = 6, COLS = 7;
vector<vector<char>> board(ROWS, vector<char>(COLS, '.'));

bool dropDisc(int col, char player) {
    for (int i = ROWS - 1; i >= 0; --i) {
        if (board[i][col] == '.') {
            board[i][col] = player;
            return true;
        }
    }
    return false;
}

void readBoard(ifstream &fin) {
    string line;
    for (int i = 0; i < ROWS; ++i) {
        getline(fin, line);
        board[i] = vector<char>(line.begin(), line.end());
    }
}

void writeBoard(ofstream &fout) {
    for (auto &row : board) {
        for (char c : row) fout << c;
        fout << '\n';
    }
}

bool checkWin(char player) {
    // Horizontal
    for (int r = 0; r < ROWS; ++r) {
        for (int c = 0; c <= COLS - 4; ++c) {
            if (board[r][c] == player && board[r][c+1] == player &&
                board[r][c+2] == player && board[r][c+3] == player)
                return true;
        }
    }
    // Vertical
    for (int r = 0; r <= ROWS - 4; ++r) {
        for (int c = 0; c < COLS; ++c) {
            if (board[r][c] == player && board[r+1][c] == player &&
                board[r+2][c] == player && board[r+3][c] == player)
                return true;
        }
    }
    // Diagonal (top-left to bottom-right)
    for (int r = 0; r <= ROWS - 4; ++r) {
        for (int c = 0; c <= COLS - 4; ++c) {
            if (board[r][c] == player && board[r+1][c+1] == player &&
                board[r+2][c+2] == player && board[r+3][c+3] == player)
                return true;
        }
    }
    // Diagonal (bottom-left to top-right)
    for (int r = 3; r < ROWS; ++r) {
        for (int c = 0; c <= COLS - 4; ++c) {
            if (board[r][c] == player && board[r-1][c+1] == player &&
                board[r-2][c+2] == player && board[r-3][c+3] == player)
                return true;
        }
    }
    return false;
}

int main() {
    ifstream fin("backend/game_state.txt");
    readBoard(fin);
    int col; char player;
    fin >> col >> player;
    fin.close();

    dropDisc(col, player);

    // Check for win
    if (checkWin(player)) {
        ofstream winFile("backend/winner.txt");
        winFile << player;
        winFile.close();
    }

    ofstream fout("backend/game_state.txt");
    writeBoard(fout);
    fout.close();

    return 0;
}

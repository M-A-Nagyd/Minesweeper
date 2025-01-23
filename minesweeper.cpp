#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

#ifdef _WIN32
#include <windows.h> // For Windows only
#endif

using namespace std;

const int BOARD_SIZE = 5;
void initialize(char board[][BOARD_SIZE], bool mines[][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            board[i][j] = 'X';
        }
    }
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            mines[i][j] = false;
        }
    }

    srand(time(nullptr));
    int count = 0;
    while (count < 5) {
        int x = rand() % BOARD_SIZE;
        int y = rand() % BOARD_SIZE;
        if (!mines[x][y]) {
            mines[x][y] = true;
            count++;
        }
    }
}
void displayBoard(const char board[][BOARD_SIZE], const bool mines[][BOARD_SIZE]) {
    cout <<' ';
    for (int i = 0; i < BOARD_SIZE; ++i) {
        cout <<setw(3)<<i;
    }
    cout << endl;

    for (int i = 0; i < BOARD_SIZE; ++i) {
        cout << i << " ";
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (board[i][j] == 'M') {
                #ifdef _WIN32
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, 12);
                #endif
                cout << setw(2) << board[i][j];
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, 7);
                #endif
            } else if (board[i][j] == 'X') {
                int c=rand()%100+1;
                if(c<=15)
                    c+=20;
                #ifdef _WIN32
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, c);
                #endif
                cout << setw(2) << ' ';
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, 7);
                #endif
            } else {
                cout << setw(2) << board[i][j];
            }
            cout << " ";
        }
        cout << endl;
    }
}

void playMinesweeper() {
    char board[BOARD_SIZE][BOARD_SIZE];
    bool mines[BOARD_SIZE][BOARD_SIZE];
    initialize(board, mines);

    bool gameOver = false;
    int movesLeft = BOARD_SIZE * BOARD_SIZE - 3;
    while (!gameOver && movesLeft > 0) {
        displayBoard(board, mines);
        int x, y;
        cout << "Enter row and column (0-4): ";
        cin >> x >> y;
        if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE) {
            cout << "Invalid input! Try again." << endl;
            continue;
        }
        if (board[x][y] != 'X') {
            cout << "Cell already revealed! Try again." << endl;
            continue;
        }
        if (mines[x][y]) {
            cout << "Game Over! You stepped on a mine." << endl;
            gameOver = true;
            for (int i = 0; i < BOARD_SIZE; ++i) {
                for (int j = 0; j < BOARD_SIZE; ++j) {
                    if (mines[i][j]) {
                        board[i][j] = 'M';
                    }
                }
            }
        } else {
            int minesCount = 0;
            for (int i = max(0, x - 1); i <= min(BOARD_SIZE - 1, x + 1); ++i) {
                for (int j = max(0, y - 1); j <= min(BOARD_SIZE - 1, y + 1); ++j) {
                    if (mines[i][j]) {
                        minesCount++;
                    }
                }
            }
            board[x][y] = minesCount + '0';
            movesLeft--;
        }
    }
    displayBoard(board, mines);
    if (!gameOver) {
        cout << "Congratulations! You won the game!" << endl;
    }
}

int main() {
    playMinesweeper();
    return 0;
}

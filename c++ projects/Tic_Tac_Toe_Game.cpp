#include <iostream>
#include <conio.h>  // Chỉ dùng cho Windows
using namespace std;

class TicTacToe {
private:
    char board[3][3];
    char mark;
    int turn, won, input;

public:
    TicTacToe() {
        Reset();
    }

    int GetResult() {
        return won;
    }

    void Play() {
        for (int i = 0; i < 9; i++) {
            system("cls");
            PrintBoard();
            Input();

            int validInput = AddMark();
            if (!validInput) {
                cout << "Ô này đã được đánh. Nhập lại!\n";
                i--;
                _getch();
                continue;
            }

            Result(i);
            if (won != 0) break;
            turn = !turn; // đổi lượt
        }
    }

    void Result(int i) {
        if (Check()) {
            system("cls");
            PrintBoard();
            if (turn)
                cout << "\n*** Player 1 (O) Won! ***";
            else
                cout << "\n*** Player 2 (X) Won! ***";
            won = turn ? 1 : 2;
            return;
        }
        if (i == 8) {
            system("cls");
            PrintBoard();
            cout << "\n*** Hòa! ***";
            won = 3;
        }
    }

    void Input() {
        cout << "Change block (1-9): ";
        cin >> input;
        while (cin.fail() || input < 1 || input > 9) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Nhập không hợp lệ! Nhập lại (1-9): ";
            cin >> input;
        }
        mark = turn ? 'O' : 'X';
    }

    void PrintBoard() {
        cout << " " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << "\n";
        cout << "---+---+---\n";
        cout << " " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << "\n";
        cout << "---+---+---\n";
        cout << " " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << "\n\n";
        cout << (turn ? "O - Player 1: " : "X - Player 2: ");
    }

    int AddMark() {
        for (int i = 0, k = 1; i < 3; i++) {
            for (int j = 0; j < 3; j++, k++) {
                if (k == input) {
                    if (board[i][j] != 'O' && board[i][j] != 'X') {
                        board[i][j] = mark;
                        return 1;
                    } else return 0;
                }
            }
        }
        return 0;
    }

    int Check() {
        // rows
        for (int i = 0; i < 3; i++)
            if (board[i][0] == mark && board[i][1] == mark && board[i][2] == mark)
                return 1;
        // columns
        for (int i = 0; i < 3; i++)
            if (board[0][i] == mark && board[1][i] == mark && board[2][i] == mark)
                return 1;
        // diagonals
        if (board[0][0] == mark && board[1][1] == mark && board[2][2] == mark) return 1;
        if (board[0][2] == mark && board[1][1] == mark && board[2][0] == mark) return 1;
        return 0;
    }

    void Reset() {
        char start = '1';
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                board[i][j] = start++;
        turn = 1;  // Player 1 bắt đầu
        mark = 'O';
        won = 0;
        input = 0;
    }
};

int main() {
    TicTacToe t;
    char replay;
    do {
        t.Play();
        cout << "\n\nChơi lại? (Y/N): ";
        replay = _getche();
        t.Reset();
    } while (replay == 'y' || replay == 'Y');
    return 0;
}
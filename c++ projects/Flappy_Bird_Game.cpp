#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>
using namespace std;

#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70
#define GAP_SIZE 7
#define PIPE_DIF 35

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

int pipePos[3], gapPos[3], pipeFlag[3];
char bird[2][6] = {
    {'/', '-', '-', 'o', '\\', ' '},
    {'|', '_', '_', '_', ' ', '>'}
};
int birdPos = 6, score = 0;

void gotoxy(int x, int y) {
    CursorPosition.X = x; CursorPosition.Y = y;
    SetConsoleCursorPosition(console, CursorPosition);
}

void setcursor(bool visible, DWORD size) {
    if (size == 0) size = 20;
    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible; lpCursor.dwSize = size;
    SetConsoleCursorInfo(console, &lpCursor);
}

void setcolor(int color) {
    SetConsoleTextAttribute(console, color);
}

void drawBorder() {
    setcolor(11);
    for (int i = 0; i < SCREEN_WIDTH; i++) {
        gotoxy(i, 0); cout << "#";
        gotoxy(i, SCREEN_HEIGHT); cout << "#";
    }
    for (int i = 0; i <= SCREEN_HEIGHT; i++) {
        gotoxy(0, i); cout << "#";
        gotoxy(SCREEN_WIDTH, i); cout << "#";
    }
    for (int i = 0; i <= SCREEN_HEIGHT; i++) {
        gotoxy(WIN_WIDTH, i); cout << "#";
    }
    setcolor(7);
}

void genPipe(int ind) {
    gapPos[ind] = 3 + rand() % 14;
}

void drawPipe(int ind) {
    if (!pipeFlag[ind]) return;
    setcolor(14);
    int x = WIN_WIDTH - pipePos[ind];
    for (int i = 1; i < gapPos[ind]; i++) { gotoxy(x, i); cout << "###"; }
    for (int i = gapPos[ind] + GAP_SIZE; i < SCREEN_HEIGHT; i++) { gotoxy(x, i); cout << "###"; }
    setcolor(7);
}

void erasePipe(int ind) {
    if (!pipeFlag[ind]) return;
    int x = WIN_WIDTH - pipePos[ind];
    for (int i = 1; i < gapPos[ind]; i++) { gotoxy(x, i); cout << "   "; }
    for (int i = gapPos[ind] + GAP_SIZE; i < SCREEN_HEIGHT; i++) { gotoxy(x, i); cout << "   "; }
}

void drawBird() {
    setcolor(10);
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 6; j++) {
            gotoxy(j + 2, i + birdPos);
            cout << bird[i][j];
        }
    setcolor(7);
}

void eraseBird() {
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 6; j++) {
            gotoxy(j + 2, i + birdPos);
            cout << " ";
        }
}

bool collision() {
    int birdX = 2 + 6; 
    for (int k = 0; k < 3; k++) {
        if (!pipeFlag[k]) continue;
        int pipeX = WIN_WIDTH - pipePos[k];
        if (pipeX <= birdX && pipeX + 2 >= 2) {
            if (birdPos < gapPos[k] || birdPos > gapPos[k] + GAP_SIZE) return true;
        }
    }
    return false;
}

void gameover() {
    system("cls");
    cout << "\n\n\t\t===== GAME OVER =====\n";
    cout << "\t\tYour Score: " << score << "\n";
    cout << "\t\tPress any key to return to menu...";
    getch();
}

void updateScore() {
    gotoxy(WIN_WIDTH + 5, 5);
    setcolor(13); cout << "Score: " << score; setcolor(7);
}

void play() {
    birdPos = 6; score = 0;
    for (int i = 0; i < 3; i++) {
        pipeFlag[i] = 1;
        pipePos[i] = 40 + i * PIPE_DIF;
        genPipe(i);
    }

    system("cls");
    drawBorder(); updateScore();
    gotoxy(WIN_WIDTH + 5, 2); cout << "FLAPPY BIRD";
    gotoxy(10, 5); cout << "Press any key to start..."; getch();
    gotoxy(10, 5); cout << "                       ";

    while (true) {
        if (kbhit()) {
            char ch = getch();
            if (ch == 32 && birdPos > 3) birdPos -= 3;
            if (ch == 27) break;
        }
        drawBird(); for (int i = 0; i < 3; i++) drawPipe(i);
        Sleep(80);
        eraseBird(); for (int i = 0; i < 3; i++) erasePipe(i);

        birdPos++;
        for (int i = 0; i < 3; i++) {
            pipePos[i] += 2;
            if (pipePos[i] > WIN_WIDTH + 2) {
                pipePos[i] = 0; genPipe(i); score++;
                updateScore();
            }
        }

        if (birdPos > SCREEN_HEIGHT - 2 || collision()) { gameover(); return; }
    }
}

int main() {
    setcursor(0, 0); srand((unsigned)time(0));
    while (1) {
        system("cls");
        gotoxy(10, 5); cout << "==============================";
        gotoxy(10, 6); cout << "         FLAPPY BIRD          ";
        gotoxy(10, 7); cout << "==============================";
        gotoxy(10, 9); cout << "1. Start Game";
        gotoxy(10, 10); cout << "2. Quit";
        gotoxy(10, 12); cout << "Choose: ";
        char op = getche();
        if (op == '1') play(); else if (op == '2') break;
    }
    return 0;
}
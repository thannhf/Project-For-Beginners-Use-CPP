#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70

// Play area margins
const int PLAY_LEFT = 17;
const int PLAY_RIGHT = WIN_WIDTH - 1 - 17; // adjust to leave margin
const int PLAY_WIDTH = PLAY_RIGHT - PLAY_LEFT + 1;

const int CAR_W = 4;
const int CAR_H = 4;
const int ENEMY_W = 4;
const int ENEMY_H = 4;

const int ENEMY_COUNT = 4; // <-- thay giá trị này để tăng/số xe địch

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

int score = 0;
int carPosX;   // x-coordinate left of car
int carPosY = SCREEN_HEIGHT - CAR_H - 1; // fixed vertical position

// Car sprite (4x4)
char car[CAR_H][CAR_W] = {
    { ' ', '*', '*', ' '},
    { '*', '*', '*', '*'},
    { ' ', '*', '*', ' '},
    { '*', '*', '*', '*'}
};

struct Enemy {
    int x;
    int y;
    bool alive;
};

vector<Enemy> enemies;

// Utility: move cursor
void gotoxy(int x, int y) {
    CursorPosition.X = (SHORT)x;
    CursorPosition.Y = (SHORT)y;
    SetConsoleCursorPosition(console, CursorPosition);
}

// Show/hide console cursor
void setcursor(bool visible, DWORD size=20) {
    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = size;
    SetConsoleCursorInfo(console, &lpCursor);
}

// Set color attribute
void setColor(WORD attr) {
    SetConsoleTextAttribute(console, attr);
}

// Draw play border
void drawBorder() {
    // top/bottom borders across play area
    for (int x = PLAY_LEFT - 2; x <= PLAY_RIGHT + 2; ++x) {
        gotoxy(x, 0);
        setColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        cout << "*";
        gotoxy(x, SCREEN_HEIGHT - 1);
        cout << "*";
    }

    // left & right vertical borders
    for (int y = 0; y < SCREEN_HEIGHT; ++y) {
        gotoxy(PLAY_LEFT - 2, y);
        cout << "*";
        gotoxy(PLAY_RIGHT + 2, y);
        cout << "*";
    }

    // side info separation
    setColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    for (int y = 1; y < SCREEN_HEIGHT - 1; ++y) {
        gotoxy(WIN_WIDTH + 2, y);
        cout << "|";
    }

    setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

// Generate random enemy x within play area
int randEnemyX() {
    // ensure enemy fully inside horizontal play area
    int minX = PLAY_LEFT;
    int maxX = PLAY_RIGHT - ENEMY_W + 1;
    if (maxX < minX) return minX;
    return minX + rand() % (maxX - minX + 1);
}

void initEnemies(int count) {
    enemies.clear();
    enemies.resize(count);
    for (int i = 0; i < count; ++i) {
        enemies[i].x = randEnemyX();
        enemies[i].y = - (rand() % SCREEN_HEIGHT); // stagger spawn
        enemies[i].alive = true;
    }
}

void drawEnemy(const Enemy &e) {
    if (!e.alive) return;
    setColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
    gotoxy(e.x, e.y); cout << "****";
    gotoxy(e.x, e.y + 1); cout << " ** ";
    gotoxy(e.x, e.y + 2); cout << "****";
    gotoxy(e.x, e.y + 3); cout << " ** ";
    setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void eraseEnemy(const Enemy &e) {
    if (!e.alive) return;
    gotoxy(e.x, e.y);     cout << "    ";
    gotoxy(e.x, e.y + 1); cout << "    ";
    gotoxy(e.x, e.y + 2); cout << "    ";
    gotoxy(e.x, e.y + 3); cout << "    ";
}

// Draw car
void drawCar() {
    setColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY); // cyan-ish
    for (int i = 0; i < CAR_H; ++i) {
        for (int j = 0; j < CAR_W; ++j) {
            gotoxy(carPosX + j, carPosY + i);
            cout << car[i][j];
        }
    }
    setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void eraseCar() {
    for (int i = 0; i < CAR_H; ++i) {
        gotoxy(carPosX, carPosY + i);
        cout << "    ";
    }
}

// Bounding-box collision between car and enemy
bool checkCollision(const Enemy &e) {
    if (!e.alive) return false;
    int ex1 = e.x;
    int ex2 = e.x + ENEMY_W - 1;
    int ey1 = e.y;
    int ey2 = e.y + ENEMY_H - 1;

    int cx1 = carPosX;
    int cx2 = carPosX + CAR_W - 1;
    int cy1 = carPosY;
    int cy2 = carPosY + CAR_H - 1;

    // simple AABB
    if (ex1 <= cx2 && ex2 >= cx1 && ey1 <= cy2 && ey2 >= cy1) {
        return true;
    }
    return false;
}

void updateScoreDisplay() {
    gotoxy(WIN_WIDTH + 4, 2);
    setColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    cout << "Score: " << score << "   ";
    setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void showInfoPanel() {
    setColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    gotoxy(WIN_WIDTH + 4, 0); cout << "Car Game";
    setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    gotoxy(WIN_WIDTH + 4, 4); cout << "Controls:";
    gotoxy(WIN_WIDTH + 4, 5); cout << "A - left";
    gotoxy(WIN_WIDTH + 4, 6); cout << "D - right";
    gotoxy(WIN_WIDTH + 4, 7); cout << "Esc - quit";
    gotoxy(WIN_WIDTH + 4, 9); cout << "Enemies: " << enemies.size();
    gotoxy(WIN_WIDTH + 4, 11); cout << "Speed up with score";
}

// Game over screen
void gameOverScreen() {
    system("cls");
    setColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
    cout << "\n\n\n\t\t-------------------------------\n";
    cout << "\t\t----------  GAME OVER  --------\n";
    cout << "\t\t-------------------------------\n\n";
    setColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    cout << "\t\tYour score: " << score << "\n\n";
    setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    cout << "\t\tPress any key to return to menu...";
    getch();
}

// Instructions
void instructionsScreen() {
    system("cls");
    cout << "INSTRUCTIONS\n";
    cout << "------------------\n";
    cout << "Avoid enemy cars by moving left or right.\n";
    cout << "Controls:\n";
    cout << "  A / a : move left\n";
    cout << "  D / d : move right\n";
    cout << "  Esc   : exit to menu\n\n";
    cout << "Press any key to return...";
    getch();
}

// Play loop
void playGame() {
    // init positions
    carPosX = PLAY_LEFT + (PLAY_WIDTH / 2) - (CAR_W / 2);
    score = 0;
    initEnemies(ENEMY_COUNT);

    system("cls");
    drawBorder();
    showInfoPanel();
    updateScoreDisplay();

    gotoxy(PLAY_LEFT + 2, 5);
    cout << "Press any key to start";
    getch();
    gotoxy(PLAY_LEFT + 2, 5);
    cout << "                      ";

    bool running = true;
    int baseDelay = 80; // ms
    while (running) {
        // input
        if (kbhit()) {
            char ch = getch();
            if (ch == 'a' || ch == 'A') {
                if (carPosX - 4 >= PLAY_LEFT) carPosX -= 4;
            } else if (ch == 'd' || ch == 'D') {
                if (carPosX + 4 + CAR_W - 1 <= PLAY_RIGHT) carPosX += 4;
            } else if (ch == 27) { // ESC
                running = false;
                break;
            }
        }

        // draw
        drawCar();
        for (auto &e : enemies) drawEnemy(e);

        // collision check
        for (auto &e : enemies) {
            if (checkCollision(e)) {
                // hit -> end game
                running = false;
                break;
            }
        }
        if (!running) break;

        Sleep(max(20, baseDelay - score*2)); // speed increases with score (min 20ms)

        // erase
        eraseCar();
        for (auto &e : enemies) eraseEnemy(e);

        // update enemies
        for (auto &e : enemies) {
            if (!e.alive) continue;
            e.y += 1 + (score / 10); // increase falling speed slightly with score
            // if passed bottom
            if (e.y > SCREEN_HEIGHT - ENEMY_H - 1) {
                // respawn above
                e.y = - (rand() % 5) - 1;
                e.x = randEnemyX();
                score++;
                updateScoreDisplay();
            }
        }
    }

    // game over
    gameOverScreen();
}

int main() {
    srand((unsigned)time(nullptr));
    setcursor(0, 0);

    do {
        system("cls");
        drawBorder();
        setColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        gotoxy(10, 5); cout << "------------------------";
        gotoxy(10, 6); cout << "|     CAR GAME         |";
        gotoxy(10, 7); cout << "------------------------";
        setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        gotoxy(10, 9); cout << "1. Start Game";
        gotoxy(10, 10); cout << "2. Instructions";
        gotoxy(10, 11); cout << "3. Change difficulty (enemy count)";
        gotoxy(10, 12); cout << "4. Quit";
        gotoxy(10, 14); cout << "Select option: ";
        char op = getche();

        if (op == '1') {
            playGame();
        } else if (op == '2') {
            instructionsScreen();
        } else if (op == '3') {
            gotoxy(10, 16);
            cout << "Enter enemy count (1-8): ";
            int n = 0;
            cin >> n;
            if (n < 1) n = 1;
            if (n > 8) n = 8;
            
            enemies.clear();
            enemies.resize(n);
            initEnemies(n);
            gotoxy(10, 17); cout << "Enemy count set to " << n << ". Press any key...";
            getch();
        } else if (op == '4') {
            setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            system("cls");
            break;
        }
    } while (1);

    return 0;
}
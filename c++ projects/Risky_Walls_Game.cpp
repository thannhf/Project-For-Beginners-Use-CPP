#include <iostream>
#include <graphics.h>
#include <conio.h>
#include <time.h>
#include <stdio.h>

#define ScWidth 1400
#define ScHeight 700
#define OpWidth 400
#define SPACEBAR 32

using namespace std;

// global
char option, txtScore[10];
int score = 0;
int gameRunning = 1;

void GameOver() {
    cleardevice();
    settextstyle(4, 0, 9);
    outtextxy(400, 250, "GAME OVER");

    settextstyle(4, 0, 2);
    outtextxy(500, 420, "Press any key to quit...");
    getch();
    gameRunning = 0;
}

int main() {
    srand((unsigned) time(0));
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    // Enemy: [x, y, height, direction]
    int Enemy[4][4] = {
        {0, 0, 0, 0},
        {0, 0, 0, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 1},
    };

    int ei = 1, ew = 40, eStep = 5;

    // Fruit: [x, y, activeFlag]
    int Fruit[4][3] = {0};

    int fSize = 20;
    int px = (ScWidth - OpWidth) / 2, py = 300, pSize = 20, pStep = 10;

    // khởi tạo cột + quả
    for (int i = 0; i < 4; i++) {
        Enemy[i][0] = ScWidth - OpWidth;
        Fruit[i][0] = Enemy[i][0];
        Fruit[i][2] = 1; // còn tồn tại

        if (i % 2 == 0) {
            Enemy[i][1] = ScHeight / 3 + rand() % (ScHeight / 3);
            Enemy[i][2] = ScHeight - Enemy[i][1];
            Fruit[i][1] = Enemy[i][1] - 70;
        } else {
            Enemy[i][1] = 0;
            Enemy[i][2] = ScHeight / 3 + rand() % (ScHeight / 3);
            Fruit[i][1] = Enemy[i][1] + Enemy[i][2] + 50;
        }
    }

    // Game loop
    while (gameRunning) {
        setcolor(WHITE);
        rectangle(0, 0, ScWidth - OpWidth, ScHeight);
        rectangle(ScWidth - OpWidth, 0, ScWidth, ScHeight);

        // hiển thị điểm
        settextstyle(4, 0, 6);
        sprintf(txtScore, "%d", score);
        outtextxy(ScWidth - 300, 200, txtScore);

        settextstyle(4, 0, 1);
        outtextxy(ScWidth - 370, 500, "Press SPACE to Jump");

        // vẽ cột và quả
        for (int i = 0; i < ei; i++) {
            // vẽ quả nếu còn tồn tại
            if (Fruit[i][2] == 1) {
                setcolor(LIGHTBLUE);
                setfillstyle(1, LIGHTBLUE);
                bar(Fruit[i][0], Fruit[i][1], Fruit[i][0] + fSize, Fruit[i][1] + fSize);
            }

            // vẽ cột vàng
            setfillstyle(1, YELLOW);
            bar(Enemy[i][0], Enemy[i][1], Enemy[i][0] + ew, Enemy[i][1] + Enemy[i][2]);

            // di chuyển sang trái
            Enemy[i][0] -= eStep;
            Fruit[i][0] -= eStep;

            // thêm cột mới khi gần giữa màn hình
            if (Enemy[i][0] <= 750 && Enemy[i][0] > 750 - eStep) {
                if (ei < 4) ei++;
            }

            // reset khi đi hết màn hình
            if (Enemy[i][0] < 0) {
                Enemy[i][0] = ScWidth - OpWidth;
                Fruit[i][0] = Enemy[i][0];
                Fruit[i][2] = 1;

                if (i % 2 == 0) {
                    Enemy[i][1] = ScHeight / 3 + rand() % (ScHeight / 3);
                    Enemy[i][2] = ScHeight - Enemy[i][1];
                    Fruit[i][1] = Enemy[i][1] - 70;
                } else {
                    Enemy[i][1] = 0;
                    Enemy[i][2] = ScHeight / 3 + rand() % (ScHeight / 3);
                    Fruit[i][1] = Enemy[i][1] + Enemy[i][2] + 50;
                }
            }
        }

        // điều khiển nhảy
        if (kbhit()) {
            option = getch();
            if (option == SPACEBAR) {
                if (py > 10) {
                    py -= pStep * 10;
                }
            }
        }

        // vẽ nhân vật (ô trắng)
        setcolor(WHITE);
        setfillstyle(1, WHITE);
        bar(px, py, px + pSize, py + pSize);

        // kiểm tra va chạm với cột
        for (int i = 0; i < ei; i++) {
            if (px + pSize > Enemy[i][0] && px < Enemy[i][0] + ew) {
                if (Enemy[i][3] == 0) { // cột dưới
                    if (py + pSize >= Enemy[i][1]) {
                        GameOver();
                        break;
                    }
                } else { // cột trên
                    if (py <= Enemy[i][1] + Enemy[i][2]) {
                        GameOver();
                        break;
                    }
                }
            }
        }

        // kiểm tra ăn Fruit
        for (int i = 0; i < ei; i++) {
            if (Fruit[i][2] == 1) {
                if (px + pSize > Fruit[i][0] && px < Fruit[i][0] + fSize) {
                    if (py + pSize >= Fruit[i][1] && py <= Fruit[i][1] + fSize) {
                        score += 5;
                        Fruit[i][2] = 0; // đã ăn
                    }
                }
            }
        }

        // tăng điểm khi vượt qua cột
        for (int i = 0; i < ei; i++) {
            if (px + pSize == Enemy[i][0]) {
                score++;
            }
        }

        // trọng lực (rơi xuống)
        if (py + pSize < ScHeight) {
            py += pStep;
        } else {
            GameOver();
            break;
        }

        delay(40);
        cleardevice();
    }

    getch();
    closegraph();
    return 0;
}
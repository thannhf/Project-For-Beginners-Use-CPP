#include<iostream>
#include<graphics.h>
#include<conio.h>
#include<dos.h>
#include<time.h>
#include<stdio.h>

#define ScWidth 1000
#define ScHeight 700

using namespace std;

int main() {
    srand((unsigned) time(0));
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    // Player
    int px = 350, py = 515, pr = 12, pStep = 6;

    // Bar
    int bx = 200, by = 500, bw = 300, bh = 30;

    // Enemy list
    int enemy[5][3] = { { ScWidth / 2, 0, 0 } };
    int ei = 1, eStep = 4, eGap = 0, er = 12;

    char option, txtChances[5], txtScore[5];
    int chances = 3, score = 0;   // sửa lại thành 3

    while(1) {
        // Draw board
        setcolor(WHITE);
        rectangle(0, 0, ScWidth - 300, ScHeight);
        rectangle(ScWidth - 300, 0, ScWidth, ScHeight);

        // UI chances
        settextstyle(4, 0, 3);
        outtextxy(ScWidth - 220, 100, "Chances");
        settextstyle(4, 0, 7);
        outtextxy(ScWidth - 180, 150, itoa(chances, txtChances, 10));

        // UI score
        settextstyle(4, 0, 4);
        outtextxy(ScWidth - 220, 300, "Score");
        settextstyle(4, 0, 7);
        outtextxy(ScWidth - (score < 10 ? 180 : 220), 370, itoa(score, txtScore, 10));

        // Draw bar
        rectangle(bx, by, bx + bw, by + bh);

        // Control
        if(kbhit()) {
            option = getch();
            if(option == 32) pStep = -pStep; // spacebar đổi hướng
        }

        // Draw & update enemies
        for(int i = 0; i < ei; i++) {
            if(enemy[i][2] == 0) {
                setcolor(WHITE); setfillstyle(3, WHITE);
            } else {
                setcolor(GREEN); setfillstyle(3, GREEN);
            }
            fillellipse(enemy[i][0], enemy[i][1], er, er);
            enemy[i][1] += eStep;

            // Nếu rơi quá bar thì reset
            if(enemy[i][1] - er > by + bh) {
                enemy[i][0] = bx + rand() % bw;
                enemy[i][1] = 0;
                if(i == 0) enemy[i][2] = 1; // luôn cho enemy đầu tiên là fruit
            }
        }

        // Sinh enemy mới
        if(ei < 5) {
            eGap = 100 + rand() % 200;
            if(enemy[ei - 1][1] >= eGap) {
                enemy[ei][0] = bx + rand() % bw;
                enemy[ei][1] = 0;
                enemy[ei][2] = 0;
                ei++;
            }
        }

        // Player hit detection
        for(int j = 0; j < ei; j++) {
            if(enemy[j][1] + er >= py - pr) {
                if(px >= enemy[j][0] - er && px <= enemy[j][0] + er) {
                    if(enemy[j][2] == 0) {
                        chances--;
                        enemy[j][1] = 0;
                        if(chances <= 0) {
                            cleardevice();
                            settextstyle(4, 0, 4);
                            outtextxy(300, 200, "Game Over");

                            chances = 3; score = 0; ei = 1;
                            getch();
                        }
                    } else {
                        score += 5;
                        enemy[j][1] = 0;
                    }
                }
            }
        }

        // Draw player
        setcolor(YELLOW); setfillstyle(1, YELLOW);
        fillellipse(px, py, pr, pr);
        px += pStep;

        // Giới hạn player trong bar
        if(px - pr <= bx || px + pr >= bx + bw) {
            pStep = -pStep;
        }

        delay(30);
        cleardevice();
    }

    getch();
    closegraph();
}

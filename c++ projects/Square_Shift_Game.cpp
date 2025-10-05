#include <iostream>
#include <graphics.h>
#include <conio.h>
#include <time.h>
#include <stdio.h>

#define ScWidth 1000
#define ScHeight 700
#define KEY_LEFT 75
#define KEY_RIGHT 77

using namespace std;

int main() {
    srand((unsigned) time(0));
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    // Initial Player
    int iX = 300, iY = 250, gap = 50;
    int Player[4][3] = {
        {iX, iY, 0},
        {iX, iY + gap, 1},
        {iX, iY + gap*2, 0},
        {iX, iY + gap*3, 1}
    };
    int pSize = 20, pStep = 100;

    // Enemy
    int eX, eY, eType = 0, eSize = 20, eTimer = 0, eTime = 10 + rand() % 10;
    do { eX = (1 + rand() % 5) * 100; } while(eX == Player[0][0]);
    eY = 250 + (rand() % 4) * 50;

    int score = 0;
    char txtScore[10];

    while (1) {
        setcolor(WHITE);
        rectangle(0,0, ScWidth-350, ScHeight);
        rectangle(ScWidth-350,0,ScWidth,ScHeight);

        // Score
        settextstyle(4,0,8);
        outtextxy(ScWidth-260,250,itoa(score,txtScore,10));
        settextstyle(4,0,1);
        outtextxy(ScWidth-275,500,"Use Arrow Keys");
        outtextxy(ScWidth-275,540,"to Move Player");

        // Enemy
        if(eType == 0) { setcolor(YELLOW); setfillstyle(1,YELLOW);}
        else { setcolor(WHITE); setfillstyle(1,WHITE);}
        bar(eX,eY,eX+eSize,eY+eSize);

        // Control
        if(kbhit()) {
            char c = getch();
            if(c==0 || c==-32) {
                c = getch();
                if(c == KEY_RIGHT && Player[0][0] < 500) {
                    for(int i=0;i<4;i++) Player[i][0] += pStep;
                } else if(c == KEY_LEFT && Player[0][0] > 100) {
                    for(int i=0;i<4;i++) Player[i][0] -= pStep;
                }
            }
        }

        // Check collision
        for(int i=0;i<4;i++) {
            if(Player[i][0] == eX && Player[i][1] == eY) {
                if(Player[i][2] == eType) {
                    score++;
                    do { eX = (1 + rand()%5)*100; } while(eX==Player[0][0]);
                    eY = 250 + (rand()%4)*50;
                } else {
                    settextstyle(4,0,6);
                    outtextxy(100,100,"Game Over");
                    getch();
                    score = 0;
                }
            }
        }

        // Draw Player
        for(int i=0;i<4;i++) {
            if(Player[i][2]==0) { setcolor(YELLOW); setfillstyle(1,YELLOW); }
            else { setcolor(WHITE); setfillstyle(1,WHITE); }
            bar(Player[i][0],Player[i][1],Player[i][0]+pSize,Player[i][1]+pSize);
        }

        // Enemy type switch
        eTimer++;
        if(eTimer >= eTime) {
            eType = !eType;
            eTimer = 0;
            eTime = 20 + rand()%10;
        }

        delay(30);
        cleardevice();
    }

    getch();
    closegraph();
}
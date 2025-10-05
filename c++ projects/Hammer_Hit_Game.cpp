#include <iostream>
#include <graphics.h>
#include <conio.h>
#include <dos.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define ScWidth 1400
#define ScHeight 700
#define OpWidth 400
#define SPACEBAR 32

using namespace std;

// Enemy: [0]=x, [1]=y (top of shaft), [2]=height(shaft), [3]=type(0 safe,1 danger), [4]=scored(0/1)
int Enemy[5][5] = {
    {0,0,0,0,0},
    {0,0,0,0,0},
    {0,0,0,0,0},
    {0,0,0,0,0},
    {0,0,0,0,0}
};

int NoEnemies = 5;
int ei = 1, eGap = 100, ew = 20, eStep = 12;
int px = (ScWidth - 400) / 2, py = 200, pSize = 40;
int liney = 400;

char txtScore[8];
int score = 0;

void GameOver() {
    cleardevice();
    setcolor(WHITE);
    settextstyle(4, 0, 9);
    outtextxy(300, 300, "Game Over");
    settextstyle(4, 0, 2);
    outtextxy(500, 420, "Press any key to quit...");
    getch();
    closegraph();
    exit(0);
}

// Vẽ tam giác (dùng mảng tĩnh)
void DrawTriangleDown(int x1, int y1, int x2, int y2) {
    int pts[8];
    pts[0] = x1; pts[1] = y1;
    pts[2] = x2; pts[3] = y1;
    pts[4] = (x1 + x2) / 2; pts[5] = y2;
    pts[6] = x1; pts[7] = y1;
    fillpoly(4, pts);
}

void DrawNail(int i) {
    // Shaft (bar up), head (rectangle), tip (triangle)
    int x = Enemy[i][0];
    int y = Enemy[i][1]; // top of shaft
    int h = Enemy[i][2]; // shaft height (downwards)
    // shaft (thin vertical)
    bar(x - ew/2, y - h, x + ew + ew/2, y);
    // lower shaft part (downwards)
    bar(x, y, x + ew, y + h);
    // tip triangle below the shaft
    DrawTriangleDown(x, y + h, x + ew, y + h + ew);
}

bool rectOverlap(int ax1,int ay1,int ax2,int ay2,int bx1,int by1,int bx2,int by2) {
    return !(ax2 <= bx1 || ax1 >= bx2 || ay2 <= by1 || ay1 >= by2);
}

// Kiểm tra va chạm giữa player (rectangle) và nail (tách thành bounding rects)
int PlayerHitEnemy() {
    int playerLeft = px - pSize/2;
    int playerTop = py - pSize*2;
    int playerRight = px + pSize + pSize/2;
    int playerBottom = py + pSize;

    for(int i = 0; i < ei; i++) {
        int nx = Enemy[i][0];
        int ny = Enemy[i][1];
        int nh = Enemy[i][2];

        // bounding boxes for nail parts
        // top shaft bounding
        int sx1 = nx - ew/2, sy1 = ny - nh, sx2 = nx + ew + ew/2, sy2 = ny;
        // lower shaft
        int lx1 = nx, ly1 = ny, lx2 = nx + ew, ly2 = ny + nh;
        // tip bounding (approximate triangle with rect)
        int tx1 = nx, ty1 = ny + nh, tx2 = nx + ew, ty2 = ny + nh + ew;

        // if overlap ANY part -> collision/hit
        if(rectOverlap(playerLeft, playerTop, playerRight, playerBottom, sx1, sy1, sx2, sy2) ||
           rectOverlap(playerLeft, playerTop, playerRight, playerBottom, lx1, ly1, lx2, ly2) ||
           rectOverlap(playerLeft, playerTop, playerRight, playerBottom, tx1, ty1, tx2, ty2)) {
            if(Enemy[i][3] == 1) { // dangerous
                return -2;
            } else {
                if(Enemy[i][4] == 0) { // not yet scored
                    Enemy[i][4] = 1;
                    return i;
                } else {
                    return -1; // already scored this nail
                }
            }
        }
    }
    return -1;
}

int main() {
    srand((unsigned) time(0));
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    // Initialize first enemy
    Enemy[0][0] = ScWidth - OpWidth;
    Enemy[0][1] = liney - 100; // top of shaft
    Enemy[0][2] = 100; // shaft height
    Enemy[0][3] = rand() % 2; // type
    Enemy[0][4] = 0; // scored flag

    // other enemies initial positions (off-screen)
    for(int i=1;i<NoEnemies;i++){
        Enemy[i][0] = ScWidth - OpWidth + i*200;
        Enemy[i][1] = liney - 100;
        Enemy[i][2] = 100;
        Enemy[i][3] = rand()%2;
        Enemy[i][4] = 0;
    }

    while(1) {
        setcolor(WHITE);

        rectangle(0, 0, ScWidth - OpWidth, ScHeight);
        rectangle(ScWidth - OpWidth, 0, ScWidth, ScHeight);

        line(0, liney, ScWidth - OpWidth, liney);

        // draw score
        snprintf(txtScore, sizeof(txtScore), "%d", score);
        settextstyle(4, 0, 9);
        if(score < 10) outtextxy(ScWidth - 270, 250, txtScore);
        else outtextxy(ScWidth - 320, 250, txtScore);

        settextstyle(4, 0, 1);
        outtextxy(ScWidth - 375, 500, "Use spacebar to hammer");

        // Draw & move enemies
        for(int i = 0; i < ei; i++) {
            if(Enemy[i][3] == 0) {
                setcolor(LIGHTBLUE);
                setfillstyle(1, LIGHTBLUE);
            } else {
                setcolor(LIGHTRED);
                setfillstyle(1, LIGHTRED);
            }
            DrawNail(i);
            Enemy[i][0] -= eStep;

            if(Enemy[i][0] <= 820 && Enemy[i][0] > 820 - eStep) {
                if(ei < NoEnemies) {
                    ei++;
                    // initialize newly activated enemy
                    Enemy[ei-1][0] = ScWidth - OpWidth;
                    Enemy[ei-1][1] = liney - 100;
                    Enemy[ei-1][2] = 100;
                    Enemy[ei-1][3] = rand()%2;
                    Enemy[ei-1][4] = 0;
                }
            }

            if(Enemy[i][0] < -50) { // moved past left
                Enemy[i][0] = ScWidth - OpWidth;
                Enemy[i][3] = rand() % 2;
                Enemy[i][1] = liney - 100;
                Enemy[i][2] = 100;
                Enemy[i][4] = 0; // reset scored
            }
        }

        // input
        if(kbhit()) {
            char option = getch();
            if(option == SPACEBAR) {
                int tmpEi = PlayerHitEnemy();
                if(tmpEi == -2) {
                    GameOver();
                } else if(tmpEi >= 0) {
                    // scored safe nail
                    score++;
                    // push nail down visually (simulate hit)
                    Enemy[tmpEi][1] += 100;
                }
                // hammer animation: move player up briefly
                py += 200;
                // draw player during hammer
                setcolor(WHITE);
                setfillstyle(1, WHITE);
                bar(px - pSize/2, py - pSize*2, px + pSize + pSize/2, py);
                bar(px, py, px + pSize, py + pSize);
                delay(200);
                py -= 200;
            }
        }

        // draw player normal
        setcolor(WHITE);
        setfillstyle(1, WHITE);
        bar(px - pSize/2, py - pSize*2, px + pSize + pSize/2, py);
        bar(px, py, px + pSize, py + pSize);

        delay(20);
        cleardevice();
    }

    closegraph();
    return 0;
}
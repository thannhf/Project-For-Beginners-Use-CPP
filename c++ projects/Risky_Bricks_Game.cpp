#include<iostream>
#include<graphics.h>
#include<conio.h>
#include<dos.h>
#include<time.h>
#include<stdio.h>
#include<math.h>

#define ScWidth 1400
#define ScHeight 700
#define OpWidth 400
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 77
#define KEY_RIGHT 75
#define SPACEBAR 32

using namespace std;

void GameOver();
void DrawBoard();
int EnemyHitPlayer();
int PlayerHitFruit();

int pSize = 40, step = 20;
double px = ((ScWidth - OpWidth) / 2), py = 350;

double enemy[3][3] = {
	0, 200, 10, 0, 320, 10, 0, 440, 10
};
int ei = 1, ew = 80, eh = 40;

int fx = px, fy = ScHeight / 2, fSize = 20;

char option, txtScore[5];
int score = 0;

int main() {
	srand((unsigned) time(0));
	
	int gd = DETECT, gm, err, tmp;
	initgraph(&gd, &gm, "");
	
	while(1) {
		DrawBoard();
		
		setcolor(WHITE);
		setfillstyle(1, WHITE);
		fillellipse(px, py, pSize, pSize);
		
		setcolor(LIGHTBLUE);
		setfillstyle(1, LIGHTBLUE);
		fillellipse(fx, fy, fSize, fSize);
		
		if(kbhit()) {
			option = getch();
			if(option == SPACEBAR) {
				if(step <= 1 && step >= -1) {
					step *= 20;
				} else {
					step /= 20;
				}
			}
		}
		
		if(PlayerHitFruit() == 1) {
			score++;
			fy = 150 + rand() % 400;
		}
		
		if(EnemyHitPlayer() == 1) {
			GameOver();
			
			enemy[0][0] = 0;
			enemy[0][1] = 260;
			enemy[0][2] = 8 + rand() % 8;
			enemy[1][0] = 0;
			enemy[1][1] = 320;
			enemy[1][2] = 8 + rand() % 8;
			enemy[2][0] = 0;
			enemy[2][1] = 390;
			enemy[2][2] = 8 + rand() % 8;
		}
		
		for(int i = 0; i < ei; i++) {
			setcolor(YELLOW);
			setfillstyle(1, YELLOW);
			bar(enemy[i][0], enemy[i][1], enemy[i][0] + ew, enemy[i][1] + eh);
			
			enemy[i][0] += enemy[i][2];
			
			if(enemy[i][0] >= 1000) {
				enemy[i][0] = 0;
				enemy[i][2] = 8 + rand() % 8;
			}
			
			if(enemy[i][0] >= 300 && enemy[i][0] < 310) {
				if(ei < 3) {
					ei++;
				}
			}
		}
		
		py += step;
		
		if(py > 600 || py < 100) {
			step = -step;
		}
		
		delay(40);
		cleardevice();
	}
	getch();
	closegraph();
}

void GameOver() {
	cleardevice();
	
	setcolor(WHITE);
	
	settextstyle(4, 0, 9);
	outtextxy(300, 300, "Game Over");
	
	settextstyle(4, 0, 2);
	outtextxy(500, 420, "Press any key to restart...");
	getch();
	score = 0;
}

void DrawBoard() {
	setcolor(WHITE);
	
	rectangle(0, 0, ScWidth - OpWidth, ScHeight);
	rectangle(ScWidth - OpWidth, 0, ScWidth, ScHeight);
	
	settextstyle(4, 0, 4);
	outtextxy(ScWidth - 340, 50, "Risky Bricks");
	
	settextstyle(4, 0, 9);
	if(score < 10) {
		outtextxy(ScWidth - 270, 250, itoa(score, txtScore, 10));
	} else if(score >= 10) {
		outtextxy(ScWidth - 320, 250, itoa(score, txtScore, 10));
	}
	
	settextstyle(4, 0, 1);
	outtextxy(ScWidth - 375, 500, "Controls: ");
	outtextxy(ScWidth - 300, 550, "Use Spacebar to ");
	outtextxy(ScWidth - 300, 580, "Toggle speed");
}

int EnemyHitPlayer() {
	for(int i = 0; i < ei; i++) {
		if((px - pSize <= enemy[i][0] + ew && px - pSize >= enemy[i][0]) || (px + pSize >= enemy[i][0] && px + pSize <= enemy[i][0] + ew)) {
			if((py - pSize <= enemy[i][1] + eh && py - pSize >= enemy[i][1]) || (py + pSize >= enemy[i][1] && py + pSize <= enemy[i][1] + eh)) {
				return 1;
			}
		}
	}
	return 0;
}

int PlayerHitFruit() {
	if(py - pSize <= fy + fSize && py - pSize >= fy - fSize) {
		return 1;
	}
	
	if(py + pSize <= fy - fSize && py + pSize >= fy + fSize) {
		return 1;
	}
	return 0;
}
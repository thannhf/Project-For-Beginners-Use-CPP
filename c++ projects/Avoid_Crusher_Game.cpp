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
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define SPACEBAR 32

using namespace std;

void GameOver();
void DrawBoard();
int PlayerHitFruit();
void DrawCrusherUp();
void DrawCrusherDown();

int e1x = 350, e1y = 200, e2x = 350, e2y = 200;
int e1Step = 3, e2Step = 3, eh = 100, ew = 100;
int e1Init = e1y, e1Limit = 235, e2Init = e2y, e2Limit = 165;

int px = 485, py = 322;
int ph = 30, pw = 30, pStep = 100;

int fx = 485, fy = py, fStep = -100;

char option, txtScore[5];
int score = 0;

int main() {
	srand((unsigned) time(0));
	
	int gd = DETECT, gm, err, tmp;
	initgraph(&gd, &gm, "");
	
	while(1) {
		DrawBoard();
		DrawCrusherUp();
		DrawCrusherDown();
		
		setfillstyle(1, LIGHTGREEN);
		bar(fx + fStep, fy, fx + fStep + 30, fy + 30);
		
		setfillstyle(1, LIGHTBLUE);
		bar(px, py, px + pw, py + ph);
		
		if(kbhit()) {
			option = getch();
			switch(option) {
				case KEY_LEFT:
					px -= pStep;
					break;
				case KEY_RIGHT:
					px += pStep;
					break;
			}
		}
		
		if(PlayerHitCollider() == 1) {
			delay(300);
			GameOver();
		}
		
		if(PlayerHitFruit() == 1) {
			score++;
			if(rand() % 2 == 1) {
				fStep = -100;
			} else {
				fStep = 100;
			}
		}
		
		e1y += e1Step;
		if(e1y < e1Init || e1y > e1Limit) {
			e1Step = -e1Step;
		}
		
		e2y -= e2Step;
		if(e2y > e2Init || e2y < e2Limit) {
			e2Step = -e2Step;
		}
		
		delay(80);
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
	px = 485;
}

void DrawBoard() {
	rectangle(0, 0, ScWidth - OpWidth, ScHeight);
	rectangle(ScWidth - OpWidth, 0, ScWidth, ScHeight);
	
	settextstyle(4, 0, 4);
	outtextxy(ScWidth - 380, 50, "Avoid Crusher");
	
	settextstyle(4, 0, 9);
	if(score < 10) {
		outtextxy(ScWidth - 270, 250, itoa(score, txtScore, 10));
	} else if(score >= 10) {
		outtextxy(ScWidth - 320, 250, itoa(score, txtScore, 10));
	}
	
	settextstyle(4, 0, 1);
	outtextxy(ScWidth - 375, 500, "Controls: ");
	outtextxy(ScWidth - 300, 540, "- Arrow Keys");
}

int PlayerHitCollider() {
	if(px < 485 || px > 485) {
		if(e1y + eh >= py || 2 * e2y <= py + ph) {
			return 1;
		}
	}
	return 0;
}

int PlayerhitFruit() {
	if(px == fx + fStep) {
		return 1;
	}
	return 0;
}

void DrawCrusherUp() {
	int offset = e1x;
	setfillstyle(1, WHITE);
	bar(e1x, e1y, e1x + ew, e1y + eh);
	offset = offset + ew;
	bar(offset, e1y, offset + ew, e1y + eh / 2);
	offset = offset + ew;
	bar(offset , e1y, offset + ew, e1y + eh);
}

void DrawCrusherDown() {
	int offsetX = e2x;
	int offsetY = e2y;
	setfillstyle(1, WHITE);
	bar(e2x, offsetY + e2y, e2x + ew, offsetY + e2y + eh);
	offsetX = offsetX + ew;
	bar(offsetX, offsetY + e2y + eh / 2, offsetX + ew, offsetY + e2y + eh);
	offsetX = offsetX + ew;
	bar(offsetX, offsetY + e2y, offsetX + ew, offsetY + e2y + eh);
}
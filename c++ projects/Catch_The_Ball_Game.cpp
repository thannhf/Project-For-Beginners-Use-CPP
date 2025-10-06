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
#define SPACEBAR

using namespace std;

void GameOver();
void DrawBoard();
int circleCollideCircle(int x1, int y1, int size1, int x2, int y2, int size2);
int rSize = 56;
int rx = ((ScWidth - OpWidth) / 2), ry = 350;
int pSize = 50, step = 30;
double px = ((ScWidth - OpWidth) / 2), py = 350;
char option, txtScore[5];
int score = 0;

int main() {
	srand((unsigned) time(0));
	int gd = DETECT, gm, err, tmp;
	initgraph(&gd, &gm, "");
	
	while(1) {
		DrawBoard();
		circle(rx, ry, rSize);
		
		setcolor(YELLOW);
		setfillstyle(1, YELLOW);
		fillellipse(px, py, pSize, pSize);
		
		if(kbhit()) {
			option = getch();
			if(option == SPACEBAR) {
				if(circleCollideCircle(px, py, pSize, rx, ry, rSize) == 1) {
					score++;
				} else if(circleCollideCircle(px, py, pSize, rx, ry, rSize) == 2) {
					score += 5;
					setcolor(LIGHTGREEN);
					setfillstyle(1, LIGHTGREEN);
					fillellipse(px, py, pSize, pSize);
					delay(100);
				} else {
					GameOver();
				}
				delay(100);
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
	outtextxy(ScWidth - 375, 50, "Catch the Ball");
	
	settextstyle(4, 0, 9);
	if(score < 10) {
		outtextxy(ScWidth - 270, 250, itoa(score, txtScore, 10));
	} else if(score >= 10) {
		outtextxy(ScWidth - 320, 250, itoa(score, txtScore, 10));
	}
	
	settextstyle(4, 0, 1);
	outtextxy(ScWidth - 375, 500, "Controls: ");
	outtextxy(ScWidth - 300, 550, "Spacebar to stop");
}

int circleCollideCircle(int x1, int y1, int size1, int x2, int y2, int size2) {
	if(y1 == y2) {
		return 2;
	}
	if(y1 - size1 <= y2 + size2 && y1 - size1 >= y2 - size2) {
		return 1;
	} else if(y1 + size1 >= y2 - size2 && y1 - size1 <= y2 - size2) {
		return 1;
	}
	return 0;
}
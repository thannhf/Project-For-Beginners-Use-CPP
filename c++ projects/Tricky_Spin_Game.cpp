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

using namespace std;

void GameOver();
void DrawBoard();
int EnemyHitPlayer();
static double d2r(double degree);
double px, py;
int pSize = 20, step = 8;
double enemy[3][3] = {
	0, 260, 10, 0, 320, 10, 0, 390, 10
};
int ei = 1;
char option, txtScore[5];
int score = 0;

int main() {
	srand((unsigned) time(0));
	int gd = DETECT, gm, err, tmp;
	initgraph(&gd, &gm, "");
	int i = 0;
	while(1) {
		DrawBoard();
		setcolor(WHITE);
		circle(500, 350, 100);
		
		if(kbhit()) {
			option = getch();
			if(option == 32) {
				step = -step;
			}
		}
		
		for(int i = 0; i < ei; i++) {
			setcolor(YELLOW);
			setfillstyle(1, YELLOW);
			bar(enemy[i][0], enemy[i][1], enemy[i][0] + 40, enemy[i][1] + 20);
			
			if(enemy[i][0] >= 600 && enemy[i][0] < 610) {
				score++;
			}
			
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
		
		px = 500 + -1 * sin(d2r(i)) * 90;
		py = 350 + -1 * cos(d2r(i)) * 90;
		
		setcolor(WHITE);
		setfillstyle(1, WHITE);
		fillellipse(px, py, pSize, pSize);
		
		i += step;
		
		if(i > 360) {
			i = 0;
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
	
	settextstyle(4, 0, 9);
	if(score < 10) {
		outtextxy(ScWidth - 270, 250, itoa(score, txtScore, 10));
	} else if(score >= 10) {
		outtextxy(ScWidth - 320, 250, itoa(score, txtScore, 10));
	}
	
	settextstyle(4, 0, 1);
	outtextxy(ScWidth - 375, 500, "Controls: ");
	outtextxy(ScWidth - 300, 550, "Spacebar");
}

int EnemyHitPlayer() {
	for(int i = 0; i < ei; i++) {
		if(enemy[i][0] + 40 >= px - pSize && enemy[i][0] <= px + pSize) {
			if(py + pSize >= enemy[i][1] && py <= enemy[i][1]) {
				return 1;
			}
		}
	}
	return 0;
}

static double d2r(double degree) {
	double pi = 3.14159265359;
	return (degree * (pi / 180));
}
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
int BulletHitEnemy();
static double d2r(double degree);
int pSize = 20, step = 20;
double px = 1000 - pSize, py = 300;
int bullet[30][3], bi = 0;
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
	
	for(int i = 0; i < 30; i++) {
		bullet[bi][0] = bullet[bi][1] = bullet[bi][2] = 0;
	}
	
	while(1) {
		DrawBoard();
		
		if(kbhit()) {
			option = getch();
			if(option == KEY_UP) {
				if(py > 200) {
					py -= step;
				}
			} else if(option == KEY_DOWN) {
				if(py < 450) {
					py += step;
				}
			} else if(option == SPACEBAR) {
				bullet[bi][0] = 1000;
				bullet[bi][1] = py + pSize * 1.5;
				bullet[bi][2] = 1;
				
				if(bi < 29) {
					bi++;
				} else {
					bi = 0;
				}
			}
		}
		
		for(int i = 0; i < 30; i++) {
			if(bullet[i][2] != 0) {
				circle(bullet[i][0], bullet[i][1], 5);
			}
			if(bullet[i][0] >= 0) {
				bullet[i][0] -= 10;
			} else {
				bullet[i][2] = 0;
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
		
		for(int i = 0; i < ei; i++) {
			setcolor(YELLOW);
			setfillstyle(1, YELLOW);
			bar(enemy[i][0], enemy[i][1], enemy[i][0] + 40, enemy[i][1] + 20);
			
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
		
		if(BulletHitEnemy() == 1) {
			score++;
		}
		
		setcolor(WHITE);
		setfillstyle(1, WHITE);
		bar(px, py, px + pSize, py + pSize * 3);
		bar(px - pSize, py + pSize, px, py + pSize * 2);
		
		delay(40);
		cleardevice();
	}
	
	getch();
	cleardevice();
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
	outtextxy(ScWidth - 300, 550, "Up Arrow - Move Upward");
	outtextxy(ScWidth - 300, 600, "Down Arrow - Move Downward");
	outtextxy(ScWidth - 300, 650, "Spacebar - Fire");
}

int EnemyHitPlayer() {
	for(int i = 0; i < ei; i++) {
		if(enemy[i][0] >= px - pSize && enemy[i][0] <= px + pSize) {
			if((enemy[i][1] <= py + pSize * 3 && enemy[i][1] >= py) || (enemy[i][1] + 20 >= py && enemy[i][1] + 20 <= py)) {
				return 1;
			}
		}
	}
	return 0;
}

int BulletHitEnemy() {
	for(int i = 0; i < 30; i++) {
		if(bullet[i][2] == 1) {
			for(int j = 0; j < ei; j++) {
				if(enemy[j][0] + 40 >= bullet[i][0] - 10 && enemy[j][0] <= bullet[i][0] + 10) {
					if(bullet[i][1] >= enemy[j][1] && bullet[i][1] <= enemy[j][1] + 20) {
						enemy[j][0] = 0;
						bullet[i][2] = 0;
						return 1;
					}
				}
			}
		}
	}
	return 0;
}

static double d2r(double degree) {
	double pi = 3.14159265359;
	return (degree * (pi / 180));
}
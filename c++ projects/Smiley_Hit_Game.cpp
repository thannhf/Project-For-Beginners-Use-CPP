#include<iostream>
#include<graphics.h>
#include<conio.h>
#include<dos.h>
#include<time.h>
#include<stdio.h>

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
void DrawEnemies();
void DrawPlayer();
int PlayerHitEnemy();
char option, txtScore[5];
int score = 0;
const int NoEnemies = 3;

int Enemy[NoEnemies][4] = {
	{300, 500, 0, 0},
	{500, 500, 1, 0},
	{700, 500, 0, 0}
};

int eSize = 50, eStep = -10, ei = 0;
int pw = 70, ph = 100, px = 500 - pw / 2, py = 150;
int lx = 200, ly = 400, lw = 800;
int i = 0; timer;

int main() {
	srand((unsigned) time(0));
	timer = 5 + rand() % 5;
	
	int gd = DETECT, gm, err, tmp;
	initgraph(&gd, &gm, "");
	
	while(1) {
		setcolor(WHITE);
		DrawBoard();
		
		line(lx, ly, lw, ly);
		
		for(int i = 0; i < NoEnemies; i++) {
			setcolor(YELLOW);
			DrawEnemies();
		}
		
		Enemy[ei][1] + eStep;
		if(Enemy[ei][1] < 350) {
			eStep = -eStep;
		}
		if(Enemy[ei][1] > 500) {
			ei = rand() % 3;
			eStep = -10;
			Enemy[0][2] = Enemy[1][2] = Enemy[2][2] = 0;
		}
		if(i == timer) {
			Enemy[ei][2] = (Enemy[ei][2] == 0 ? 1 : 0);
			i = 0;
			timer = 10 + rand() % 5;
		}
		if(kbhit()) {
			option = getch();
			if(option == KEY_LEFT) {
				if(px + pw / 2 > 300) {
					px -= 200;
				}
			} else if(option == KEY_RIGHT) {
				if(px + pw / 2 < 700) {
					px += 200;
				} 
			} else if(option == SPACEBAR) {
				py += 150;
				DrawPlayer();
				delay(200);
				
				if(PlayerHitEnemy() == 1) {
					score++;
				} else if(PlayerHitEnemy() == 2) {
					GameOver();
				}
				py -= 150;
			}
		}
		DrawPlayer();
		i++
		delay(40);
		cleardevice();
	}
	closegraph();
}

int PlayerHitEnemy() {
	if(px + pw / 2 == Enemy[ei][0]) {
		if(py + ph >= Enemy[ei][1] - eSize) {
			if(Enemy[ei][2] == 0) {
				return 1;
			} else {
				return 2;
			}
		}
	}
	return 0;
}

void DrawEnemies() {
	for(int i = 0; i < NoEnemies; i++) {
		if(Enemy[i][2] == 0) {
			setcolor(YELLOW);
		} else {
			setcolor(LIGHTRED);
		}
		circle(Enemy[i][0], Enemy[i][1], eSize);
		circle(Enemy[i][0] - eSize / 3, Enemy[i][1] - eSize / 3, 5);
		circle(Enemy[i][0] + eSize / 3, Enemy[i][1] - eSize / 3, 5);
		arc(Enemy[i][0], Enemy[i][1], 180, 360, eSize / 2);
	}
}

void DrawPlayer() {
	setcolor(WHITE);
	setfillstyle(1, WHITE);
	
	bar(px, py, px + pw, py + ph);
	
	bar(px + pw, py + ph / 2 - 20, px + pw + 20, py + ph / 2 + 20);
	bar(px + pw + 25, py + ph / 2 - 20, px + pw + 45, py + ph / 2 + 20);
	bar(px + pw + 50, py + ph / 2 - 20, px + pw + 75, py + ph / 2 + 20);
	bar(px + pw + 80, py + ph / 2 - 20, px + pw + 105, py + ph / 2 + 20);
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
	
	settextstyle(4, 0, 5);
	outtextxy(ScWidth - 375, 50, "Smiley Hit");
	
	settextstyle(4, 0, 9);
	if(score < 10) {
		outtextxy(ScWidth - 270, 250, itoa(score, txtScore, 10));
	} else if(score >= 10) {
		outtextxy(ScWidth - 320, 250, itoa(score, txtScore, 10));
	}
	
	settextstyle(4, 0, 1);
	outtextxy(ScWidth - 375, 500, "Controls: ");
	outtextxy(ScWidth - 300, 550, "Spacebar to Hit");
	outtextxy(ScWidth - 300, 600, "Left Arrow Key");
	outtextxy(ScWidth - 300, 650, "Right Arrow Key");
}
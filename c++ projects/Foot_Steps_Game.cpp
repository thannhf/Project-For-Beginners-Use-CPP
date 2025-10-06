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
int EnemyHitPlayer();
int PlayerHitFruit();

int pSize = 40, step = 20;
int dir = 0;
double px = ((ScWidth - OpWidth) / 2), py = 350;

int path[2000][2];
int pathIndex = 0;

double enemy[100][3];
int ei = 0, eSize = 10, eStep = 10;
int eGen = 0;
int fx = px, fy = ScHeight / 2, fSize = 10;
char option, txtScore[5];
int score = 0;

int main() {
	srand((unsigned) time(0));
	
	int gd = DETECT, gm, err, tmp;
	initgraph(&gd, &gm, "");
	
	for(int i = 0; i < 2000; i++) {
		path[i][0] = path[i][1] = 0;
	}
	
	path[0][0] = px;
	path[0][1] = py;
	
	while(1) {
		DrawBoard();
		
		setcolor(WHITE);
		setfillstyle(1, WHITE);
		bar(px, py, px + pSize, py + pSize);
		
		setcolor(LIGHTGREEN);
		setfillstyle(1, LIGHTGREEN);
		fillellipse(fx, fy, fSize, fSize);
		
		if(kbhit()) {
			option = getch();
			if(option == KEY_UP) {
				dir = 0;
			} else if(option == KEY_RIGHT) {
				dir = 1;
			} else if(option == KEY_DOWN) {
				dir = 2;
			} else if(option == KEY_LEFT) {
				dir = 3;
			}
		}
		
		if(pathIndex > 0) {
			for(int i = 0; i < ei; i++) {
				int tmpEnemyLoc = enemy[i][2];
				enemy[i][0] = path[tmpEnemyLoc][0];
				enemy[i][1] = path[tmpEnemyLoc][1];
				enemy[i][2]++;
				
				setcolor(LIGHTRED);
				setfillstyle(1, LIGHTRED);
				fillellipse(enemy[i][0], enemy[i][1], eSize, eSize);
			}
		}
		
		if(eGen = 30) {
			enemy[ei][2] = 0;
			ei++;
			eGen = 0;
		}
		eGen++;
		
		if(EnemyHitPlayer() == 1) {
			GameOver();
			score = 0;
			pathIndex = 0;
			eGen = 0;
			ei = 0;
		}
		
		if(PlayerHitFruit() == 1) {
			score++;
			fy = 150 + rand() % 400;
		}
		
		path[pathIndex][0] = px;
		path[pathIndex][1] = py;
		
		if(dir == 0) py -= step;
		else if(dir == 1) px += step;
		else if(dir == 2) py += step;
		else if(dir == 3) px -= step;
		
		if(px <= 0) px = 0;
		if(py <= 0) py = 0;
		if(px + pSize >= 1000) px = 1000 - pSize;
		if(py + pSize >= 700) py = 700 - pSize;
		
		if(pathIndex != 0) {
			if(path[pathIndex][0] == px && path[pathIndex][1] == py) {
				pathIndex--;
			}
		}
		
		pathIndex++;
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
	outtextxy(ScWidth - 340, 50, "Foot Steps");
	
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

int EnemyHitPlayer() {
	for(int i = 0; i < ei; i++) {
		if(enemy[i][0] >= px && enemy[i][0] <= px + pSize) {
			if(enemy[i][1] >= py && enemy[i][1] <= py + pSize) {
				delay(500);
				return 1;
			}
		}
	}
	return 0;
}

int PlayerHitFruit() {
	if(fx >= px && fx <= px + pSize) {
		if(fy >= py && fy <= py + pSize) {
			return 1;
		}
	}
	return 0;
}
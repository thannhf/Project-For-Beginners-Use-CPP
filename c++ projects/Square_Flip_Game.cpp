#include<iostream>
#include<graphics.h>
#include<conio.h>
#include<dos.h>
#include<time.h>
#include<stdio.h>

#define ScWidth 1400
#define ScHeight 700
#define OpWidth 400
#define SPACEBAR 32

using namespace std;

char option, txtScore[5];
int score = 1;

void GameOver() {
	cleardevice();
	
	settextstyle(4, 0, 9);
	outtextxy(300, 300, "Game Over");
	
	settextstyle(4, 0, 2);
	outtextxy(500, 420, "Press any key to quit...");
	getch();
	score = 0;
}

void DrawTriangleUp(int x1, int y1, int x2, int y2) {
	fillpoly(4, new int[8] {
		x1, y2, x2, y2, (x1 + x2) / 2, y1, x1, y2
	});
}

void DrawTriangleDown(int x1, int y1, int x2, int y2) {
	fillpoly(4, new int[8] {
		x1, y1, x2, y1, (x1 + x2) / 2, y2, x1, y1
	});
}

int main() {
	srand((unsigned) time(0));
	int gd = DETECT, gm, err, tmp;
	initgraph(&gd, &gm, "");
	
	int Enemy[8][4] = {
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0}
	};
	
	int ei = 1, eGap = 100, ew = 20, eStep = 10, NoEnemies = 8;
	int px = (ScWidth - 400) / 2, py = 300 - 2, pSize = 20;
	int linex = px + pSize, liney = py + pSize;
	
	Enemy[0][0] = ScWidth - OpWidth;
	Enemy[0][1] = liney + 2;
	Enemy[0][2] = pSize;
	
	while(1) {
		setcolor(WHITE);
		rectangle(0, 0, ScWidth - OpWidth, ScHeight);
		rectangle(ScWidth - OpWidth, 0, ScWidth, ScHeight);
		
		line(0, liney, ScWidth - OpWidth, liney);
		
		settextstyle(4, 0, 9);
		if(score < 10) {
			outtextxy(ScWidth - 270, 250, itoa(score, txtScore, 10));
		} else if(score >= 10) {
			outtextxy(ScWidth - 320, 250, itoa(score, txtScore, 10));
		}
		settextstyle(4, 0, 1);
		outtextxy(ScWidth - 375, 500, "use spacebar to jump");
		
		for(int i = 0; i < ei; i++) {
			setcolor(YELLOW);
			setfillstyle(1, YELLOW);
			if(Enemy[i][3] == 0) {
				DrawTriangleDown(Enemy[i][0], Enemy[i][1], Enemy[i][0] + ew, Enemy[i][1] + Enemy[i][2]);
			} else {
				DrawTriangleUp(Enemy[i][0], Enemy[i][1], Enemy[i][0] + ew, Enemy[i][1] + Enemy[i][2]);
			}
			Enemy[i][0] -= eStep;
			
			if(Enemy[i][0] <= 900 && Enemy[i][0] > 900 - eStep) {
				if(ei < NoEnemies) {
					ei++;
					break;
				}
			}
			
			if(Enemy[i][0] < 0) {
				Enemy[i][0] = ScWidth - OpWidth;
				Enemy[i][3] = rand() % 2;
				
				if(Enemy[i][3] == 0) {
					Enemy[i][1] = liney;
					Enemy[i][2] = pSize;
				} else {
					Enemy[i][1] = liney - pSize;
					Enemy[i][2] = pSize;
				}
			}
		}
		
		if(kbhit()) {
			option = getch();
			if(option == SPACEBAR) {
				if(py < liney) {
					py += pSize;
				} else {
					py -= pSize;
				}
			}
		}
		
		setcolor(WHITE);
		setfillstyle(1, WHITE);
		bar(px, py, px + pSize, py + pSize);
		
		for(int i = 0; i < NoEnemies; i++) {
			if(px + pSize > Enemy[i][0] && px < Enemy[i][0] + ew) {
				if(py + pSize / 2 >= Enemy[i][1] && py + pSize / 2 <= Enemy[i][1] + Enemy[i][2]) {
					GameOver();
					break;
				}
			}
		}
		
		for(int i = 0; i < NoEnemies; i++) {
			if(px + pSize / 2 >= Enemy[i][0] && px + pSize / 2 <= Enemy[i][0]) {
				score++;
			}
		}
		
		delay(40);
		cleardevice();
	}
	
	getch();
	closegraph();
}
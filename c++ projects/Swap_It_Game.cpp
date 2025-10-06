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

void YouWin();
void DrawBoard();
void DrawBalls();
void DrawHandles();
void Swap(int &x, int &y);
int WinCondition();

int balls[7][2] = {
	{200, 1},
	{300, 1},
	{400, 1},
	{500, 0},
	{600, 2},
	{700, 2},
	{800, 2}
};
int bi = 0, bSize = 25;
int handleX = 200;
int handleY = 400;

char option, txtMoves[5];
int moves = 0;

void Reset() {
	balls[0][1] = 1;
	balls[1][1] = 1;
	balls[2][1] = 1;
	balls[3][1] = 0;
	balls[4][1] = 2;
	balls[5][1] = 2;
	balls[6][1] = 2;
	moves = 0;
}      

int main() {
	srand((unsigned) time(0));
	int gd = DETECT, gm, err, tmp;
	initgraph(&gd, &gm, "");
	
	setbkcolor(LIGHTGRAY);
	setlinestyle(1, 0, 3);
	while(1) {
		DrawBoard();
		DrawBalls();
		DrawHandles();
		
		if(kbhit()) {
			option = getch();
			if(option == 'r') {
				Reset();
			}
			if(option == KEY_RIGHT) {
				if(handleX < 800) {
					handleX += 100;
					bi++;
				}
			} else if(option == KEY_LEFT) {
				if(handleX > 200) {
					handleX -= 100;
					bi--;
				}
			} else if(option == SPACEBAR) {
				if(balls[bi][1] != 0) {
					moves++;
					
					if(balls[bi][1] == 1 && bi < 6) {
						if(balls[bi + 1][1] == 0) {
							Swap(balls[bi][1], balls[bi + 1][1]);
						}
						if(balls[bi + 2][1] == 0) {
							Swap(balls[bi][1], balls[bi + 2][1]);
						}
					} else if(balls[bi][1] == 2 && bi > 0) {
						if(balls[bi - 1][1] == 0) {
							Swap(balls[bi][1], balls[bi - 1][1]);
						}
						if(balls[bi - 2][1] == 0) {
							Swap(balls[bi][1], balls[bi - 2][1]);
						}
					} 
				}
			}
		}
		if(WinCondition() == 1) {
			YouWin();
			Reset();
		}
		delay(40);
		cleardevice();
	}
	getch();
	closegraph();
}

void YouWin() {
	cleardevice();
	
	setcolor(WHITE);
	settextstyle(4, 0, 9);
	outtextxy(300, 300, "You Win");
	
	settextstyle(4, 0, 2);
	outtextxy(500, 420, "Press any key to restart...");
	getch();
	moves = 0;
}

void DrawBoard() {
	setcolor(BLACK);
	
	rectangle(0, 0, ScWidth - OpWidth, ScHeight);
	rectangle(ScWidth - OpWidth, 0, ScWidth, ScHeight);
	
	settextstyle(4, 0, 5);
	outtextxy(ScWidth - 330, 50, "Swap It");
	
	settextstyle(4, 0, 9);
	if(moves < 10) {
		outtextxy(ScWidth - 270, 250, itoa(moves, txtMoves, 10));
	} else if(moves >= 10) {
		outtextxy(ScWidth - 320, 250, itoa(moves, txtMoves, 10));
	}
	
	settextstyle(4, 0, 1);
	outtextxy(ScWidth - 375, 500, "Controls: ");
	outtextxy(ScWidth - 375, 540, "- Arrow Keys to navigate");
	outtextxy(ScWidth - 375, 570, "- Spacebar to swap");
	outtextxy(ScWidth - 375, 600, "- R to Reset");
}

void DrawBalls() {
	for(int i = 0; i < 7; i++) {
		setcolor(RED);
		circle(balls[i][0], 300, bSize);
		
		if(balls[i][1] == 0) {
			setfillstyle(1, LIGHTGRAY);
		} 
		if(balls[i][1] == 1) {
			setfillstyle(1, BLACK);
		}
		if(balls[i][1] == 2) {
			setfillstyle(1, WHITE);
		}
		
		fillellipse(balls[i][0], 300, bSize, bSize);
	}
}

void DrawHandles() {
	setcolor(BLUE);
	circle(handleX, handleY, 10);
}

void Swap(int &x, int &y) {
	int tmpType = x;
	x = y;
	y = tmpType;
}

int WinCondition() {
	if(balls[0][1] == 2 && balls[1][1] == 2 && balls[2][1] == 2 && balls[3][1] == 0 && balls[4][1] == 1 && balls[5][1] == 1 && balls[6][1] == 1) {
		return 1;
	}
	return 0;
}
#include<iostream>
#include<conio.h>
#include<windows.h>

using namespace std;

const int HEIGHT = 20;
const int WIDTH = 40;
char screen[HEIGHT][WIDTH];

int ballX = HEIGHT / 2;
int ballY = WIDTH / 2;
int ballDirX = -1;
int ballDirY = 1;

int paddleWidth = 7;
int paddleX = WIDTH / 2 - paddleWidth / 2;
const int paddleY = HEIGHT - 2;

int score = 0;

void showInstructions() {
	cout << "================= TEXT BOUNCING BALL GAME ==================";
	cout << "Symbols:\n";
	cout << " # : Wall\n";
	cout << " * : Ball\n";
	cout << " = : Paddle\n\n";
	cout << "Controls:\n";
	cout << " a : Move paddle left\n";
	cout << " d : Move paddle right\n";
	cout << "Keep the ball bouncing! Game ends if you miss the ball.\n";
	cout << "==========================================================\n";
	cout << "Press Enter to start...";
	cin.ignore();
}

void clearScreen() {
	for(int i = 0; i < HEIGHT; i++) {
		for(int j = 0; j < WIDTH; j++) {
			screen[i][j] = ' ';
		}
	}
}

void drawWalls() {
	for(int i = 0; i < HEIGHT; i++) {
		screen[i][0] = '#';
		screen[i][WIDTH - 1] = '#';
	}
	for(int j = 0; j < WIDTH; j++) {
		screen[0][j] = '#';
	}
}

void drawPaddle() {
	for(int j = 0; j < WIDTH; j++) {
		if(j >= paddleX && j < paddleX + paddleWidth) {
			screen[paddleY][j] = '=';
		}
	}
}

void drawBall() {
	screen[ballX][ballY] = '*';
}

void updateBall() {
	screen[ballX][ballY] = ' ';
	
	int nextX = ballX + ballDirX;
	int nextY = ballY + ballDirY;
	
	if(nextX <= 0) {
		ballDirX *= -1;
	}
	
	if(nextY <= 0 || nextY >= WIDTH - 1) {
		ballDirY *= -1;
	}
	
	if(nextX == paddleY && nextY >= paddleX && nextY < paddleX + paddleWidth) {
		ballDirX = -1;
		score++;
	}
	
	if(nextX >= HEIGHT - 1) {
		system("cls");
		cout << "\n You missed the ball! game over.\n";
		cout << "Final Score: " << score << "\n";
		cout << "Press any key to exit...";
		_getch();
		exit(0);
	}
	
	ballX += ballDirX;
	ballY += ballDirY;
}

void drawScreen() {
	system("cls");
	
	clearScreen();
	drawWalls();
	drawPaddle();
	drawBall();
	
	for(int i = 0; i < HEIGHT; i++) {
		for(int j = 0; j < WIDTH; j++) {
			cout << screen[i][j];
		}
		cout << "\n";
	}
	cout << "Score: " << score << "\n";
}

void updatePaddle(char key) {
	if(key == 'a' && paddleX > 1) {
		paddleX--;
	} else if(key == 'd' && paddleX + paddleWidth < WIDTH - 1) {
		paddleX++;
	}
}

void hideCursor() {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 10;
	info.bVisible = false;
	SetConsoleCursorInfo(h, &info);
}

int main() {
	showInstructions();
	hideCursor();
	
	while(true) {
		if(_kbhit()) {
			char ch = _getch();
			updatePaddle(ch);
		}
		
		updateBall();
		drawScreen();
		Sleep(80);
	}
	return 0;
}
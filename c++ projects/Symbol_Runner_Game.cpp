#include<iostream>
#include<cstdlib>
#include<ctime>
#include<conio.h>
#include<windows.h>

using namespace std;

const int HEIGHT = 5;
const int WIDTH = 30;
char screen[HEIGHT][WIDTH];
int playerX = HEIGHT - 2;
int playerY = 2;
bool isJumping = false;
int jumpCounter = 0;
int score = 0;
char obstacles[] = {'#', '$', '%', '&', '*', '|'};

void showInstructions() {
	cout << "=============== SYMBOL RUNNER =================\n";
	cout << "Symbols:\n";
	cout << " @ : You (the runner)\n";
	cout << " _ : Ground\n";
	cout << " # $ % & * | : Obstacles\n\n";
	cout << "Controls:\n";
	cout << " Press SPACE (Enter) to jump\n";
	cout << "Avoid the obstacles and keep running!\n";
	cout << "================================================\n";
	cout << "Press Enter to start the game...";
	cin.ignore();
}

void clearScreen() {
	for(int i = 0; i < HEIGHT; i++) {
		for(int j = 0; j < WIDTH; j++) {
			screen[i][j] = ' ';
		}
	}
}

void scrollScreen() {
	for(int i = 0; i < HEIGHT; i++) {
		for(int j = 1; j < WIDTH; j++) {
			screen[i][j - 1] = screen[i][j];
		}
	}
	
	for(int i = 0; i < HEIGHT; i++) {
		screen[i][WIDTH - 1] = ' ';
	}
	screen[HEIGHT - 1][WIDTH - 1] = '_';
	
	if(rand() % 5 == 0) {
		char symbol = obstacles[rand() % 6];
		screen[HEIGHT - 2][WIDTH - 1] = symbol;
	}
}

void updatePlayer() {
	if(isJumping) {
		if(jumpCounter < 3) {
			playerX = HEIGHT - 3;
		} else {
			playerX = HEIGHT - 2;
			isJumping = false;
			jumpCounter = 0;
		}
		jumpCounter++;
	}
}

void draw() {
	system("cls");
	for(int i = 0; i < HEIGHT; i++) {
		for(int j = 0; j < WIDTH; j++) {
			if(i == playerX && j == playerY) {
				cout << "@";
			} else {
				cout << screen[i][j];
			}
		}
		cout << "\n";
	}
	cout << "Score: " << score << "\n";
}

bool checkCollision() {
	char ahead = screen[playerX][playerY];
	return (ahead != ' ' && ahead != '_');
}

int main() {
	srand(time(0));
	showInstructions();
	
	clearScreen();
	
	bool gameOver = false;
	
	while(!gameOver) {
		if(_kbhit()) {
			char ch = _getch();
			if(ch == ' ' && !isJumping) {
				isJumping = true;
				jumpCounter = 0;
			}
		}
		
		updatePlayer();
		scrollScreen();
		draw();
		
		if(checkCollision()) {
			cout << "\n you hit an obstacle! game over.\n";
			break;
		}
		
		score++;
		Sleep(150);
	}
	
	cout << "Final Score: " << score << "\n";
	cout << "Press any key to exit...";
	_getch();
	return 0;
}
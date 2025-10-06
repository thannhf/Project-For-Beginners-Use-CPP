#include<iostream>
#include<conio.h>
#include<windows.h>
#include<ctime>

using namespace std;

const int HEIGHT = 20;
const int WIDTH = 40;

char screen[HEIGHT][WIDTH];

int playerX = WIDTH / 2;
int score = 0;

const int MAX_BULLETS = 5;
int bulletX[MAX_BULLETS];
int bulletY[MAX_BULLETS];
bool bulletActive[MAX_BULLETS];

const char enemyTypes[] = {'#', '$', '%', '&', '*'};
const int MAX_ENEMIES = 10;
int enemyX[MAX_ENEMIES];
int enemyY[MAX_ENEMIES];
char enemySymbol[MAX_ENEMIES];

void showInstructions() {
	cout << "============== SYMBOL DEFENDER GAME ============";
	cout << "Symbols:\n";
	cout << " ^ : You (Defender)\n";
	cout << " | : Bullet\n";
	cout << " # $ % & * : Falling enemies\n\n";
	cout << "Controls:\n";
	cout << " a : Move left\n";
	cout << " d : Move right\n";
	cout << " space : Fire bullet (multiple allowed)\n";
	cout << "Prevent enemies from hitting the ground!\n";
	cout << "==================================================";
	cout << "Press Enter to start...";
	cin.ignore();
}

void initGame() {
	for(int i = 0; i < MAX_ENEMIES; i++) {
		enemyX[i] = rand() % WIDTH;
		enemyY[i] = rand() % 5;
		enemySymbol[i] = enemyTypes[rand() % 5];
	}
	
	for(int i = 0; i < MAX_BULLETS; i++) {
		bulletActive[i] = false;
	}
}

void clearScreenBuffer() {
	for(int i = 0; i < HEIGHT; i++) {
		for(int j = 0; j < WIDTH; j++) {
			screen[i][j] = ' ';
		}
	}
}

void draw() {
	clearScreenBuffer();
	
	screen[HEIGHT - 1][playerX] = '^';
	
	for(int i = 0; i < MAX_BULLETS; i++) {
		if(bulletActive[i] && bulletY[i] >= 0) {
			screen[bulletY[i]][bulletX[i]] = '|';
		}
	}
	
	for(int i = 0; i < MAX_ENEMIES; i++) {
		if(enemyY[i] >= 0 && enemyY[i] < HEIGHT) {
			screen[enemyY[i]][enemyX[i]] = enemySymbol[i];
		}
	}
	
	system("cls");
	for(int i = 0; i < HEIGHT; i++) {
		for(int j = 0; j < WIDTH; j++) {
			cout << screen[i][j];
		}
		cout << "\n";
	}
	cout << "Score: " << score << "\n";
}

void updateBullets() {
	for(int i = 0; i < MAX_BULLETS; i++) {
		if(bulletActive[i]) {
			bulletY[i]--;
			if(bulletY[i] < 0) {
				bulletActive[i] = false;
			}
		}
	}
}

void updateEnemies(bool& gameOver) {
	for(int i = 0; i < MAX_ENEMIES; i++) {
		enemyY[i]++;
		if(enemyY[i] >= HEIGHT - 1) {
			gameOver = true;
		}
	}
}

void checkCollisions() {
	for(int b = 0; b < MAX_BULLETS; b++) {
		if(!bulletActive[b]) continue;
		
		for(int e = 0; e < MAX_ENEMIES; e++) {
			if(bulletY[b] == enemyY[e] && bulletX[b] == enemyX[e]) {
				bulletActive[b] = false;
				score++;
				
				enemyY[e] = 0;
				enemyX[e] = rand() % WIDTH;
				enemySymbol[e] = enemyTypes[rand() % 5];
			}
		}
	}
}

void fireBullet() {
	for(int i = 0; i < MAX_BULLETS; i++) {
		if(!bulletActive[i]) {
			bulletX[i] = playerX;
			bulletY[i] = HEIGHT - 2;
			bulletActive[i] = true;
			break;
		}
	}
}

void processInput() {
	if(_kbhit()) {
		char ch = _getch();
		if(ch == 'a' && playerX > 0) playerX--;
		else if(ch == 'd' && playerX < WIDTH - 1) playerX++;
		else if(ch == ' ') fireBullet();
	}
}

int main() {
	srand(time(0));
	showInstructions();
	initGame();
	
	bool gameOver = false;
	
	while(!gameOver) {
		processInput();
		updateBullets();
		updateEnemies(gameOver);
		checkCollisions();
		draw();
		Sleep(100);
	}
	
	cout << "\n Enemy reached the ground! Game Over.\n";
	cout << "Final Score: " << score << "\n";
	cout << "press any key to exit...";
	_getch();
	return 0;
}
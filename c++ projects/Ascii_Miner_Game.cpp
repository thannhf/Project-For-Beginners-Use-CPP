#include<iostream>
#include<conio.h>
#include<windows.h>
#include<ctime>
using namespace std;

const int WIDTH = 20;
const int HEIGHT = 20;
char world[HEIGHT][WIDTH + 1];
int playerX = WIDTH / 2;
int playerY = 0;
int treasures = 0;
bool gameOver = false;

void hideCursor() {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 10;
	info.bVisible = false;
	SetConsoleCursorInfo(h, &info);
}

void moveCursorTop() {
	COORD pos = {0, 0};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void generateWorld() {
	srand(time(0));
	for(int y = 0; y < HEIGHT; ++y) {
		for(int x = 0; x < WIDTH; ++x) {
			int r = rand() % 100;
			if(y == 0 && x == playerX) world[y][x] = '@';
			else if(r < 70) world[y][x] = '#';
			else if(r < 85) world[y][x] = '*';
			else world[y][x] = 'O';
		}
		world[y][WIDTH] = '\0';
	}
}

void drawWorld() {
	moveCursorTop();
	for(int y = 0; y < HEIGHT; ++y) {
		cout << world[y] << "\n";
	}
	cout << "\nTreasures Collected: " << treasures << "\n";
}

void applyGravity() {
	for(int y = HEIGHT - 2; y >= 0; --y) {
		for(int x = 0; x < WIDTH; ++x) {
			char& current = world[y][x];
			char& below = world[y + 1][x];
			
			if((current == 'O' || current == '*') && below == ' ') {
				below = current;
				current = ' ';
				
				if(playerY == y + 1 && playerX == x && below == 'O') {
					gameOver = true;
				}
			}
		}
	}
}

void movePlayer(int dx, int dy) {
	int newX = playerX + dx;
	int newY = playerY + dy;
	
	if(newX < 0 || newX >= WIDTH || newY < 0 || newY >= HEIGHT) {
		return;
	}
	
	char target = world[newY][newX];
	if(target == 'O') return;
	if(target == '*') treasures++;
	world[playerY][playerX] = ' ';
	playerX = newX;
	playerY = newY;
	world[playerY][playerX] = '@'; 
}

void gameLoop() {
	while(!gameOver) {
		drawWorld();
		
		if(_kbhit()) {
			int ch = _getch();
			if(ch == 0 || ch == 224) {
				ch = _getch();
				switch(ch) {
					case 75: movePlayer(-1, 0); break;
					case 77: movePlayer(1, 0); break;
					case 80: movePlayer(0, 1); break;
				}
			}
		}
		applyGravity();
		
		if(world[playerY][playerX] == 'O') {
			gameOver = true;
		}
		Sleep(100);
	}
	drawWorld();
	cout << "\n Game Over Final Score: " << treasures << "\n";
}

void showInstructions() {
	system("cls");
	cout << "================ ASCII MINER ===============\n";
	cout << "you are a miner '@' digging through the earth.\n\n";
	cout << "your objective: collect as many treasures '*' as you can\n";
	cout << "while avoiding falling rocks 'O'. break dirt blocks '#' to dig.\n\n";
	
	cout << "Controls:\n";
	cout << " -> Arrow right : Move right\n";
	cout << " <- Arrow left : Move left\n";
	cout << " Arrow down : Dig Down\n\n";
	
	cout << "Beware: Rocks 'O' will fall due to gravity if unsupported.\n";
	cout << "Getting hit by a falling rock will end the game.\n\n";
	
	cout << "Press any key to start...\n";
	_getch();
	system("cls");
}

int main() {
	hideCursor();
	showInstructions();
	generateWorld();
	gameLoop();
	return 0;
}
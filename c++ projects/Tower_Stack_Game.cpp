#include<iostream>
#include<conio.h>
#include<windows.h>
using namespace std;

const int screenWidth = 40;
const int maxHeight = 20;

struct Block {
	int startX;
	int width;
};

Block tower[maxHeight];
int currentLevel = 0;
int direction = 1;
int movingX = 0;
bool gameOver = false;

void hideCursor() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	GetConsoleCursorInfo(hConsole, &info);
	info.bVisible = false;
	SetConsoleCursorInfo(hConsole, &info);
}

void moveCursorTop() {
	COORD pos = {0, 0};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void draw() {
	moveCursorTop();
	for(int i = 0; i < maxHeight; ++i) {
		for(int j = 0; j < screenWidth; ++j) {
			if(i < currentLevel) {
				if(j >= tower[i].startX && j < tower[i].startX + tower[i].width) {
					cout << "*";
				} else {
					cout << " ";
				}
			} else if(i == currentLevel) {
				if(j >= movingX && j < movingX + tower[i].width) {
					cout << "*";
				} else {
					cout << " ";
				}
			} else {
				cout << " ";
			}
		}
		cout << "\n";
	}
	cout << "\nStack Height: " << currentLevel << "\n";
}

void placeBlock() {
	if(currentLevel == 0) {
		tower[currentLevel].startX = movingX;
		currentLevel++;
		return;
	}
	
	int prevStart = tower[currentLevel - 1].startX;
	int prevWidth = tower[currentLevel - 1].width;
	
	int newStart = movingX;
	int newEnd = movingX + tower[currentLevel].width;
	
	int overlapStart = max(prevStart, newStart);
	int overlapEnd = min(prevStart + prevWidth, newEnd);
	
	int overlapWidth = overlapEnd - overlapStart;
	
	if(overlapWidth <= 0) {
		gameOver = true;
		return;
	}
	
	tower[currentLevel].startX = overlapStart;
	tower[currentLevel].width = overlapWidth;
	currentLevel++;
	if(currentLevel >= maxHeight) gameOver = true;
}

void gameLoop() {
	tower[0].width = 10;
	tower[0].startX = screenWidth / 2 - 5;
	
	tower[1].width = 10;
	movingX = 0;
	direction = 1;
	
	while(!gameOver) {
		if(_kbhit()) {
			char key = _getch();
			if(key == ' ' || key == 13) {
				placeBlock();
				tower[currentLevel].width = tower[currentLevel - 1].width;
				movingX = 0;
				direction = 1;
			}
		}
		
		movingX += direction;
		if(movingX + tower[currentLevel].width >= screenWidth || movingX <= 0) {
			direction *= -1;
		}
		draw();
		Sleep(50);
	}
	draw();
	cout << "\n game over final height: " << currentLevel << "\n";
}

int main() {
	hideCursor();
	cout << "Press any key to start" << endl;
	getch();
	gameLoop(); 
	return 0;
}
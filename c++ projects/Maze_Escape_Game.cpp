#include<iostream>
#include<conio.h>
#include<windows.h>

using namespace std;

const int WIDTH = 20;
const int HEIGHT = 10;

char maze[HEIGHT][WIDTH + 1] = {
	"********************",
	
	"*P		*			*",
	
	"* *** ***** *****  *",
	
	"*   *     *     *  *",
	
	"*** *** ***** * *  *",
	
	"*     *     * * *  *",
	
	"* ***** *** * * *  *",
	
	"*     *   *   *    E",
	
	"* *** * ********** *",
	
	"********************"
};

int playerX = 1, playerY = 1;

void moveCursorToTop() {
	COORD pos = {0, 0};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void hideCursor() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	GetConsoleCursorInfo(hConsole, &info);
	info.bVisible = false;
	SetConsoleCursorInfo(hConsole, &info);
}

void drawMaze() {
	moveCursorToTop();
	for(int i = 0; i < HEIGHT; ++i) {
		cout << maze[i] << "\n";
	}
}

void movePlayer(int dx, int dy) {
	int newX = playerX + dx;
	int newY = playerY + dy;
	
	if(maze[newY][newX] == ' ' || maze[newY][newX] == 'E') {
		maze[playerY][playerX] = ' ';
		playerX = newX;
		playerY = newY;
		maze[playerY][playerX] = 'P';
	}
}

int main() {
	hideCursor();
	drawMaze();
	
	while(true) {
		if(_kbhit()) {
			int ch = _getch();
			if(ch == 0 || ch == 224) {
				ch = _getch();
				switch(ch) {
					case 72: movePlayer(0, -1); break;
					case 80: movePlayer(0, 1); break;
					case 75: movePlayer(-1, 0); break;
					case 77: movePlayer(1, 0); break;
				}
				drawMaze();
			}
		}
		
		if(maze[playerY][playerX] == 'E') {
			drawMaze();
			cout << "\n You escaped the maze!\n";
			break;
		}
		Sleep(50);
	}
	return 0;
}
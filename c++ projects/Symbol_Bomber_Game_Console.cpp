#include<iostream>
#include<conio.h>
#include<windows.h>
#include<ctime>

using namespace std;

const int HEIGHT = 20;
const int WIDTH = 50;

char screen[HEIGHT][WIDTH];

const int MAX_BOMBS = 40;
int bombX[MAX_BOMBS];
int bombY[MAX_BOMBS];
bool bombActive[MAX_BOMBS];

int planeX = 0;
int score = 0;

const int TARGET_ROW = HEIGHT - 2;
const int NUM_TARGETS = 10;
int targetPositions[NUM_TARGETS];

void hideCursor() {
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(console, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(console, &cursorInfo);
}

void showInstructions() {
	cout << "============= SYMBOL BOMBER GAME ===============\n";
	cout << "Symbols:\n";
	cout << "	>===< : Plane\n";
	cout << "	  |	  : Bomb\n";
	cout << "	  #   : Target\n\n";
	cout << "Controls:\n";
	cout << "	SPACE : Drop bomb\n";
	cout << "	Q	  : Quit Game\n";
	cout << "Hit targets (#) to score points!\n";
	cout << "===================================\n";
	cout << "Press Enter to start...";
	cin.ignore();
}

void initTargets() {
	int spacing = WIDTH / NUM_TARGETS;
	for(int i = 0; i < NUM_TARGETS; i++) {
		targetPositions[i] = spacing * i + spacing / 2;
	}
}

void clearScreenBuffer() {
	for(int i = 0; i < HEIGHT; i++) {
		for(int j = 0; j < WIDTH; j++) {
			screen[i][j] = ' ';
		}
	}
}

void drawPlane() {
	string plane = ">===<";
	for(int i = 0; i < plane.length(); i++) {
		int pos = planeX + i;
		if(pos >= 0 && pos < WIDTH) {
			screen[0][pos] = plane[i];
		}
	}
}

void drawTargets() {
	for(int i = 0; i < NUM_TARGETS; i++) {
		screen[TARGET_ROW][targetPositions[i]] = '#';
	}
}

void dropBomb() {
	for(int i = 0; i < MAX_BOMBS; i++) {
		if(!bombActive[i]) {
			bombActive[i] = true;
			bombX[i] = 1;
			bombY[i] = planeX + 2;
			break;
		}
	}
}

void updateBombs() {
	for(int i = 0; i < MAX_BOMBS; i++) {
		if(bombActive[i]) {
			bombX[i]++;
			if(bombX[i] >= HEIGHT) {
				bombActive[i] = false;
			} else if(bombX[i] == TARGET_ROW) {
				for(int j = 0; j < NUM_TARGETS; j++) {
					if(bombY[i] == targetPositions[j]) {
						score++;
						bombActive[i] = false;
						break;
					}
				}
			}
		}
	}
}

void drawBombs() {
	for(int i = 0; i < MAX_BOMBS; i++) {
		if(bombActive[i] && bombX[i] < HEIGHT) {
			screen[bombX[i]][bombY[i]] = '|';
		}
	}
}

void drawScreen() {
	system("cls");
	clearScreenBuffer();
	drawPlane();
	drawTargets();
	drawBombs();
	
	for(int i = 0; i < HEIGHT; i++) {
		for(int j = 0; j < WIDTH; j++) {
			cout << screen[i][j];
		}
		cout << "\n";
	}
	cout << "Score: " << score << "\n";
	cout << "Press Q to quit.\n";
}

void movePlane() {
	planeX++;
	if(planeX > WIDTH - 5) {
		planeX = 0;
	}
}

int main() {
	srand(time(0));
	showInstructions();
	hideCursor();
	initTargets();
	
	while(true) {
		if(_kbhit()) {
			char ch = _getch();
			if(ch == ' ') {
				dropBomb();
			} else if(ch == 'q' || ch == 'Q') {
				break;
			}
		}
		
		updateBombs();
		drawScreen();
		movePlane();
		Sleep(20);
	}
	
	cout << "\nFinal Score: " << score << "\n";
	cout << "thank for playing!\n";
	return 0;
}
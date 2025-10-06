#include<iostream>
#include<conio.h>
#include<windows.h>
#include<ctime>

using namespace std;

const int HEIGHT = 20;
const int WIDTH = 21;
char screen[HEIGHT][WIDTH];

int playerRow = HEIGHT - 2;
int playerCol = WIDTH / 2;
int score = 0;

char obstacles[] = {'#', '%'};

void hideCursor() {
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(out, &cursorInfo);
}

void showInstructions() {
	cout << "============= SYMBOL LADDER CLIMB ================";
	cout << "Symbols:\n";
	cout << " @ : You (the climber)\n";
	cout << " | : Ladder\n";
	cout << " #, % : Falling obstacles\n\n";
	cout << "Controls:\n";
	cout << " a : Move left\n";
	cout << " d : Move right\n";
	cout << "Avoid obstactes and stay on the ladder!\n";
	cout << "Score only increases when you're on the ladder!\n";
	cout << "==============================================\n";
	cout << "Press Enter to start...";
	cin.ignore();
}

void initializeScreen() {
	for(int i = 0; i < HEIGHT; i++) {
		for(int j = 0; j < WIDTH; j++) {
			screen[i][j] = ' ';
		}
	}
}

void generateNewTopRow(char row[WIDTH]) {
	for(int j = 0; j < WIDTH; j++) {
		row[j] = ' ';
	}
	
	int center = WIDTH / 2;
	row[center] = '|';
	
	if(rand() % 4 == 0) {
		row[center] = obstacles[rand() % 2];
	}
}

void scrollDown() {
	for(int i = HEIGHT - 1; i > 0; i--) {
		for(int j = 0; j < WIDTH; j++) {
			screen[i][j] = screen[i - 1][j];
		}
	}
	
	char newRow[WIDTH];
	generateNewTopRow(newRow);
	for(int j = 0; j < WIDTH; j++) {
		screen[0][j] = newRow[j];
	}
}

void drawScreen() {
	system("cls");
	
	for(int i = 0; i < HEIGHT; i++) {
		for(int j = 0; j < WIDTH; j++) {
			if(i == playerRow && j == playerCol) {
				cout << '@';
			} else {
				cout << screen[i][j];
			}
		}
		cout << "\n";
	}
	cout << "Score: " << score << "\n";
}

bool isGameOver() {
	char underPlayer = screen[playerRow][playerCol];
	return (underPlayer == '#' || underPlayer == '%');
}

void processInput() {
	if(_kbhit()) {
		char ch = _getch();
		if(ch == 'a' && playerCol > 0) {
			playerCol--;
		} else if(ch == 'd' && playerCol < WIDTH - 1) {
			playerCol++;
		}
	}
}

int main() {
	srand(time(0));
	showInstructions();
	hideCursor();
	initializeScreen();
	
	while(true) {
		processInput();
		scrollDown();
		
		if(isGameOver()) {
			drawScreen();
			cout << "\n you were hit by an obstacle game over.\n";
			break;
		}
		
		if(screen[playerRow][playerCol] == '|') {
			score++;
		}
		
		drawScreen();
		Sleep(200);
	}
	
	cout << "Final Score:" << score << "\n";
	cout << "Press any key to exit...";
	_getch();
	return 0;
}
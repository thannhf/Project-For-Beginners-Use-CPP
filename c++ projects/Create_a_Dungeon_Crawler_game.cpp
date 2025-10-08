#include<iostream>
#include<conio.h>

using namespace std;

const int ROWS = 10;
const int COLS = 20;
char dungeon[ROWS][COLS];
int playerX = 1, playerY = 1;
int treasureCount = 0;
int collected = 0;

void showInstructions() {
	cout << "============= ROGUE-LIKE DUNGEON CRAWLER ===============\n";
	cout << "Symbols:\n";
	cout << " # : Wall\n";
	cout << " . : Floor\n";
	cout << " @ : You (player)\n";
	cout << " $ : Treasure\n";
	cout << " % : Enemy (touch = death)\n";
	cout << " & : Exit (only usable after collecting all $)\n\n";
	cout << "Controls:\n";
	cout << " w : Move up\n";
	cout << " s : Move down\n";
	cout << " a : Move left\n";
	cout << " d : Move right\n";
	cout << "Goal: collect all treasures ($) and reach the exit (&)\n";
	cout << "=========================================================\n";
	cout << "Press enter to start...";
	cin.ignore();
}

void drawDungeon() {
	system("cls");
	for(int i = 0; i < ROWS; i++) {
		for(int j = 0; j < COLS; j++) {
			if(i == playerX && j == playerY) {
				cout << "@";
			} else {
				cout << dungeon[i][j];
			}
		}
		cout << "\n";
	}
	cout << "Treasures Collected: " << collected << "/" << treasureCount << "\n";
}

void setupDungeon() {
	for(int i = 0; i < ROWS; i++) {
		for(int j = 0; j < COLS; j++) {
			dungeon[i][j] = '.';
		}
	}
	
	for(int i = 0; i < ROWS; i++) {
		dungeon[i][0] = '#';
		dungeon[i][COLS - 1] = '#';
	}
	for(int j = 0; j < COLS; j++) {
		dungeon[0][j] = '#';
		dungeon[ROWS - 1][j] = '#';
	}
	
	dungeon[3][5] = '#'; dungeon[3][6] = '#';
	dungeon[5][10] = '#'; dungeon[6][10] = '#';
	
	dungeon[2][2] = '$'; dungeon[4][7] = '$';
	dungeon[6][3] = '$'; dungeon[7][15] = '$';
	treasureCount = 4;
	
	dungeon[3][3] = '%'; dungeon[5][8] = '%';
	dungeon[8][18] = '&';
}

bool isWalkable(int x, int y) {
	return dungeon[x][y] != '#';
}

bool gameLoop() {
	char move = _getch();
	int nextX = playerX;
	int nextY = playerY;
	
	if(move == 'w') nextX--;
	else if(move == 's') nextX++;
	else if(move == 'a') nextY--;
	else if(move == 'd') nextY++;
	
	if(nextX < 0 || nextX >= ROWS || nextY < 0 || nextY >= COLS) {
		return false;
	}
	
	char target = dungeon[nextX][nextY];
	if(target == '#') return false;
	
	if(target == '$') {
		collected++;
		dungeon[nextX][nextY] = '.';
	} else if(target == '%') {
		drawDungeon();
		cout << "\n you were killed by an enemy! game over.\n";
		return true;
	} else if(target == '&') {
		if(collected == treasureCount) {
			drawDungeon();
			cout << "\n you escaped with all treasures! you win!\n";
			return true;
		} else {
			cout << "\n the exit is locked! collect all treasures first.!\n";
			_getch();
			return false;
		}
	}
	
	playerX = nextX;
	playerY = nextY;
	return false;
}

int main() {
	showInstructions();
	setupDungeon();
	
	bool gameOver = false;
	while(!gameOver) {
		drawDungeon();
		gameOver = gameLoop();
	}
	
	cout << "Press any key to exit...\n";
	_getch();
	return 0;
}
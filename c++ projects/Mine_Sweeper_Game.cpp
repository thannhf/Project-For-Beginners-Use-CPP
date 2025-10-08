#include<iostream>
#include<cstdlib>
#include<ctime>
#include<iomanip>
using namespace std;

const int ROWS = 9;
const int COLS = 9;
const int MINES = 10;

char display[ROWS][COLS];
bool isMine[ROWS][COLS];
bool isOpen[ROWS][COLS];
bool isFlagged[ROWS][COLS];
int nearbyMines[ROWS][COLS];

int dx[] = {-1,-1,-1,0,1,1,1,0};
int dy[] = {-1,0,1,1,1,0,-1,-1};

void showInstructions() {
	cout << "=============== TEXT MODE MINESWEEPER =============\n";
	cout << "Symbols:\n";
	cout << " # : Unopened cell\n";
	cout << " & : Flagged cell\n";
	cout << " * : Mine (when revealed)\n";
	cout << " 1-8 : Opened cell showing nearby mine count\n";
	cout << " space : Opened cell with no nearby mines\n\n";
	cout << "Commands:\n";
	cout << " o x y -> Open cell at (x, y)\n";
	cout << "===================================================\n";
	cout << "press enter to start the game...";
	cin.ignore();
}

void initializeBoard() {
	for(int i = 0; i < ROWS; i++) {
		for(int j = 0; j < COLS; j++) {
			isMine[i][j] = false;
			isOpen[i][j] = false;
			isFlagged[i][j] = false;
			nearbyMines[i][j] = 0;
			display[i][j] = '#';
		}
	}
}

void placeMines() {
	int placed = 0;
	while(placed < MINES) {
		int x = rand() % ROWS;
		int y = rand() % COLS;
		if(!isMine[x][y]) {
			isMine[x][y] = true;
			placed++;
		}
	}
}

void countNearbyMines() {
	for(int i = 0; i < ROWS; i++) {
		for(int j = 0; j < COLS; j++) {
			if(isMine[i][j]) continue;
			int count = 0;
			for(int d = 0; d < 8; d++) {
				int ni = i + dx[d], nj = j + dy[d];
				if(ni >= 0 && ni < ROWS && nj >= 0 && nj < COLS && isMine[ni][nj]) {
					count++;
				}
			}
			nearbyMines[i][j] = count;
		}
	}
}

void reveal(int x, int y) {
	if(x < 0 || y < 0 || x >= ROWS || y >= COLS) return;
	if(isOpen[x][y] || isFlagged[x][y]) return;
	isOpen[x][y] = true;
	
	if(isMine[x][y]) return;
	
	if(nearbyMines[x][y] > 0) {
		display[x][y] = '0' + nearbyMines[x][y];
	} else {
		display[x][y] = ' ';
		for(int d = 0; d < 8; d++) {
			reveal(x + dx[d], y + dy[d]);
		}
	}
}

bool checkWin() {
	for(int i = 0; i < ROWS; i++) {
		for(int j = 0; j < COLS; j++) {
			if(!isMine[i][j] && !isOpen[i][j]) {
				return false;
			}
		}
	}
	return true;
}

void printBoard(bool revealMines = false) {
	cout << "\n ";
	for(int j = 0; j < COLS; j++) cout << setw(2) << j << " ";
	cout << "\n";
	
	for(int i = 0; i < ROWS; i++) {
		cout << setw(2) << i << " ";
		for(int j = 0; j < COLS; j++) {
			if(revealMines && isMine[i][j]) {
				cout << " * ";
			} else if(isFlagged[i][j]) {
				cout << " & ";
			} else {
				cout << " " << display[i][j] << " ";
			}
		}
		cout << "\n";
	}
}

int main() {
	srand(time(0));
	
	showInstructions();
	initializeBoard();
	placeMines();
	countNearbyMines();
	
	bool gameOver = false;
	
	while(!gameOver) {
		printBoard();
		cout << "\nEnter command (o x y = open, f x y = flag): ";
		char cmd;
		int x, y;
		cin >> cmd >> x >> y;
		
		if(x < 0 || x >= ROWS || y < 0 || y >= COLS) {
			cout << "Invalid coordinates!\n";
			continue;
		}
		
		if(cmd == 'f') {
			isFlagged[x][y] = !isFlagged[x][y];
			display[x][y] = isFlagged[x][y] ? '&' : '#';
		} else if(cmd == 'o') {
			if(isFlagged[x][y] || isOpen[x][y]) continue;
			
			if(isMine[x][y]) {
				cout << "\n Boom! you hit a mine. Game Over!.\n";
				printBoard(true);
				gameOver = true;
			} else {
				reveal(x, y);
				if(checkWin()) {
					cout << "\n congratulations! you cleared all safe cells!\n";
					printBoard(true);
					gameOver = true;
				}
			}
		} else {
			cout << "Invalid command! use 'o' or 'f'.\n";
		}
	}
	return 0;
}
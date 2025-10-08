#include<iostream>
#include<ctime>
#include<cstdlib>
#include<conio.h>
#include<windows.h>
using namespace std;

const int WIDTH = 10;
const int HEIGHT = 20;

int grid[HEIGHT][WIDTH] = {0};

const int tetrominoes[7][4][4] = {
	{
		{0,0,0,0},
		{1,1,1,1},
		{0,0,0,0},
		{0,0,0,0}
	},
	{
		{0,0,0,0},
		{0,1,1,0},
		{0,1,1,0},
		{0,0,0,0}
	},
	{
		{0,0,0,0},
		{1,1,1,0},
		{0,1,0,0},	
		{0,0,0,0}
	},
	{
		{0,0,0,0},
		{0,1,1,0},
		{1,1,0,0},
		{0,0,0,0}
	},
	{
		{0,0,0,0},
		{1,1,0,0},
		{0,1,1,0},
		{0,0,0,0}
	},
	{
		{0,0,0,0},
		{1,1,1,0},
		{0,0,1,0},
		{0,0,0,0}
	},
	{
		{0,0,0,0},
		{1,1,1,0},
		{1,0,0,0},
		{0,0,0,0}
	}
};

int block[4][4] = {0};
int bx = WIDTH / 2 - 2;
int by = 0;

void setShape(const int shape[4][4]) {
	for(int i = 0; i < 4; ++i) {
		for(int j = 0; j < 4; ++j) {
			block[i][j] = shape[i][j];
		}
	}
}

void rotateBlock() {
	int temp[4][4] = {0};
	for(int i = 0; i < 4; ++i) {
		for(int j = 0; j < 4; ++j) {
			temp[j][3 - i] = block[i][j];
		}
	}
	
	for(int i = 0; i < 4; ++i) {
		for(int j = 0; j < 4; ++j) {
			if(temp[i][j]) {
				int x = bx + j;
				int y = by + i;
				if(x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT || grid[y][x]) {
					return;
				}
			}
		}
	}
	
	for(int i = 0; i < 4; ++i) {
		for(int j = 0; j < 4; ++j) {
			block[i][j] = temp[i][j];
		}
	}
}

void draw() {
	system("cls");
	for(int i = 0; i < HEIGHT; ++i) {
		cout << "|";
		for(int j = 0; j < WIDTH; ++j) {
			char ch = '.';
			if(grid[i][j]) ch = '#';
			for(int bi = 0; bi < 4; ++bi) {
				for(int bj = 0; bj < 4; ++bj) {
					int x = bx + bj;
					int y = by + bi;
					if(x == j && y == i && block[bi][bj]) {
						ch = '#';
					}
				}
			}
			cout << ch;
		}
		cout << "|\n";
	}
	
	for(int i = 0; i < WIDTH + 2; ++i) cout << "=";
	cout << "\n";
}

bool canMove(int dx, int dy) {
	for(int i = 0; i < 4; ++i) {
		for(int j = 0; j < 4; ++j) {
			if(block[i][j]) {
				int x = bx + j + dx;
				int y = by + i + dy;
				if(x < 0 || x >= WIDTH || y >= HEIGHT || (y >= 0 && grid[y][x])) {
					return false;
				}
			}
		}
	}
	return true;
}

void placeBlock() {
	for(int i = 0; i < 4; ++i) {
		for(int j = 0; j < 4; ++j) {
			if(block[i][j]) {
				int x = bx + j;
				int y = by + i;
				if(y >= 0) {
					grid[y][x] = 1;
				}
			}
		}
	}
}

void clearLines() {
	for(int i = HEIGHT - 1; i >= 0; --i) {
		bool full = true;
		for(int j = 0; j < WIDTH; ++j) {
			if(!grid[i][j]) full = false;
		}
		
		if(full) {
			for(int k = i; k > 0; --k) {
				for(int j = 0; j < WIDTH; ++j) {
					grid[k][j] = grid[k - 1][j];
				}
			}
			for(int j = 0; j < WIDTH; ++j) {
				grid[0][j] = 0;
			}
			i++;
		}
	}
}

void newShape() {
	int shapeIndex = rand() % 7;
	setShape(tetrominoes[shapeIndex]);
	bx = WIDTH / 2 - 2;
	by = 0;
	if(!canMove(0, 0)) {
		draw();
		cout << "\nGAME OVER\n";
		exit(0);
	}
}

int main() {
	srand(time(0));
	newShape();
	
	while(true) {
		draw();
		
		if(_kbhit()) {
			char key = _getch();
			if(key == 'a' && canMove(-1, 0)) bx--;
			else if(key == 'd' && canMove(1, 0)) bx++;
			else if(key == 's' && canMove(0, 1)) by++;
			else if(key == ' ') rotateBlock();
		}
		
		if(canMove(0, 1)) {
			by++;
		} else {
			placeBlock();
			clearLines();
			newShape();
		}
		Sleep(200);
	}
	return 0;
}
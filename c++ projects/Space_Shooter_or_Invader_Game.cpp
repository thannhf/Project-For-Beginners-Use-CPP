#include<iostream>
#include<vector>
#include<conio.h>
#include<windows.h>
#include<ctime>

using namespace std;

const int width = 30;
const int height = 20;
bool gameOver = false;

int playerX = width / 2;
vector<pair<int, int>> bullets;
vector<pair<int, int>> invaders;

int score = 0;

void clearScreen() {
	CROOD cursorPosition;
	cursorPosition.X = 0;
	cursorPosition.Y = 0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}

void draw() {
	clearScreen();
	
	for(int y = 0; y < height; ++y) {
		for(int x = 0; x < width; ++x) {
			bool printed = false;
			
			if(y == height - 1 && x == playerX) {
				cout << "^";
				printed = true;
			}
			
			for(auto& b : bullets) {
				if(b.first == x && b.second == y) {
					cout << "|";
					printed = true;
					break;
				}
			}
			
			for(auto& i : invaders) {
				if(i.first == x && i.second == y) {
					cout << "W";
					printed = true;
					break;
				}
			}
			
			if(!printed) cout << " ";
		}
		cout << "\n";
	}
	cout << "\nScore: " << score << "\n";
}

void input() {
	if(_kbhit()) {
		char ch = _getch();
		
		if(ch == 'a' && playerX > 0) {
			playerX--;
		} else if(ch == 'd' && playerX < width - 1) {
			playerX++;
		} else if(ch == ' ') {
			bullets.push_back({playerX, height - 2});
		}
	}
}

void update() {
	for(int i = 0; i < bullets.size(); ++i) {
		bullets[i].second--;
		
		if(bullets[i].second < 0) {
			bullets.erase(bullets.begin() + i);
			i--;
		}
	}
	
	static int tick = 0;
	tick++;
	if(tick % 10 == 0) {
		for(auto& i : invaders) {
			if(rand() % 2 == 0) i.first += 1;
			else i.first -= 1;
			
			i.first = max(0, min(i.first, width - 1));
			i.second++;
			
			if(i.second == height - 1) gameOver = true;
		}
	}
	
	for(int i = 0; i < bullets.size(); ++i) {
		for(int j = 0; j < invaders.size(); ++j) {
			if(bullets[i].first == invaders[j].first && bullets[i].second == invaders[j].second) {
				score += 10;
				bullets.erase(bullets.begin() + i);
				invaders.erase(invaders.begin() + j);
				i--;
				break;
			}
		}
	}
	
	if(invaders.empty()) {
		gameOver = true;
	}
}

void setup() {
	srand(time(0));
	for(int i = 0; i < 10; ++i) {
		int x = rand() % width;
		int y = rand() % 3;
		invaders.push_back({x, y});
	}
}

void hideCursor() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	
	GetConsoleCursorInfo(hConsole, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(hConsole, &cursorInfo);
}

int main() {
	hideCursor();
	cout << "press any key to start." << endl;
	getch();
	setup();
	while(!gameOver) {
		draw();
		input();
		update();
		Sleep(100);
	}
	draw();
	cout << "\nGame Over!\n Final Score: " << score << "\n";
	return 0;
}
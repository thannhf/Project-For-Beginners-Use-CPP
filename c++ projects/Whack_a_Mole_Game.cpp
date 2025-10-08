#include<iostream>
#include<vector>
#include<cstdlib>
#include<ctime>
#include<conio.h>
#include<time.h>

using namespace std;

const int BOARD_SIZE = 3;
const int GAME_DURATION = 30;
const int MOLE_APPEAR_TIME = 1;
const int MOLE_HIT_POINTS = 10;
const int FRAME_DELAY = 200;

class WhackAMole {
	private:
		vector<vector<char>> board;
		int score;
		time_t startTime;
		bool gameOver;
		time_t lastMoleTime;
		time_t lastFrameTime;
		
		void clearBoard() {
			board = vector<vector<char>>(BOARD_SIZE, vector<char>(BOARD_SIZE, ' '));
		}
		
		void drawBoard() {
			system("cls");
			
			cout << "WHACK-A-MOLE! (Score: " << score << ")\n";
			cout << "Time left: " << GAME_DURATION - (time(0) - startTime) << "s\n\n";
			
			cout << "+---+---+---+\n";
			cout << " | " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << " |\n";
			cout << "+---+---+---+\n";
			cout << " | " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << " |\n";
			cout << "+---+---+---+\n";
			cout << " | " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << " |\n";
			cout << "+---+---+---+\n";
		
			cout << "\nPositions (like numeric keypad):\n";
			cout << " 7 | 8 | 9 \n";
			cout << "---+---+---\n";
			cout << " 4 | 5 | 6 \n";
			cout << "---+---+---\n";
			cout << " 1 | 2 | 3 \n\n";
			cout << "Press 1-9 to whack, Q to quit\n";
		}
		
		void spawnMole() {
			for(int i = 0; i < BOARD_SIZE; i++) {
				for(int j = 0; j < BOARD_SIZE; j++) {
					if(board[i][j] == 'M') board[i][j] = ' ';
				}
			}
			
			int row = rand() % BOARD_SIZE;
			int col = rand() % BOARD_SIZE;
			board[row][col] = 'M';
		}
		
		void keypadToCoord(int num, int &row, int &col) {
			switch(num) {
				case 7: row = 0; col = 0; break;
				case 8: row = 0; col = 1; break;
				case 9: row = 0; col = 2; break;
				case 4: row = 1; col = 0; break;
				case 5: row = 1; col = 1; break;
				case 6: row = 1; col = 2; break;
				case 1: row = 2; col = 0; break;
				case 2: row = 2; col = 1; break;
				case 3: row = 2; col = 2; break;
			}
		}
		
		void delay(int milliseconds) {
			clock_t start = clock();
			while((clock() - start) * 1000 / CLOCKS_PER_SEC < milliseconds);
		}
		
	public:
		WhackAMole() : score(0), gameOver(false) {
			srand(time(0));
			clearBoard();
		}
		
		void run() {
			startTime = time(0);
			lastMoleTime = startTime;
			lastFrameTime = startTime;
			
			cout << "Get ready to play Whack-a-Mole!\n";
			cout << "Moles will appear as 'M' on the board.\n";
			cout << "Use number keys (like numeric keypad):\n";
			cout << "7 8 9\n4 5 6\n1 2 3\n";
			cout << "Game lasts for " << GAME_DURATION << " seconds.\n";
			cout << "Press any key to start...";
			_getch();
			
			while(!gameOver) {
				time_t currentTime = time(0);
				double elapsed = difftime(currentTime, startTime);
				
				if(elapsed >= GAME_DURATION) {
					gameOver = true;
					break;
				}
				
				if(difftime(currentTime, lastMoleTime) >= MOLE_APPEAR_TIME) {
					spawnMole();
					lastMoleTime = currentTime;
				}
				
				if(difftime(currentTime, lastFrameTime) * 1000 >= FRAME_DELAY) {
					drawBoard();
					lastFrameTime = currentTime;
				}
				
				if(_kbhit()) {
					char input = _getch();
					
					if(toupper(input) == 'Q') {
						gameOver = true;
						break;
					}
					
					if(input >= '1' && input <= '9') {
						int position = input - '0';
						int row, col;
						keypadToCoord(position, row, col);
						
						if(board[row][col] == 'M') {
							score += MOLE_HIT_POINTS;
							board[row][col] = 'X';
							drawBoard();
							delay(200);
							board[row][col] = ' ';
						}
					}
				}
				delay(50);
			}
			
			system("cls");
			cout << "GAME OVER!\n";
			cout << "Final Score: " << score << "\n";
			cout << "Thanks for playing whack-a-Mole!\n";
		}
};

int main() {
	WhackAMole game;
	game.run();
	return 0;
}
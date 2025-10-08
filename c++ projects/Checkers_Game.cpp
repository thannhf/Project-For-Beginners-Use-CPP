#include<iostream>
#include<string>
#include<cstdlib>
#include<conio.h>
#include<math.h>
using namespace std;

const int SIZE = 8;
char board[SIZE][SIZE];

void initBoard() {
	for(int i = 0; i < SIZE; ++i) {
		for(int j = 0; j < SIZE; ++j) {
			board[i][j] = ((i + j) % 2 == 1) ? '.' : ' ';
		}
	}
	
	for(int i = 0; i < 3; ++i) {
		for(int j = 0; j < SIZE; ++j) {
			if((i + j) % 2 == 1) {
				board[i][j] = 'b';
			}
		}
	}
	
	for(int i = 5; i < SIZE; ++i) {
		for(int j = 0; j < SIZE; ++j) {
			if((i + j) % 2 == 1) {
				board[i][j] = 'r';
			}
		}
	}
}

void printBoard() {
	system("cls");
	
	cout << " ";
	for(int i = 0; i < SIZE; ++i) {
		cout << i << " ";
	}
	cout << "\n";
	
	for(int i = 0; i < SIZE; ++i) {
		cout << i << " ";
		for(int j = 0; j < SIZE; ++j) {
			cout << board[i][j] << " ";
		}
		cout << "\n";
	}
}

bool movePiece(int fromRow, int fromCol, int toRow, int toCol, char player) {
	if(toRow < 0 || toRow >= SIZE || toCol < 0 || toCol >= SIZE) return false;
	if(board[fromRow][fromCol] != player || board[toRow][toCol] != '.') return false;
	
	int dir = (player == 'r') ? -1 : 1;
	int rowDiff = toRow - fromRow;
	int colDiff = toCol - fromCol;
	
	if(rowDiff = dir && abs(colDiff) == 1) {
		board[toRow][toCol] = player;
		board[fromRow][fromCol] = '.';
		return true;
	}
	
	if(rowDiff == 2 * dir && abs(colDiff) == 2) {
		int midRow = fromRow + dir;
		int midCol = fromCol + (colDiff / 2);
		char opponent = (player == 'r') ? 'b' : 'r';
		
		if(board[midRow][midCol] == opponent) {
			board[toRow][toCol] = player;
			board[fromRow][fromCol] = '.';
			board[midRow][midCol] = '.';
			return true;
		}
	}
	return false;
}

bool isGameOver(char& winner) {
	int rCount = 0, bCount = 0;
	for(int i = 0; i < SIZE; ++i) {
		for(int j = 0; j < SIZE; ++j) {
			if(board[i][j] == 'r') rCount++;
			if(board[i][j] == 'b') bCount++;
		}
	}
	
	if(rCount == 0) {
		winner = 'b';
		return true;
	}
	
	if(bCount == 0) {
		winner = 'r';
		return true;
	}
	return false;
}

int main() {
	initBoard();
	char player = 'r';
	char winner;
	
	while(true) {
		printBoard();
		cout << "Player " << player << "'S turn (format: fromRow fromCol toRow toCol):";
		int fromRow, fromCol, toRow, toCol;
		cin >> fromRow >> fromCol >> toRow >> toCol;
		
		if(!cin) {
			cout << "Invalid input. Exiting.\n";
			getch();
			break;
		}
		
		if(movePiece(fromRow, fromCol, toRow, toCol, player)) {
			if(isGameOver(winner)) {
				printBoard();
				cout << "Game over! player " << winner << " wins!\n";
				getch();
				break;
			}
			player = (player == 'r') ? 'b' : 'r';
		} else {
			cout << "Invalid move. Try again.\n";
			getch();
		}
	}
	
	return 0;
}
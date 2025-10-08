#include<iostream>
#include<vector>
#include<algorithm>
#include<ctime>
#include<cstdlib>
#include<iomanip>
#include<conio.h>
using namespace std;

const int SIZE = 4;
const int TOTAL_CELLS = SIZE * SIZE;

void printGrid(const vector<int>& board, const vector<bool>& revealed) {
	system("cls");
	cout << "\n ";
	for(int col = 0; col < SIZE; ++col) {
		cout << setw(3) << col;
	}
	cout << "\n";
	
	for(int row = 0; row < SIZE; ++row) {
		cout << setw(3) << row << " ";
		for(int col = 0; col < SIZE; ++col) {
			int idx = row * SIZE + col;
			if(revealed[idx]) {
				cout << setw(3) << board[idx];
			} else {
				cout << " *";
			}
		}
		cout << "\n";
	}
}

bool allMatched(const vector<bool>& revealed) {
	return all_of(revealed.begin(), revealed.end(), [](bool r) {return r;});
}

int getIndex(int row, int col) {
	return row * SIZE + col;
}

bool isValidChoice(int row, int col, const vector<bool>& revealed) {
	return row >= 0 && row < SIZE && col >= 0 && col < SIZE && !revealed[getIndex(row, col)];
}

int main() {
	srand(static_cast<unsigned int>(time(0)));
	
	vector<int> numbers;
	for(int i = 1; i <= 8; ++i) {
		numbers.push_back(i);
		numbers.push_back(i);
	}
	random_shuffle(numbers.begin(), numbers.end());
	
	vector<bool> revealed(TOTAL_CELLS, false);
	int moves = 0;
	
	cout << "=== Number Match Game (4x4) ===\nMatch all pairs to win.\n";
	
	while(!allMatched(revealed)) {
		printGrid(numbers, revealed);
		
		int r1, c1, r2, c2;
		
		cout << "\nSelect first cell (row col):";
		cin >> r1 >> c1;
		while(!isValidChoice(r1, c1, revealed)) {
			cout << "Invalid. Try again: ";
			cin >> r1 >> c1;
		}
		
		int i1 = getIndex(r1, c1);
		revealed[i1] = true;
		printGrid(numbers, revealed);
		
		cout << "\nSelect second cell (row col): ";
		cin >> r2 >> c2;
		while(!isValidChoice(r2, c2, revealed) || (r1 == r2 && c1 == c2)) {
			cout << "Invalid. Try again: ";
			cin >> r2 >> c2;
		}
		int i2 = getIndex(r2, c2);
		revealed[i2] = true;
		printGrid(numbers, revealed);
		
		++moves;
		
		if(numbers[i1] == numbers[i2]) {
			cout << "? Match!\n";
		} else {
			cout << "? Not a match.\n";
			revealed[i1] = false;
			revealed[i2] = false;
		}
		
		cout << "\nMoves made: " << moves << "\n";
		getch();
	}
	
	cout << "\n?? Congratulations! You matched all pairs in " << moves << " moves.\n";
	return 0;
}
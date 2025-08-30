#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
using namespace std;

void draw_line(int n, char ch);
void board();
void gamescore(char name1[], char name2[], int p1, int p2);
void play_dice(int &score);

int main() {
    int player1 = 0, player2 = 0, lastpos;
    char p1name[80], p2name[80];
    system("cls");
    srand((unsigned)time(NULL));

    draw_line(50, '='); cout << "\n";
    draw_line(50, '='); cout << "\n";
    draw_line(50, '=');
    cout << "\n\t\tSNAKE LADDER GAME\n";
    draw_line(50, '='); cout << "\n";
    draw_line(50, '='); cout << "\n";
    draw_line(50, '=');

    cout << "\n\n\nENTER NAME of player 1: ";
    cin.getline(p1name, 80);
    cout << "\nEnter NAME of player 2: ";
    cin.getline(p2name, 80);

    while (player1 < 100 && player2 < 100) {
        board();
        gamescore(p1name, p2name, player1, player2);

        cout << "\n\n >>> " << p1name << " Now your Turn >> Press any key to play";
        getch();
        lastpos = player1;
        play_dice(player1);
        if (player1 < lastpos)
            cout << "\n\nOops !! Snake found !! You are at position " << player1 << "\n";
        else if (player1 > lastpos + 6)
            cout << "\nGreat!! You got a ladder !! You are at position " << player1;

        cout << "\n\n >>> " << p2name << " Now your Turn >> Press any key to play ";
        getch();
        lastpos = player2;
        play_dice(player2);
        if (player2 < lastpos)
            cout << "\n\n\aOops !! Snake found !! You are at position " << player2 << "\n";
        else if (player2 > lastpos + 6)
            cout << "\n\nGreat!! You got a ladder !! You are at position " << player2 << "\n";

        getch();
    }

    system("cls");
    cout << "\n\n\n";
    draw_line(52, '#');
    cout << "\n\t\tRESULT\n\n";
    draw_line(52, '#');
    cout << endl;
    gamescore(p1name, p2name, player1, player2);
    cout << "\n\n\n";

    if (player1 >= player2)
        cout << "Congratulations !!! " << p1name << ", you won the game!!!\n\n";
    else
        cout << "Congratulations !!! " << p2name << ", You won the game!\n\n";

    draw_line(52, '#');
    getch();
    return 0;
}

void draw_line(int n, char ch) {
    for (int i = 0; i < n; i++)
        cout << ch;
}

void board() {
    system("cls");
    cout << "\n\n";
    draw_line(52, '-');
    cout << "\n | Snake at position \t|\t" << "Ladder at position |\n";
    draw_line(52, '-');
    cout << endl;
    cout << "| From 98 to 28 \t|\tFrom 8 to 26 |\n";
    cout << "| From 92 to 51 \t|\tFrom 21 to 82 |\n";
    cout << "| From 83 to 19 \t|\tFrom 43 to 77 |\n";
    cout << "| From 69 to 33 \t|\tFrom 50 to 91 |\n";
    cout << "| From 59 to 17 \t|\tFrom 62 to 96 |\n";
    cout << "| From 48 to 9 \t|\tFrom 66 to 87 |\n";
    cout << "| From 46 to 5 \t|\tFrom 80 to 100 |\n";
    draw_line(52, '-');
    cout << endl;
}

void gamescore(char name1[], char name2[], int p1, int p2) {
    cout << "\n";
    draw_line(52, '-');
    cout << "\n\t\tGAME STATUS\n";
    draw_line(52, '-');
    cout << "\n > " << name1 << " is at position " << p1 << endl;
    cout << " > " << name2 << " is at position " << p2 << endl;
    draw_line(52, '_');
    cout << endl;
}

void play_dice(int &score) {
    int dice = 1 + rand() % 6;
    cout << "\nYou got " << dice << " point || ";
    score += dice;

    if (score > 100) {
        score -= dice;
        cout << "Roll exceeded 100! Stay at " << score;
        return;
    }

    cout << "Now you are at position " << score;

    switch (score) {
        case 98: score = 28; break;
        case 92: score = 51; break;
        case 83: score = 19; break;
        case 69: score = 33; break;
        case 59: score = 17; break;
        case 48: score = 9; break;
        case 46: score = 5; break;
        case 8:  score = 26; break;
        case 21: score = 82; break;
        case 43: score = 77; break;
        case 50: score = 91; break;
        case 54: score = 93; break;
        case 62: score = 96; break;
        case 66: score = 87; break;
        case 80: score = 100; break;
    }
}
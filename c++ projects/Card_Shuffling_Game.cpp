#include <iostream>
#include <conio.h>
#include <graphics.h>
#include <dos.h>
#include <stdlib.h>
#include <time.h>

void swapCards(int &a, int &b);

int card1[] = {20, 20, 70, 20, 70, 100, 20, 100, 20, 20};
int card2[] = {80, 20, 130, 20, 130, 100, 80, 100, 80, 20};
int card3[] = {140, 20, 190, 20, 190, 100, 140, 100, 140, 20};

int cardVal[3] = {1, 2, 3}; // lưu giá trị lá bài

int main() {
    system("cls");
    int swapnum = 0;
    int driver, mode;

    driver = DETECT;
    initgraph(&driver, &mode, "");

    srand((unsigned)time(NULL));  // chỉ gọi 1 lần

    // vẽ 3 lá bài ban đầu
    setfillstyle(HATCH_FILL, BLUE);
    fillpoly(5, card1);
    fillpoly(5, card2);
    fillpoly(5, card3);

    settextstyle(GOTHIC_FONT, HORIZ_DIR, 4);
    setcolor(BLUE);
    moveto(25, 25); outtext("1");
    moveto(85, 25); outtext("2");
    moveto(145, 25); outtext("3");

    delay(1500);

    // tráo bài
    do {
        char count[10];
        sprintf(count, "%d", swapnum+1);

        delay(1000);

        settextstyle(3, HORIZ_DIR, 2);
        moveto(20, 150);
        outtext("No. of Times cards have been swapped:");
        settextstyle(3, HORIZ_DIR, 3);
        moveto(20, 170);
        outtext(count);

        setfillstyle(HATCH_FILL, BLUE);
        fillpoly(5, card1);
        fillpoly(5, card2);
        fillpoly(5, card3);

        int choice1 = rand() % 3;
        int choice2;
        do {
            choice2 = rand() % 3;
        } while (choice2 == choice1);

        // highlight lá được chọn
        switch(choice1) {
            case 0: setfillstyle(LTSLASH_FILL, YELLOW); fillpoly(5, card1); break;
            case 1: setfillstyle(LTSLASH_FILL, YELLOW); fillpoly(5, card2); break;
            case 2: setfillstyle(LTSLASH_FILL, YELLOW); fillpoly(5, card3); break;
        }
        switch(choice2) {
            case 0: setfillstyle(LTSLASH_FILL, YELLOW); fillpoly(5, card1); break;
            case 1: setfillstyle(LTSLASH_FILL, YELLOW); fillpoly(5, card2); break;
            case 2: setfillstyle(LTSLASH_FILL, YELLOW); fillpoly(5, card3); break;
        }

        // tráo giá trị
        swapCards(cardVal[choice1], cardVal[choice2]);

        swapnum++;
    } while (swapnum < 6);

    // hỏi người chơi
    settextstyle(3, HORIZ_DIR, 3);
    moveto(20, 200);
    setcolor(YELLOW);
    outtext("What is card number 2? ");
    char userChoice = getch();

    moveto(20, 230);
    if (userChoice - '0' == cardVal[1]) {
        outtext("You Win");
    } else {
        outtext("You Lose");
    }

    getch();
    closegraph();
    return 0;
}

void swapCards(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

#include<iostream>
#include<graphics.h>
#include<conio.h>
#include<dos.h>
#include<time.h>
#include<stdio.h>
#include<math.h>

#define ScWidth 1400
#define ScHeight 700
#define OpWidth 400

using namespace std;

double px, py;
int pSize = 20;
int pcolor = LIGHTRED;

int sizeBox = 250;
int x = 250;
int y = 100;
int x2 = x + sizeBox;
int y2 = y;
int x3 = x;
int y3 = y + sizeBox;
int x4 = x + sizeBox;
int y4 = y + sizeBox;

int colorsArr[4] = {
    LIGHTRED,
    LIGHTBLUE,
    LIGHTMAGENTA,
    LIGHTGREEN
};

int angleDeg = 0;          // chạy góc (độ)
int angleStep = 6;        // step độ mỗi vòng, chỉnh mượt/nhanh ở đây
int score = 0;
char txtScore[16];

int changeInterval = 0;   // số vòng (counter max) tới lần đổi màu tiếp
int changeCounter = 0;    // bộ đếm hiện tại
bool restartRequested = false;

static double d2r(double degree) {
    const double pi = 3.14159265358979323846;
    return (degree * (pi / 180.0));
}

// vẽ 4 ô vuông
void drawBoxes() {
    setcolor(LIGHTRED);
    setfillstyle(1, LIGHTRED);
    bar(x, y, x + sizeBox, y + sizeBox);

    setcolor(LIGHTBLUE);
    setfillstyle(1, LIGHTBLUE);
    bar(x2, y2, x2 + sizeBox, y2 + sizeBox);

    setcolor(LIGHTMAGENTA);
    setfillstyle(1, LIGHTMAGENTA);
    bar(x3, y3, x3 + sizeBox, y3 + sizeBox);

    setcolor(LIGHTGREEN);
    setfillstyle(1, LIGHTGREEN);
    bar(x4, y4, x4 + sizeBox, y4 + sizeBox);
}

// kiểm tra va chạm giữa circle (cx,cy,r) và rect (rx,ry,rw,rh)
// phương pháp: tìm điểm gần nhất trên rect tới tâm circle rồi kiểm tra khoảng cách
bool circleRectCollision(double cx, double cy, double r, int rx, int ry, int rw, int rh) {
    double closestX = cx;
    double closestY = cy;
    if (cx < rx) closestX = rx;
    else if (cx > rx + rw) closestX = rx + rw;
    if (cy < ry) closestY = ry;
    else if (cy > ry + rh) closestY = ry + rh;

    double dx = cx - closestX;
    double dy = cy - closestY;
    double dist2 = dx * dx + dy * dy;
    return dist2 <= (r * r);
}

int playerCollision() {
    // px,py là tâm quả cầu, pSize là bán kính dùng cho va chạm
    double cx = px, cy = py, r = pSize;

    // ô 1
    if (circleRectCollision(cx, cy, r, x, y, sizeBox, sizeBox)) {
        return (pcolor == colorsArr[0]) ? 1 : 0;
    }
    // ô 2
    if (circleRectCollision(cx, cy, r, x2, y2, sizeBox, sizeBox)) {
        return (pcolor == colorsArr[1]) ? 1 : 0;
    }
    // ô 3
    if (circleRectCollision(cx, cy, r, x3, y3, sizeBox, sizeBox)) {
        return (pcolor == colorsArr[2]) ? 1 : 0; // <-- sửa lỗi = thành ==
    }
    // ô 4
    if (circleRectCollision(cx, cy, r, x4, y4, sizeBox, sizeBox)) {
        return (pcolor == colorsArr[3]) ? 1 : 0;
    }
    return 0;
}

void GameOver() {
    cleardevice();
    setcolor(WHITE);
    settextstyle(4, 0, 9);
    outtextxy(300, 300, "Game Over");
    settextstyle(4, 0, 2);
    outtextxy(500, 420, "Press any key to restart...");
    getch();
    // yêu cầu reset ở vòng chính
    restartRequested = true;
}

// khởi tạo / reset trạng thái game
void resetGame() {
    score = 0;
    angleDeg = 0;
    pcolor = colorsArr[rand() % 4];
    changeCounter = 0;
    changeInterval = 15 + rand() % 20; // 15..34 frames (ở step nhỏ)
    restartRequested = false;
}

int main() {
    srand((unsigned) time(0));
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    // khởi tạo ban đầu
    resetGame();

    while (1) {
        setcolor(WHITE);
        rectangle(0, 0, ScWidth - OpWidth, ScHeight);
        rectangle(ScWidth - OpWidth, 0, ScWidth, ScHeight);

        // hiện điểm
        snprintf(txtScore, sizeof(txtScore), "%d", score);
        settextstyle(4, 0, 9);
        if (score < 10) outtextxy(ScWidth - 270, 250, txtScore);
        else outtextxy(ScWidth - 320, 250, txtScore);

        settextstyle(4, 0, 1);
        outtextxy(ScWidth - 375, 500, "Controls: ");
        outtextxy(ScWidth - 300, 550, "Spacebar");

        // vẽ ô
        drawBoxes();

        // vẽ vòng tròn đường dẫn (chỉ để nhìn)
        setcolor(WHITE);
        circle(500, 350, 100);

        // xử lý phím
        if (kbhit()) {
            char option = getch();
            if (option == 32) { // space
                if (playerCollision() == 1) {
                    score++;
                } else {
                    GameOver();
                }
            }
        }

        // tính vị trí tâm quả cầu theo góc tròn
        // dùng bán kính 90 như trước, tâm ở (500,350)
        double rad = d2r((double)angleDeg);
        px = -sin(rad) * 90.0 + 500.0;
        py = -cos(rad) * 90.0 + 350.0;

        // vẽ quả cầu
        setcolor(WHITE);
        setfillstyle(1, pcolor);
        fillellipse((int)px, (int)py, pSize, pSize);

        // cập nhật góc
        angleDeg += angleStep;
        if (angleDeg >= 360) angleDeg -= 360;

        // cập nhật counter đổi màu theo interval
        changeCounter++;
        if (changeCounter >= changeInterval) {
            pcolor = colorsArr[rand() % 4];
            changeCounter = 0;
            changeInterval = 10 + rand() % 30; // 10..39 "ticks"
        }

        delay(50); // fps ~ 20
        cleardevice();

        if (restartRequested) {
            resetGame();
        }
    }

    getch();
    closegraph();
    return 0;
}
#include <graphics.h>
#include <conio.h>
#include <math.h>
#include <time.h>
#include <stdio.h>

#define PI 3.14159265

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");   // không cần đường dẫn BGI nếu dùng WinBGI
    
    int midx = getmaxx() / 2;
    int midy = getmaxy() / 2;
    int radius = 200;

    while (!kbhit()) {
        // Lấy thời gian hệ thống
        time_t t = time(NULL);
        struct tm *now = localtime(&t);

        int hr  = now->tm_hour % 12;
        int min = now->tm_min;
        int sec = now->tm_sec;

        // Vẽ mặt đồng hồ
        setlinestyle(SOLID_LINE, 0, 2);
        settextstyle(SANS_SERIF_FONT, 0, 2);
        circle(midx, midy, radius);

        // Vẽ các số 1–12
        for (int i = 1; i <= 12; i++) {
            double angle = (90 - i * 30) * PI / 180.0;
            int x = midx + (radius - 30) * cos(angle);
            int y = midy - (radius - 30) * sin(angle);

            char label[3];
            sprintf(label, "%d", i);
            settextjustify(CENTER_TEXT, CENTER_TEXT);
            outtextxy(x, y, label);
        }

        // Tính toán góc kim
        double sec_angle  = (90 - sec * 6) * PI / 180.0;
        double min_angle  = (90 - (min * 6 + sec * 0.1)) * PI / 180.0;
        double hour_angle = (90 - (hr * 30 + min * 0.5)) * PI / 180.0;

        // Vẽ kim giây (màu đỏ)
        setcolor(RED);
        line(midx, midy,
             midx + (radius - 20) * cos(sec_angle),
             midy - (radius - 20) * sin(sec_angle));

        // Vẽ kim phút (màu xanh lá)
        setcolor(GREEN);
        line(midx, midy,
             midx + (radius - 40) * cos(min_angle),
             midy - (radius - 40) * sin(min_angle));

        // Vẽ kim giờ (màu xanh dương)
        setcolor(BLUE);
        line(midx, midy,
             midx + (radius - 80) * cos(hour_angle),
             midy - (radius - 80) * sin(hour_angle));

        // Vẽ tâm đồng hồ
        setcolor(WHITE);
        setfillstyle(SOLID_FILL, WHITE);
        fillellipse(midx, midy, 5, 5);

        delay(1000);
        cleardevice();
    }

    getch();
    closegraph();
    return 0;
}
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <sys/wait.h>
#define N 50000

double f(int x, int y) {
    return x * x * x * sin((double)x) - y * y * y * cos((double)y) + x * y * y;
}

int main(void) {
    double maxp = 0, maxf = 0;
    int x_maxp = 0, y_maxp = 0, x_maxf = 0, y_maxf = 0;

    int k = fork();
    if (k > 0) {
        for (int x = 0; x <= N; x += 2) {
            for (int y = 0; y <= N; y++) {
                double cal = f(x, y);
                double abs_cal = fabs(cal);
                if (abs_cal > maxp) {
                    maxp = abs_cal;
                    x_maxp = x;
                    y_maxp = y;
                }
            }
        }
        wait(NULL);
        printf("fin pere\n");
    } else {
        for (int x = 1; x <= N; x += 2) {
            for (int y = 0; y <= N; y++) {
                double cal = f(x, y);
                double abs_cal = fabs(cal);
                if (abs_cal > maxf) {
                    maxf = abs_cal;
                    x_maxf = x;
                    y_maxf = y;
                }
            }
        }
        printf("fin fils\n");
        exit(0);
    }

    if (maxp > maxf)
        printf("pere %f, fils %f: le max est atteint en (x=%d, y=%d) et vaut %f\n", maxp, maxf, x_maxp, y_maxp, maxp);
    else
        printf("fils %f, pere %f: le max est atteint en (x=%d, y=%d) et vaut %f\n", maxf, maxp, x_maxf, y_maxf, maxf);
}

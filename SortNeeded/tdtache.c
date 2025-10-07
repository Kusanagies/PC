#include <stdio.h>
#include <math.h>
#include <float.h>
#include <time.h>

double f(double x, double y) {
    return pow(x, 3) * cos(x) - pow(y, 3) * sin(x) - pow(x, 3) / pow(y, 2);
}

int main() {
    double max_value = -DBL_MAX;
    double max_x = 1.0, max_y = 1.0;
    clock_t start, end;
    double cpu_time_used;

    start = clock();

    for (double x = 1.0; x <= 5000.0; x += 1.0) {
        for (double y = 1.0; y <= 5000.0; y += 1.0) {
            double current = fabs(f(x, y));
            if (current > max_value) {
                max_value = current;
                max_x = x;
                max_y = y;
            }
        }
    }

    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    
    printf("Maximum de |f(x,y)| : %e\n", max_value);
    printf("Atteint en x = %.2f, y = %.2f\n", max_x, max_y);
    printf("Temps de calcul : %f secondes\n", cpu_time_used);

    return 0;
}

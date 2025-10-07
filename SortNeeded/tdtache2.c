#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <float.h>
#include <time.h>

typedef struct {
    double max_value;
    double max_x;
    double max_y;
} Result;

double f(double x, double y) {
    return pow(x, 3) * cos(x) - pow(y, 3) * sin(x) - pow(x, 3) / pow(y, 2);
}

void* search_even(void* arg) {
    Result* result = (Result*)arg;
    result->max_value = -DBL_MAX;
    for (double x = 2.0; x <= 5000.0; x += 2.0) {
        for (double y = 1.0; y <= 5000.0; y += 1.0) {
            double current = fabs(f(x, y));
            if (current > result->max_value) {
                result->max_value = current;
                result->max_x = x;
                result->max_y = y;
            }
        }
    }
    return NULL;
}

void* search_odd(void* arg) {
    Result* result = (Result*)arg;
    result->max_value = -DBL_MAX;
    for (double x = 1.0; x <= 5000.0; x += 2.0) {
        for (double y = 1.0; y <= 5000.0; y += 1.0) {
            double current = fabs(f(x, y));
            if (current > result->max_value) {
                result->max_value = current;
                result->max_x = x;
                result->max_y = y;
            }
        }
    }
    return NULL;
}

int main() {
    pthread_t thread_even, thread_odd;
    Result result_even, result_odd;
    clock_t start, end;
    double cpu_time_used;

    start = clock();

    pthread_create(&thread_even, NULL, search_even, &result_even);
    pthread_create(&thread_odd, NULL, search_odd, &result_odd);

    pthread_join(thread_even, NULL);
    pthread_join(thread_odd, NULL);

    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    Result global_max = (result_even.max_value > result_odd.max_value) ? result_even : result_odd;

    printf("Maximum de |f(x,y)| : %e\n", global_max.max_value);
    printf("Atteint en x = %.2f, y = %.2f\n", global_max.max_x, global_max.max_y);
    printf("Temps de calcul : %f secondes\n", cpu_time_used);

    return 0;
}

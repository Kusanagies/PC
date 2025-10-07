#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <sys/wait.h>

#define N 50000

double f(int x, int y) {
    return x * x * x * sin((double)x) - y * y * y * cos((double)y) + x * y * y;
}

int main(void) {
    double max_values[4] = {0}; // max_values[0] pour le père, max_values[1..3] pour les fils
    int x_max[4] = {0}, y_max[4] = {0};

    pid_t pids[3]; // Tableau pour stocker les PID des 3 fils

    // Création des 3 fils
    for (int i = 0; i < 3; i++) {
        pids[i] = fork();
        if (pids[i] == 0) {
            // Code des fils
            int startmod = i + 1; // Chaque fils traite x % 4 == startmod
            for (int x = startmod; x <= N; x += 4) {
                for (int y = 0; y <= N; y++) {
                    double cal = f(x, y);
                    double abs_cal = fabs(cal);
                    if (abs_cal > max_values[startmod]) {
                        max_values[startmod] = abs_cal;
                        x_max[startmod] = x;
                        y_max[startmod] = y;
                    }
                }
            }
            printf("Fils %d terminé (mod %d)\n", getpid(), startmod);
            exit(0);
        } else if (pids[i] < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        }
    }

    // Code du père : traite x % 4 == 0
    for (int x = 0; x <= N; x += 4) {
        for (int y = 0; y <= N; y++) {
            double cal = f(x, y);
            double abs_cal = fabs(cal);
            if (abs_cal > max_values[0]) {
                max_values[0] = abs_cal;
                x_max[0] = x;
                y_max[0] = y;
            }
        }
    }

    // Attendre la fin des 3 fils
    for (int i = 0; i < 3; i++) {
        wait(NULL);
    }
    printf("Père terminé\n");

    // Trouver le maximum global
    double global_max = max_values[0];
    int global_x = x_max[0], global_y = y_max[0];
    for (int i = 1; i < 4; i++) {
        if (max_values[i] > global_max) {
            global_max = max_values[i];
            global_x = x_max[i];
            global_y = y_max[i];
        }
    }

    // Afficher le résultat
    printf("Le maximum global est atteint en (x=%d, y=%d) et vaut %f\n", global_x, global_y, global_max);

    return 0;
}


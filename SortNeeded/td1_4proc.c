#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <sys/wait.h>
#include <sys/time.h>

#define N 5000

double f(int x,int y){
    return x * x * x * sin((double)x) - y * y *y * cos((double)y) + x * y * y;
}

int main(void){
    double max_values[4] = {0};
    int x_max[4] = {0}, y_max[4] = {0};
    pid_t pids[3];
    int status;

    struct timeval start, end;
    gettimeofday(&start,NULL);

    //Création des 3 fils
    for(int i = 0;i < 3;i++){
        pids[i] = fork();
        if(pids[i] < 0){
            perror("fork");
            exit(EXIT_FAILURE);
        }
        if(pids[i] == 0){   //Code du fils
            double max_local = 0;
            int x_max_local = 0, y_max_local = 0;

            for(int x = i;x <= N;x = x + 4){
                for(int y = 0;y <= N; y++){
                    double cal = f(x,y);
                    double abs_cal = fabs(cal);
                    if(abs_cal > max_local){
                        max_local = abs_cal;
                        x_max_local = x;
                        y_max_local = y;
                    }
                }
            }
            exit((int)(max_local));
        }
    }

    //Code du père
    double max_pere = 0;
    int x_max_pere = 0,y_max_pere = 0;
    for(int x = 3;x <= N;x +=4){
        for(int y = 0;y <= N;y++){
            double cal = f(x,y);
            double abs_cal = fabs(cal);
            if(abs_cal > max_pere){
                max_pere = abs_cal;
                x_max_pere = x;
                y_max_pere = y;
            }
        }
    }
    max_values[0] = max_pere;
    x_max[0] = x_max_pere;
    y_max[0] = y_max_pere;

    for(int i = 0;i < 3;i++){
        waitpid(pids[i],&status,0);
        if(WIFEXITED(status)){
            max_values[i+1] = (double)WEXITSTATUS(status);
        }
    }
    gettimeofday(&end, NULL);
    double time_spent = (end.tv_sec - start.tv_sec) * 1e6;
    time_spent = (time_spent + (end.tv_usec - start.tv_usec)) * 1e-6;

    // Détermination du maximum global
    double max_global = max_values[0];
    int x_max_global = x_max[0], y_max_global = y_max[0];
    for (int i = 1; i < 4; i++) {
        if (max_values[i] > max_global) {
            max_global = max_values[i];
            x_max_global = x_max[i];
            y_max_global = y_max[i];
        }
    }

    printf("Max global : %f en (x=%d, y=%d) en %f secondes\n", max_global, x_max_global, y_max_global, time_spent);

    return 0;
}
#include <stdio.h>
#include <pthread.h>

int val = 10000;
int N  = 10;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
void *inc(){
    pthread_mutex_lock(&mutex);
    for(int i = 0;i < N;i++){
        pthread_mutex_lock(&mutex);
        val++;
        pthread_mutex_unlock(&mutex);
    }

}
void *dec(){
    for(int i = 0;i < N;i++){
        pthread_mutex_lock(&mutex);
        val--;
        pthread_mutex_unlock(&mutex);
    }

}
int main(){
    pthread_t T1,T2;

    pthread_create(&T1,NULL,inc,NULL);
    pthread_create(&T2,NULL,dec,NULL);

    pthread_join(T1,NULL);
    pthread_join(T2,NULL);

    printf("Val vaut: %d\n",val);
    return 0;
}
#include <stdio.h>
#include <pthread.h>

//Sans protection enlever les lignes avec les pthreads.

//Variable globale 
int Val = 0;

//Mutex pour la synchronisation 
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

//Fonction incrementer facon securisé 
void Inc(){
    pthread_mutex_lock(&mutex);
    Val = Val + 1;
    pthread_mutex_unlock(&mutex);
}

//Fonction décrémenter facon sécurisé
void Dec(){
    pthread_mutex_lock(&mutex);
    Val = Val - 1;
    pthread_mutex_unlock(&mutex);
}

int main(){



    
    Inc();
    Dec();
    printf("Val =  %d\n",Val);
    return 0;
}
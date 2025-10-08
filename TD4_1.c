#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

#define MAX_RESSOURCES 100
#define NB_TASKS 10

int NbRessDisponibles = MAX_RESSOURCES;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void request(int m, int task_id) {
    pthread_mutex_lock(&mutex);
    printf("Tâche %d : Demande %d ressources (disponibles : %d)\n", task_id, m, NbRessDisponibles);

    while (NbRessDisponibles < m) {
        printf("Tâche %d : En attente (ressources insuffisantes : %d)\n", task_id, NbRessDisponibles);
        pthread_cond_wait(&cond, &mutex);
    }

    NbRessDisponibles -= m;
    printf("Tâche %d : A obtenu %d ressources (restantes : %d)\n", task_id, m, NbRessDisponibles);
    pthread_mutex_unlock(&mutex);
}

void release(int m, int task_id) {
    pthread_mutex_lock(&mutex);
    NbRessDisponibles += m;
    printf("Tâche %d : Libère %d ressources (disponibles : %d)\n", task_id, m, NbRessDisponibles);
    pthread_cond_broadcast(&cond); // Réveiller tous les threads en attente
    pthread_mutex_unlock(&mutex);
}

void* task(void* arg) {
    int task_id = *(int*)arg;
    int m = (task_id % 5 + 1) * 10; // Chaque tâche demande entre 10 et 50 ressources

    while (true) {
        request(m, task_id);
        // Simuler l'utilisation des ressources
        printf("Tâche %d : Utilise %d ressources...\n", task_id, m);
        usleep(10000); // Attendre 10 ms
        release(m, task_id);
        usleep(50000); // Attendre avant de refaire une demande
    }

    return NULL;
}

int main() {
    pthread_t threads[NB_TASKS];
    int task_ids[NB_TASKS];

    for (int i = 0; i < NB_TASKS; i++) {
        task_ids[i] = i + 1;
        pthread_create(&threads[i], NULL, task, &task_ids[i]);
    }

    // Attendre 5 secondes pour observer le comportement
    sleep(5);

    // Terminer les threads (en pratique, il faudrait une condition d'arrêt propre)
    // Ici, on ne le fait pas pour simplifier l'exemple.

    return 0;
}

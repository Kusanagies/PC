#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

typedef struct {
    int id;
    const char *phrase;
} Task;

void *afficher_phrase(void *arg){
    Task *task = (Task *)arg;
    printf("T%d: %s\n",task->id, task->phrase);
    return NULL;
}


int main(void) {
    pthread_t threads[4];
    Task tasks[4];

    tasks[0] = (Task){1, "Souvent, pour s’amuser, les hommes d’équipage"};
    tasks[1] = (Task){2, "Prennent des goélands, vastes oiseaux des mers,"};
    tasks[2] = (Task){3, "Qui suivent, indolents compagnons de voyage,"};
    tasks[3] = (Task){4, "Le navire glissant sur les gouffres amers."};

    for(int i = 0;i < 4;i++){
        if(pthread_create(&threads[i],NULL, afficher_phrase,&tasks[i])!= 0){
            perror("pthread_create");
            return 1;
        }
    }
    for(int i = 0;i < 4;i++){
        if(pthread_join(threads[i],NULL)!=0){
            perror("pthread_join");
            return 1;
        }
    }

    return 0;
}

//La répartition en 4 activités autonomes ne sont pas ordonnée, la sortie dépend de l'ordre que l'ordonnanceur va donner aux taches

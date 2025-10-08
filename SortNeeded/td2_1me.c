#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>



void *affCar(void *arg){
   char c;

   c = * (char *)arg;

   while(1){
      putchar(c);
   }
}

void *affCar2(void *arg){
   char c;
int i;

   c = * (char *)arg;

   for (i=0; i<1000; i++){
      putchar( c );
   }
}
  pthread_t cree_tache(void * (*start_routine)(void *), void * arg){
   pthread_t id;
   int erreur;

   erreur = pthread_create( &id, NULL, start_routine, arg);
   if (erreur != 0){
	   perror( "Echec creation de tâche Posix" );
	   exit(-1);
   }
   return id;
}
	int main(void)
{
   char *leCar; int i;
      pthread_t tache_Posix_B;
   pthread_t tache_Posix_C;

   leCar = (char*) malloc(1*sizeof(char)); *leCar = 'B';
      tache_Posix_B = cree_tache( affCar2, (void*) leCar);

   leCar = (char*) malloc(1*sizeof(char)); *leCar = 'C';
   tache_Posix_C = cree_tache( affCar2, (void*) leCar);

   for (i=0; i<1000; i++){
      putchar('Z');
   }
   pthread_join( tache_Posix_B, NULL);

   pthread_join( tache_Posix_C, NULL);
} 
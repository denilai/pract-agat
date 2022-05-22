#include <stdio.h> 
#include <pthread.h> 
#include <semaphore.h> 
#include <unistd.h> 
#include <stdlib.h>
  
sem_t sem; 
  
void* first(void* arg) 
{ 
    FILE *fp;
    //wait 
    sem_wait(&sem); 
    printf("\nSeizing control of the semaphore\n"); 
  
    //critical section 
    sleep(4); 
    if ((fp=fopen("semtest.txt", "a")) == NULL){
      perror("posixsem.fopen");
      exit(1);
    }
    fputs("Caprture file for write. Thread 1\n", fp);
    fclose(fp);
      
    printf("\nTransfer of control over the semaphore\n"); 
    sem_post(&sem); 
} 

void* second(void* arg) 
{ 
    FILE *fp;
    //wait 
    sem_wait(&sem); 
    printf("\nSeizing control of the semaphore\n"); 
  
    //critical section 
    sleep(4); 
    if ((fp=fopen("semtest.txt", "a")) == NULL){
      perror("posixsem.fopen");
      exit(1);
    }
    fputs("Caprture file for write. Thread 2\n", fp);
    fclose(fp);
      
    printf("\nTransfer of control over the semaphore\n"); 
    sem_post(&sem); 
} 
  
  
int main() 
{ 
    sem_init(&sem, 0, 1); 
    pthread_t t1,t2; 
    pthread_create(&t1,NULL,first,NULL); 
    //sleep(2); 
    pthread_create(&t2,NULL,second,NULL); 
    pthread_join(t1,NULL); 
    pthread_join(t2,NULL); 
    sem_destroy(&sem); 
    return 0; 
}

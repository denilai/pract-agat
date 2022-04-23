#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024

int main(int argc, char *argv[])
{
    key_t key;
    int shmid;
    char *data;
    int mode;
    
    //key = 1234;
    //
    if (argc != 2){
      printf("USAGE: sharedmem [name of segment]\n");
      exit (1);
    }

    if ((key = ftok("shmdemo.c", 'R')) == -1) {
        perror("ftok");
        exit(1);
    }

    /* connect to the segment: */
    if ((shmid = shmget(key, SHM_SIZE, 0644 | IPC_CREAT)) == -1) 
    {
        perror("shmget");
        exit(1);
    }

    /* attach to the segment to get a pointer to it: */
    data = shmat(shmid, (void *)0, 0);
    if (data == (char *)(-1)) 
    {
        perror("shmat");
        exit(1);
    }

    /*Write into the segment*/

    printf("Writing to segment: \"%s\"\n", argv[1]);
    strncpy(data, argv[1], SHM_SIZE);

    /* Reading from the segment*/
    printf("Reading form the segment: \"%s\"\n", data);

    /* detach from the segment: */
    if (shmdt(data) == -1) 
    {
        perror("shmdt");
        exit(1);
    }

    return 0;
}

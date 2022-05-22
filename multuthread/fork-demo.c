#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
    pid_t t;
    setbuf(stdout, NULL); /* stdout не буферизуется */
    int a;
    a=89;
    int status;
    printf("До создания процесса-потомка a = %d\n",a);
    t=fork();
    if(t<0){
       perror("ERROR: Ошибка создания процесса\n");
       return 1;
    }
    if(t==0){
       printf("В дочернем процессе a = %d\n",a);
       printf("Дочерний PID = %d\n",getpid());
       printf("Родительский PID = %d\n",getppid());
       exit(1);
    }
    if (t>0)
    {
       a = 10;
       printf("a = 10\n");
       printf("В родительском роцессе a = %d\n",a);
       printf("Родительский PID =  %d\n",getpid());
       printf("Дочерний PID =  %d\n",t);
       wait(&status);
       printf("Результат функции wait() =  0x%04x\n" , status);
    }
    return 0;
}

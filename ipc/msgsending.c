#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXSIZE 128

int msqid;
void sigint_handler(int sig){
  printf("\n=== handle SIGINT ===\n");
  msgctl(msqid,IPC_RMID,NULL);
  exit (0);
}

typedef struct msgbuf {
    long mtype;
    char mtext[MAXSIZE];
}msgbuf;

int main()
{
    struct sigaction sa; /* обьявление структуры для обработки сигнала */
    
    sa.sa_handler = sigint_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIGINT, &sa, NULL) == -1){
      perror("sigaction");
      exit(1);
    }
    int msgflg = IPC_CREAT | 0666;
    key_t key;
    msgbuf sbuf;
    size_t buflen; 
    key = ftok("/home/denilai/myFile", 'b');
    //key = 1234;

    if ((msqid = msgget(key, msgflg )) < 0)
    { 
        perror("msgsnd");
        exit(1);
    }
    while (1)
    {
      sbuf.mtype = 1;
      //Тип сообщения
      printf("Введите сообщение: ");
      scanf("%[^\n]",sbuf.mtext);
      getchar();
      buflen = strlen(sbuf.mtext) + 1;
   /*Если в очереди недостаточно свободного места, то функция msgsnd() по умолчанию блокируется до тех пор, пока свободное место не станет доступным. Если IPC_NOWAIT указан в msgflg, то вызов вместо этого завершается ошибкой EAGAIN.*/
      if (msgsnd(msqid, &sbuf, buflen, IPC_NOWAIT) < 0)
      { 
        printf ("Ошибка при отправке сообщения\n"); perror("msgsnd");
        exit(1);
      }
      else printf("Сообщение отправлено\n");
    }

    msgctl(msqid,IPC_RMID,NULL);
    exit(0);
}

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 128

typedef struct msgbuf
{
    long mtype;
    char mtext[MAXSIZE];
} msgbuf;


int main()
{
    int msqid;
    key_t key;
    msgbuf rcvbuffer;

    //key = 1234;
    key = ftok("/home/aj/myFile", 'b');


    if ((msqid = msgget(key, 0666)) < 0)
    {
      perror("msgsnd");
      exit(1);
    }
    int byte_size;
     //Получить ответ типа сообщения 1.
     //Если сообщение запрошенного типа недоступно и IPC_NOWAIT не указан в msgflg, вызывающий процесс блокируется до тех пор, пока не возникнет одно из следующих условий:
     //Сообщение нужного типа помещается в очередь.
     //Очередь сообщений удаляется из системы. В этом случае системный вызов завершается ошибкой с errno, установленным в EIDRM.
    if ((byte_size = msgrcv(msqid, &rcvbuffer, MAXSIZE, 1, 0)) < 0)
    {
       perror("msgrcv");
       exit(1);    
    }
    printf("%s\n", rcvbuffer.mtext);
    printf("Размер сообщения = %dБ\n",byte_size-1);
    exit(0);
}

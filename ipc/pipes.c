#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include<string.h>
#include <sys/types.h>


int main(void)
{
        int fd[2], nbytes;
        char string[] = "Организуем межпроцессное взаимодействие!\n";
        char readbuffer[80]; pipe(fd);
        pid_t childpid;
        childpid = fork();
        //создать дочерний процесс
        if(childpid == -1)
        {
          perror("fork creation");
          exit(1);
        }
        //закрыть входной канал дочернего процесса
        if(childpid == 0)
        {
          /* Дочерний процесс закрывает дескриптор для четния */ 
          close(fd[0]);
          /* Отправить "строку" через дескриптор записи*/ 
          write(fd[1], string, (strlen(string)+1));
          exit(0);
        }
        else
        {
          /* Родительский процесс закрывает дескриптор для записи*/ 
          close(fd[1]);
          /* Чтение строки из канала */ 
          nbytes = read(fd[0], readbuffer, sizeof(readbuffer)); printf("Строка, полученная от процесса %d: %s", childpid, readbuffer);
        }
        return(0);
}

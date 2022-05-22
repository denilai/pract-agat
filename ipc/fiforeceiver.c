#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#define FIFO_FILE "fifo"
#define BUFF_SIZE 80

int main(void)
{
  FILE *fp;
  char readbuf[80];

  /* Create the FIFO if it does not exist */
  umask(0);
  /* int mknod(char *pathname, int mode, int dev); 
   *Режим обозначается константой S_IFIFO из заголовочного файла <sys/stat.h> */
  unlink(FIFO_FILE);
  mknod(FIFO_FILE, S_IFIFO|0666, 0);

  while(1)
  {
     if((fp = fopen(FIFO_FILE, "r")) == NULL){
       perror("fifoserver.fopen");
     }
     fgets(readbuf, BUFF_SIZE, fp);
     printf("Received string: %s\n", readbuf);
     fclose(fp);
  }

  return(0);
}

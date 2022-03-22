#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{

    int pid = fork();
    if (pid > 0)
    {
      printf("\nParent process ID : %d\n\n",getpid());
    }
    else if (pid == 0)
    {
      printf("\nChild process ID: %d\n",getpid());
      printf("\nParent Process ID: %d\n",getppid());

      sleep(10);

      // by this time, parent process has finished execution.
      // and it will be killed.
      // if you see the parent ID, it will be changed.
              // this is orphan process
    printf("\nChild process  ID: %d\n",getpid());
    printf("\nParent process ID: %d\n",getppid());
    }
    return 0;
}

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

void sigint_handler(int sig){
  printf("\n===handle SIGTERM===\n");
}

int main (int argc, char* argv[]){
  int pid = fork();
  int chpid = getpid();
  if (pid == -1) {
    return 1;
  }
  if (pid == 0){
      void sigint_handler(int sig);
      char s[200];
      struct sigaction sa; /* обьявление структуры для обработки сигнала */
      
      sa.sa_handler = sigint_handler;
      sa.sa_flags = 0;
      sigemptyset(&sa.sa_mask);
      if (sigaction(SIGTERM, &sa, NULL) == -1){
        perror("sigaction");
        exit(1);
      }

    while (1) {
      printf("We are in the child process with PID = %d\n", getpid());
      sleep(1);
    }
    return 0;
  }
  else {
    printf("Send SIGKILL signal to child process with PID = %d\n", pid);
    sleep(3);
    kill(pid, SIGTERM);
    wait(NULL);
    
  }

}

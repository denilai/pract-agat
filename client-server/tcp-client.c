#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <unistd.h>
#define SIZE 1000

//main functions
int main()
{
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
// server address
  struct sockaddr_in serverAddress;
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(9002);
  serverAddress.sin_addr.s_addr = INADDR_ANY;

// communicates with listen
  if (connect(sockfd, (struct sockaddr *)&serverAddress, sizeof(serverAddress))!=0)
  {
    perror("client.connect()");
    exit(1);
  }

  char serverResponse[SIZE];
  char clientMessage[SIZE]="Message from client";
  if (recv(sockfd, &serverResponse, sizeof(serverResponse), 0)==-1)
  {
    perror("client.recv()");
    exit(1);
  }
  printf("Received data from server : %s", serverResponse);
  if (send(sockfd, clientMessage, sizeof(serverResponse), 0)==-1)
  {
    perror("client.send()");
    exit(1);
  }

  //closing the socket
  close(sockfd);
  return 0;
}

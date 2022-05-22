#include<stdio.h> 
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
int main()
{
  int sockfd, clientfd;
  struct sockaddr_in serverAddr, cliAddr;
  socklen_t addr_size;
  int len = sizeof(cliAddr);
  char serverMessage[256] = "Hello from server\n";
  char clientResponse[1000];

  //create a socket file descriptor
  sockfd = socket(PF_INET, SOCK_STREAM, 0);
  
  //fill the serverAddr structure
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(9002); 
  serverAddr.sin_addr.s_addr = INADDR_ANY;

  // bind the address
  if(bind(sockfd, (struct sockaddr *) &serverAddr, sizeof(serverAddr))!=0)
  {
    perror("server.bind()");
    exit(1);
  }

  // listen 
  if(listen(sockfd,5)==0)
  {

    //accept the connection
    clientfd = accept(sockfd, (struct sockaddr *) &cliAddr, &len);

    // send the data
    if (send(clientfd,serverMessage,sizeof(serverMessage),0)==-1)
    {
      perror("server.send()");
      exit(1);
    }
    if (recv(clientfd,&clientResponse,sizeof(clientResponse),0)==-1)
    {
      perror("server.recv()");
      exit(1);
    }
    printf("Received data from client : %s\n", clientResponse);

    close(sockfd);
  }
  return 0;
}

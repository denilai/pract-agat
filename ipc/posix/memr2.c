#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define NUM 3
#define SIZE (NUM * sizeof(int))

#define FILE_PATH "/shared-segment"


int main(){
  int fd = shm_open(FILE_PATH, O_RDONLY, 0600); 
  if (fd < 0)
  {
    perror("shm_open()");
    return 0;
  }

  int *data = (int *) mmap(0, SIZE, PROT_READ, MAP_SHARED,  fd, 0);
  printf("sender mapped address : %p\n",data);

  for (int i =0; i < NUM; i++){
    printf("%d\n", data[i]);
  } 
  munmap(data, SIZE);
  close(fd);
  shm_unlink(FILE_PATH);
  return 0;
}

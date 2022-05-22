#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define NUM 3
#define SIZE (NUM * sizeof(int))

#define FILE_PATH "/shared-segment"


int main(){
  int fd = shm_open(FILE_PATH, O_CREAT | O_EXCL | O_RDWR, 0600);
  if (fd < 0)
  {
    perror("shm_open()");
    return 0;
  }

  ftruncate(fd, SIZE);
  int *data = (int *) mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED,  fd, 0);
  printf("sender mapped address : %p\n",data);

  for (int i =0; i < NUM; i++){
    data[i] = i;
  } 
  munmap(data, SIZE);
  close(fd);
  return 0;
}

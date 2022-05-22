#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#define FILE_PATH "/shared_segment"


int main(int argc, char *argv[])
{
  int res;
  int fd;
  char data[256];
  void *addr;

  // get shared memory file descriptor
  fd = shm_open(FILE_PATH, O_RDONLY, S_IRUSR | S_IWUSR);
  if (fd == -1)
  {
    perror("open");
    return 10;
  }

  // map shared memory 
  addr = mmap(NULL, 256, PROT_READ, MAP_SHARED, fd, 0);

  // place data into memory
  memcpy(data, addr, 256);

  printf("Read from shared memory: \"%s\"\n", data);

  return 0;
}

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
  int len;
  void *addr;
  char data[256] = "Hello World";


  // get shared memory file descriptor
  fd = shm_open(FILE_PATH, O_CREAT | O_EXCL | O_RDWR, 0600);
  if (fd < 0) {
    perror("shm_open()");
    return 1;
  }

  // increase the size
  res = ftruncate(fd, 256);

  // map shared memory
  addr = mmap(NULL, 256, PROT_WRITE, MAP_SHARED, fd, 0);

  // place data into memory
  len = strlen(data) + 1;
  memcpy(addr, data, len);


  sleep(2);

  // mmap cleanup
  res = munmap(addr, 256);

  // shm_open cleanup
  fd = shm_unlink(FILE_PATH);

  return 0;
}

/* ch04-holes.c --- Демонстрация lseek() и дыр в файлах. */
#include <stdio.h> /* для fprintf(), stderr, BUFSIZ */
#include <errno.h> /* объявление errno */
#include <fcntl.h> /* для flags для open() */
#include <string.h> /* объявление strerror() */
#include <unistd.h> /* для ssize_t */
#include <sys/types.h> /* для off_t, etc. */
#include <sys/stat.h>  /* для mode_t */


struct person {
  char name[10]; /* имя */
  char id[10]; /* идентификатор */
  off_t pos; /* положение в файле для демонстрации */
} people[] = {
  { "arnold", "123456789", 0 },
  { "miriam", "987654321", 10240 },
  { "joe", "192837465", 81920 }
};


int main(int argc, char* argv[]){
  int fd;
  int i, j;
  if (argc < 2) {
    fprintf(stderr, "usage: %s file ", argv[0]);
    return 1;
  }
  fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0666);
  if (fd < 0) {
    fprintf(stderr, "%s: %s: cannot open for read/write: %s ",
    argv[0], argv[1], strerror(errno));
    return 1;
  }
  j = sizeof(people) / sizeof(people[0]); /* число элементов */
  for (i = 0; i < j; i++) {
  if (lseek(fd, people[i].pos, SEEK_SET) < 0) {
    fprintf(stderr, "%s: %s: seek error: %s ",
    argv[0], argv[1], strerror(errno));
    (void)close(fd);
   return 1;
  }
  if (write(fd, &people[i], sizeof(people[i])) != sizeof(people[i])) {
    fprintf(stderr, "%s: %s: write error: %s ",
    argv[0], argv[1], strerror(errno));
    (void)close(fd);
    return 1;
  }
 }
 /* здесь все нормально */
 (void)close(fd);
 return 0;
}

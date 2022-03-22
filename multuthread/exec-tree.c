#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    char * args[]={
       "/bin/tree", //путь к программе (или другая информация)
       "/bin",      //первый параметр командной строки
       NULL         //конец блока параметров.
    };
    int t = execv("/usr/bin/tree", args);
    if ( t < 0)
      printf("Ошибка запуска\n");
    return 0;
}

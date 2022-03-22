//особенности работы функции fork
#include <unistd.h>
#include <stdio.h>

int main(){
    pid_t t;
    int a;
    a=89;
    printf("До %d\n",a);
    t=fork();
    if(t==-1){
       printf("Ошибка\n");
       return 1;
    }
    printf("После %d\n",a);
    if(!t){
       printf("Дочерний %d\n",getpid());
       printf("Родительский %d\n",getppid());
    }else{
       printf("Родительский %d\n",getpid());
       printf("Дочерний %d\n",t);
    }
    return 0;
}

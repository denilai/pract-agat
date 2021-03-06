#include "my.h"          //Заголовочный файл с глобальными 
                            //переменными и константами
#include "findt.c"              //Поиск строки str в файле
#include "choicet.c"            //Проверка наличия строки в файле
#include "addt.c"               //Добавление строки в файл
#include "subt.c"               //Удаление строки из файла

void main(int argc, char *argv[ ])
{
    if (argc == 3)
       if (*argv[1] == '+')        //Добавить запись
       {
           if (Choice(argv[2]) == 0)    //Нет ли такой 
                                        //записи в файле?
           {
               puts("Эта фамилия есть в справочнике");
               exit(1);
           }
           Add(argv[2]);                   //Добавление записи
       }
       else if (*argv[1] == '-') Sub(argv[2]);        //Удалить запись
            else puts("Ошибочное значение аргумента");
    else if (argc == 2) Find(argv[1]);   //Поиск записи
         else puts("Ошибочное число аргументов");
}

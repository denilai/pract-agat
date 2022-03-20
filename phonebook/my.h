//Файл заголовков my.h
//--------------------------------------------------------
//Определения глобальных переменных и символьных значений
//--------------------------------------------------------
#include <stdio.h>
#include <process.h>
#include <string.h>
#define MAX_NAME 20           //Максимальное число символов в фамилии
#define MAX_NUMBER 10         //Максимальное число цифр в телеф. номере
char Name[MAX_NAME];          //  Массив   фамилий
char Number[MAX_NUMBER];      //Массив для телефонного номера
char File[ ] = "tel_num.txt"; //Имя файла справочника 
int Count;                             //Число фамилий в справочнике
FILE *F_tel;                           //Логическое имя файла справочника
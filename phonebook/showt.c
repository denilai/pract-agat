//Программа showt.c 
//-------------------------------------------------
//Выводит на экран все записи из файла tel_num.txt 
//-------------------------------------------------
#include "my.h" 
void Show(void) 
{ 
    int i; 
//Если файл невозможно открыть для чтения, то завершение работы программы 
    if ((F_tel = fopen(File, "r")) == NULL) 
    {
        fprintf(stderr, "\"%s\" : невозможно открыть\n",File);
        exit(1);
    }
//Чтение числа записей (Count) в файле
    if(fread(&Count, sizeof(int), 1, F_tel) != 1)  
    {
        fprintf(stderr, "\"%s\" : ошибка чтения\n", File);
        exit(1);
    }
//В цикле осуществляется вывод всех записей 
    for (i=0; i < Count; i++) 
    {
        fread(Name, 1, MAX_NAME, F_tel);        //Читается имя
        fread(Number, 1, MAX_NUMBER, F_tel);    //Читается номер
        if (ferror(F_tel))         //Проверяется отсутствие ошибки 
        {
            fprintf(stderr, "\"%s\" : ошибка чтения\n'', File);
            exit(1);
        }
        printf("Фамилия:  %s; номер телефона:  %s\n", Name, Number);
    }
    fclose(F_tel);
}
void main(void)
{
    Show( );
}

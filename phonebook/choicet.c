// Модуль choicet.c
//----------------------------------------------------------------------
//Функция Choice( ), проверяющая есть ли строка str в файле tel_num.txt
//----------------------------------------------------------------------
int Choice(char *str) 
{
    int i;
    char temp[MAX_NAME + MAX_NUMBER];

    if ((F_tel = fopen(File, "r")) == NULL) 
    return 1;                                //Строки str нет в файле
    if (fread(&Count, sizeof(int), 1, F_tel) != 1)
    {
        fprintf(stderr, "\"%s\" : ошибка чтения\n", File);
        exit(1);
    }
    for (i = 0; i < Count; i++)
    {
        fread(temp, 1, MAX_NAME + MAX_NUMBER, F_tel);
        if (ferror(F_tel))
        {
            fprintf(stderr, "\"%s\" : ошибка чтения\n", File);
            exit(1);
        }
        if (strcmp(str, temp) == 0)
        {
            fclose(F_tel);
            return 0;                //Строка str есть в файле
        }
    }
    fclose(F_tel);
    return 1;                        //Строки str нет в файле
}

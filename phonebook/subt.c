//Модуль subt.c
//------------------------------------------------------------
//Функция Sub( ) удаляет заданную строку из файла tel_num.txt 
//------------------------------------------------------------
void Sub(char *str)
{
    int i, j;
    char temp[MAX_NAME + MAX_NUMBER];      //Временный массив

    if ((F_tel = fopen(File, "r+")) == NULL)
    {
        fprintf(stderr, "\"%s\" : невозможно открыть\n", File);
        exit(1);
    }
    if (fread(&Count, sizeof(int), 1, F_tel) != 1)
    {
        fprintf(stderr, "\"%s\" : ошибка чтения\n", File);
        exit(1);
    }
//В цикле  осуществляется поиск удаляемой строки в файле
    for (i = 0; i < Count; i++)
    {
        fread(temp, 1, MAX_NAME + MAX_NUMBER, F_tel);
        if (ferror(F_tel))
        {
            fprintf(stderr, "\"%s\" : ошибка чтения\n", File);
            exit(1);
        }
        if (strcmp(str, temp) == 0)         //Если срока найдена 
        {
            for (j = i; j < Count; j++)   //она удаляется
            {  
                fread(temp, 1, MAX_NAME + MAX_NUMBER, F_tel);
                fseek(F_tel, (long)(j*(MAX_NAME+MAX_NUMBER)+2L), SEEK_SET);
                fwrite(temp, 1, MAX_NAME + MAX_NUMBER, F_tel);
                fseek(F_tel, (long)((j+2)*(MAX_NAME+MAX_NUMBER)+2L), SEEK_SET);
                if (ferror(F_tel))
                {
                    fprintf(stderr, "\"%s\" : ошибка чтения\n", File);
                    exit(1);
                }
            }
            --Count;         //При удалении строки   декремент   Count
            fseek(F_tel, 0L, SEEK_SET);        //Установка указателя
//Запись уменьшенного значения Count в файл
            if (fwrite(&Count, sizeof(Count), 1, F_tel) != 1)
            {
                fprintf(stderr, "\"%s\" : ошибка записи\n", File);
                exit(1);
            }
            fclose(F_tel);
            puts("Запись удалена из файла");
            return;
        }
    }
    fprintf(stderr, "\"%s\" : отсутствует в базе данных\n", File);
    fclose(F_tel);
}

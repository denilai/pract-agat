//Модуль addt.c 
//-------------------------------------------------------
//Функция Add( ) добавляет строку str в файл tel_num.txt 
//-------------------------------------------------------
void Create(void)             //Создает файл, если он не существует
{
    if ((F_tel = fopen(File, "wb+")) == NULL)
    {
        fprintf(stderr, "\%s\" : невозможно открыть\n", File);
        exit(1);
    }
    Count = 0;
    if ( ! fwrite(&Count, sizeof(Count), 1, F_tel))
    {
        fprintf(stderr, "\"%s\" : ошибка записи\n", File);
        exit(1);
    }
}
void Add(char *s)             //Добавляет запись в файл
{
    char str[MAX_NAME], sn[MAX_NUMBER];      //Временные массивы
    int i;

    for (i = 0; i < MAX_NAME; i++)    
    str[i] = ' ';                            //Пробелы в str
    strcpy(str, s);                  //Копирование строки в str
    if ((F_tel = fopen(File, "rb+")) = = NULL) 
    Create();                        //Создаем файл, если он не 
                                     //существует
    else if (fread(&Count, sizeof(Count), 1, F_tel) != 1)
         {
             fprintf(stderr, "\"%s\" : ошибка чтения\n", File);
             exit(1);
         }
         printf("Номер телефона :   "); //Запрашивается и вводится номер
         if (gets(Number) == NULL || *Number ==  '\0')
         {
             fclose(F_tel);
             return;            //Возврат, если номер не введен
         }
//Установка указателя в файле на первую свободную запись
         if (fseek(F_tel, (long)((MAX_NAME+MAX_NUMBER)*Count), SEEK_CUR)!=0)
         {
             fprintf(stderr, "\"%s\" : ошибка поиска\n", File);
             exit(1);
         }
         fwrite(str, 1, MAX_NAME, F_tel);     //Запись в файл фамилии
         for (i = 0; i < MAX_NUMBER; i++) 
         sn[i] = ' ';                         //Пробелы в sn[ ]
         strcpy(sn, Number);     //Копирование сроки Number в строку sn
         fwrite(sn, 1, MAX_NUMBER, F_tel);    //Запись в файл номера
         if (ferror(F_tel))                   //Проверка наличия ошибки
         {
             fprintf(stderr, "\"%s\" : ошибка записи\n", File);
             exit(1);
         }
//Установка указателя в файле на первый   байт  
         if (fseek(F_tel, 0L, SEEK_SET) != 0)
         {
             fprintf(stderr, "\"%s\" : ошибка позиционирования\n", File);
             exit(1);
         }
         ++Count;               //Увеличение числа записей на единицу
//Запись Count в файл
         if (fwrite(&Count, sizeof(int), 1,F_tel) != 1)  
         {
             fprintf(stderr, "\"%s\" : ошибка записи\n", File);
             exit(1);
         }
         fclose(F_tel);
         return;
}


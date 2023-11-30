#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

inline int Open_fail(FILE* fp, char nm[], char strok[], size_t lengh, char vid[]) {
    errno_t err;
    name_potok(&nm);
    tape_potok(&vid);

    system("clr");
    err = fopen_s(&fp, nm, vid);
    if (err == NULL)
    {
        printf_s("Не удалось открыть файл");
        getchar();
        return 0;

    }
    else
    {
        printf_s("1)Чтение символа из файла\n2)Запись в файл \n3)Запись строки \n");
        int i;
        printf_s("Введите номер операции");
        scanf_s("%d", &i);
        switch (i)
        {
        case 1:
            system("clr");
            //чтение символа из файла
            fgetc(fp);
            break;
        case 2:
            system("clr");
            strung(&strok, &lengh);
            fputc(strok, fp);
            break;
        case 3:
            system("clr");
            //запись строки
            strung(&strok, &lengh);
            fgetc(&strok, lengh, fp);
            break;
        case 4:
            system("clr");
            strung(&strok, &lengh);
            fputs(&strok, lengh, fp);
            break;
        default:
            break;
        }
        fclose(fp);
        getchar();
        return 0;
    }

}
inline  int strung(char* strok[], size_t* lengh) {
    printf_s("Введите строку:  ");
    scanf_s("%9s", &strok);

    lengh = strlen(strok);

}
inline  int name_potok(char* nm[]) {
    printf_s("Назовите поток: ");
    scanf_s("%9s", &nm);

}
inline int tape_potok(char* vid[]) {
    printf_s("Введите вид потока: ");
    scanf_s("%9s", &vid);

}
inline  int  strung_delet(char* strok[]) {
    strok = NULL;
}
inline int  name_potok_delet(char* nm[]) {
    nm = NULL;
}
inline int  tape_potok_delet(char* vid[]) {
    vid = NULL;
}
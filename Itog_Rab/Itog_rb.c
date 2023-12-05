#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <string.h>


 int Open_fail(FILE* fp, char nm[], char strok[], size_t lengh, char vid[]) {
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
  int strung(char* strok[], size_t* lengh) {
    printf_s("Введите строку:  ");
    scanf_s("%9s", &strok);

    lengh = strlen(strok);

}
  int name_potok(char* nm[]) {
    printf_s("Назовите поток: ");
    scanf_s("%9s", &nm);

}
 int tape_potok(char* vid[]) {
    printf_s("Введите вид потока: ");
    scanf_s("%9s", &vid);

}
  int  strung_delet(char* strok[]) {
    strok = NULL;
}
 int  name_potok_delet(char* nm[]) {
    nm = NULL;
}
 int  tape_potok_delet(char* vid[]) {
    vid = NULL;
}
int menui() {
    printf_s("\nМеню:\n1. Считать состояние потока задач\n2. Провести эксперимент по эффективности\n3. Смоделировать процесс работы планировщика потоков\n4. Выход\n");
    printf_s("Ваш выбор:");


}
int menui_pod1() {
    printf_s("\na. сгенерировать рандомно (количество потоков задаёт пользователь)\nb. прочитать из файла\nc. назад\n");
    printf_s("Ваш выбор:");


}
int menui_pod2() {
    printf_s("\na. всех сортировок\nb. выбранной сортировки\nc. назад\n");
    printf_s("Ваш выбор:");


}

int main(void) {
    setlocale(LC_ALL, "ru");
    FILE* file = NULL;

    size_t length = 0;
    char* name;
    name = (char*)malloc(10);
    char* strok;
    strok = (char*)malloc(10);
    char* vide;
    vide = (char*)malloc(10);
    Open_fail(&file, name, strok, length, vide);
    return 0;
}
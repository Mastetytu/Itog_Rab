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
        printf_s("�� ������� ������� ����");
        getchar();
        return 0;

    }
    else
    {
        printf_s("1)������ ������� �� �����\n2)������ � ���� \n3)������ ������ \n");
        int i;
        printf_s("������� ����� ��������");
        scanf_s("%d", &i);
        switch (i)
        {
        case 1:
            system("clr");
            //������ ������� �� �����
            fgetc(fp);
            break;
        case 2:
            system("clr");
            strung(&strok, &lengh);
            fputc(strok, fp);
            break;
        case 3:
            system("clr");
            //������ ������
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
    printf_s("������� ������:  ");
    scanf_s("%9s", &strok);

    lengh = strlen(strok);

}
  int name_potok(char* nm[]) {
    printf_s("�������� �����: ");
    scanf_s("%9s", &nm);

}
 int tape_potok(char* vid[]) {
    printf_s("������� ��� ������: ");
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
    printf_s("\n����:\n1. ������� ��������� ������ �����\n2. �������� ����������� �� �������������\n3. ������������� ������� ������ ������������ �������\n4. �����\n");
    printf_s("��� �����:");


}
int menui_pod1() {
    printf_s("\na. ������������� �������� (���������� ������� ����� ������������)\nb. ��������� �� �����\nc. �����\n");
    printf_s("��� �����:");


}
int menui_pod2() {
    printf_s("\na. ���� ����������\nb. ��������� ����������\nc. �����\n");
    printf_s("��� �����:");


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
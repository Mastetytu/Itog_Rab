#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <string.h>
#include "Class.c"


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
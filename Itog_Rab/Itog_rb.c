#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
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

int main(void ) {
	setlocale(LC_ALL, "ru");

  
    return 0;
}


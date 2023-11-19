#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "Class.c"


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

int main(void ) {
	setlocale(LC_ALL, "ru");

  
    return 0;
}


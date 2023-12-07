#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "sys/stat.h"
#include <omp.h>

int menu(int * point)
{
	int _turn;
	int turn;
		printf("МЕНЮ:\n");
		printf("  1. Считать стостояние потока задач:\n");
		printf("     Подменю:\n");
		printf("       1. Сгенерировать рандомно (количество потоков задает пользователь)\n");
		printf("       2. Прочитать из файла\n");
		printf("       3. Назад\n");
		printf("  2. Провести эксперемент по эффективности:\n");
		printf("     Подменю:\n");
		printf("       1. Всех сортировок\n");
		printf("       2. Выбранной сортировки\n");
		printf("       3. Назад\n");
		printf("  3. Смоделировать процесс работы потоков\n");
		printf("  4. Выход\n");
		printf("Ваш выбор:");
		scanf_s("%d", &turn);
		while (turn < 1 || turn > 4)
		{
			printf("Некорректный ввод, попробуйте еще раз:");
			scanf_s("%d", &turn);
		}
		point[0] = turn;
		if (turn == 1 || turn == 2)
		{
			scanf_s("%d", &_turn);
			while (turn < 1 || turn > 3)
			{
				printf("Некорректный ввод, попробуйте еще раз:");
				scanf_s("%d", &_turn);
			}
			point[1] = _turn;
		}
		return turn;
}


int start_menu()
{
	int turn;

	printf("Перед началом работы задайте время CPU\n");
	printf("     Подменю:\n");
	printf("       1. Сгенерировать рандомно\n");
	printf("       2. Прочитать из файла\n");
	printf("Ваш выбор: ");
	scanf_s("%d", &turn);
	while (turn < 1 || turn > 2)
	{
		printf("Некорректный ввод, попробуйте еще раз:");
		scanf_s("%d", &turn);
	}
	return turn;
}

int fird_punct()
{
	int turn;
	system("cls");
	printf("1. Сортировка пузырьком.\n2. Сортировка подсчетом.\n3. Сортировка слиянием.\n4. Сортировка Шелла.\n Выберите сортировку: ");
	scanf_s("%d", &turn);
	while (turn < 1 || turn > 4)
	{
		printf("Некорректный ввод, попробуйте еще раз:");
		scanf_s("%d", &turn);
	}
	return turn;
}
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
		printf("����:\n");
		printf("  1. ������� ���������� ������ �����:\n");
		printf("     �������:\n");
		printf("       1. ������������� �������� (���������� ������� ������ ������������)\n");
		printf("       2. ��������� �� �����\n");
		printf("       3. �����\n");
		printf("  2. �������� ����������� �� �������������:\n");
		printf("     �������:\n");
		printf("       1. ���� ����������\n");
		printf("       2. ��������� ����������\n");
		printf("       3. �����\n");
		printf("  3. ������������� ������� ������ �������\n");
		printf("  4. �����\n");
		printf("��� �����:");
		scanf_s("%d", &turn);
		while (turn < 1 || turn > 4)
		{
			printf("������������ ����, ���������� ��� ���:");
			scanf_s("%d", &turn);
		}
		point[0] = turn;
		if (turn == 1 || turn == 2)
		{
			scanf_s("%d", &_turn);
			while (turn < 1 || turn > 3)
			{
				printf("������������ ����, ���������� ��� ���:");
				scanf_s("%d", &_turn);
			}
			point[1] = _turn;
		}
		return turn;
}


int start_menu()
{
	int turn;

	printf("����� ������� ������ ������� ����� CPU\n");
	printf("     �������:\n");
	printf("       1. ������������� ��������\n");
	printf("       2. ��������� �� �����\n");
	printf("��� �����: ");
	scanf_s("%d", &turn);
	while (turn < 1 || turn > 2)
	{
		printf("������������ ����, ���������� ��� ���:");
		scanf_s("%d", &turn);
	}
	return turn;
}

int fird_punct()
{
	int turn;
	system("cls");
	printf("1. ���������� ���������.\n2. ���������� ���������.\n3. ���������� ��������.\n4. ���������� �����.\n �������� ����������: ");
	scanf_s("%d", &turn);
	while (turn < 1 || turn > 4)
	{
		printf("������������ ����, ���������� ��� ���:");
		scanf_s("%d", &turn);
	}
	return turn;
}
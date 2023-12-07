#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <omp.h>
#include <time.h>
#include <malloc.h>

#define MAX_FILENAME_LENGTH 100
#define MAX_VALUE 100


int menu(int* point)
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
void quickSort(int* numbers, int left, int right)
{
	int pivot;
	int l_hold = left;
	int r_hold = right;
	pivot = numbers[left];
	while (left < right)
	{
		while ((numbers[right] >= pivot) && (left < right))
			right--;
		if (left != right)
		{
			numbers[left] = numbers[right];
			left++;
		}
		while ((numbers[left] <= pivot) && (left < right))
			left++;
		if (left != right)
		{
			numbers[right] = numbers[left];
			right--;
		}
	}
	numbers[left] = pivot;
	pivot = left;
	left = l_hold;
	right = r_hold;
	if (left < pivot)
		quickSort(numbers, left, pivot - 1);
	if (right > pivot)
		quickSort(numbers, pivot + 1, right);
}
void shellSort(int* num, int size)
{
	int increment = 3;
	while (increment > 0)
	{
		for (int i = 0; i < size; i++)
		{
			int j = i;
			int temp = num[i];


			while ((j >= increment) && (num[j - increment] > temp))
			{
				num[j] = num[j - increment];
				j = j - increment;
			}
			num[j] = temp;
		}
		if (increment > 1)
			increment = increment / 2;
		else if (increment == 1)
			break;
	}
}
void shekerSort(double* mass, int count)
{
	int left = 0, right = count - 1;
	int flag = 1;


	while ((left < right) && flag > 0)
	{
		flag = 0;
		for (int i = left; i < right; i++)
		{
			if (mass[i] > mass[i + 1])
			{
				double t = mass[i];
				mass[i] = mass[i + 1];
				mass[i + 1] = t;
				flag = 1;
			}
		}
		right--;
		for (int i = right; i > left; i--)
		{
			if (mass[i - 1] > mass[i])
			{
				double t = mass[i];
				mass[i] = mass[i - 1];
				mass[i - 1] = t;
				flag = 1;
			}
		}
		left++;
	}
}
int main()
{
	// ������������� ���� ���������� � �������� ����� ��������
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));
	int* mass_CPU = 0;
	int* mass = 0;
	int* mass_for_fird;
	int* buble_mass;
	int* counting_mass;
	int* merge_mass;
	int* shell_mass;
	int running;
	double _running;
	int count;
	int CPU_count;
	int CPU_summ = 0;
	int summ = 0;
	int ost_time;
	int point[2] = { 0, 0 };
	int param_buble[2] = { 0, 0 };
	int param_counting[2] = { 0, 0 };
	int param_merge[2] = { 0, 0 };
	int param_shell[2] = { 0, 0 };

	//������ ���������� ���� �� menu.c
	running = start_menu();
	switch (running)
	{
	case 1:
		printf("������� ���������� ������� : ");
		scanf_s("%d", &CPU_count); // �������� ���������� ������� CPU
		mass_CPU = (int*)malloc(CPU_count * sizeof(int)); // �� ������ ���������� ��������� ������������ ������.
		for (int i = 0; i < CPU_count; i++)
		{
			mass_CPU[i] = 1 + rand() % 1001; // ������ ����������� ���������� ����������.
		}
		break;
	case 2:
		printf("������� ���������� �����: ");
		scanf_s("%d", &CPU_count); // �������� ���������� ������� CPU

		mass_CPU = (int*)malloc(CPU_count * sizeof(int)); // �� ������ ���������� ��������� ������������ ������.

		printf("������� ������ � ports.txt (\\Itog_Rab\\Itog_Rab), ����� ���� ������������� ���������\n");
		system("pause");

		
		char adr[100] = "\\Itog_Rab\\Itog_Rab"; // ���� � ����� �� ������� ����� ����� ������ 
		char CPU_file[100] = "Max.txt"; // �������� ����� �� ������� ����� ����� ������ 
		char CPU_way[200];

		FILE* input_file_CPU = NULL;
		errno_t error1;
		errno_t error2;

		strcpy_s(CPU_way, sizeof CPU_way, adr); // ���������� � ���� ������� ���� � ����� �������� ����� � �������� ������ ������ �����
		strncat_s(CPU_way, 100, CPU_file, 100);
		error1 = fopen_s(&input_file_CPU, CPU_way, "r+"); // ��������� ����

		if (input_file_CPU == 0)
		{
			printf("�� ������� ������� ����.");
			break;
		}

		for (int i = 0; i < CPU_count; i++) {
			fscanf_s(input_file_CPU, "%d", &mass_CPU[i]); // ���������� ������ �� ����� � ������
		}

		fclose(input_file_CPU); // ��������� ����
		printf("������ ������� ������!\n������� ����� ������� ��� �� ����������.");
		system("pause");
		break;
	default:
		break;
	}
	for (int i = 0; i < CPU_count; i++)
	{
		CPU_summ += mass_CPU[i];
	}
	while (1)
	{
		system("cls");
		running = menu(point); // ��������� ������� ����, ��������� � ���� ������ ����� �� ���� ��������� � ������� ����� ��������� ����� ������������
		switch (point[0])
		{
		case 1:
			switch (point[1])
			{
			case 1:
				printf("������� ���������� �������: "); // �������� ���������� ������� 
				scanf_s("%d", &count);
				mass = (int*)malloc(count * sizeof(int)); // �� ������ ���������� ������� �������� ������������ ������
				for (int i = 0; i < count; i++)
				{
					mass[i] = 1 + rand() % 255; // ������ ����������� ���������� ����������
				}
				for (int i = 0; i < CPU_count; i++)
				{
					summ += mass[i];
				}
				system("cls");
				printf("������ ������� ������!\n������� ����� ������� ��� �� ����������.");
				system("pause");
				break;
			case 2:
				printf("������� ���������� �����: "); // �������� ���������� �������
				scanf_s("%d", &count);

				mass = (int*)malloc(count * sizeof(int)); // �� ������ ����� ��������� ������������ ������

				printf("������� ������ � ports.txt (\\Itog_Rab\\Itog_Rab), ����� ���� ������������� ���������\n");
				system("pause");

				

				char adr[100] = "\\Itog_Rab\\Itog_Rab"; // ���� � ����� � ��������
				char Flow_file[100] = "ports.txt"; // �������� ����� � ��������
				char Flow_way[200]; // ���������� � ������� ����� ����������� ������ ������ �����

				FILE* input_file_Flow = NULL;
				errno_t error1;
				errno_t error2;

				strcpy_s(Flow_way, sizeof Flow_way, adr); // ���������� � ���� ������� ���� � ����� �������� ����� � �������� ������ ������ �����
				strncat_s(Flow_way, 100, Flow_file, 100);
				error1 = fopen_s(&input_file_Flow, Flow_way, "r+"); // ��������� ����

				if (input_file_Flow == 0)
				{
					printf("�� ������� ������� ����.");
					break;
				}

				for (int i = 0; i < count; i++) {
					fscanf_s(input_file_Flow, "%d", &mass[i]); // ��������� ������ �� ����� � ������
				}

				fclose(input_file_Flow); // ��������� ����
				for (int i = 0; i < CPU_count; i++)
				{
					summ += mass[i];
				}
				printf("������ ������� ������!\n������� ����� ������� ��� �� ����������.");
				system("pause");
				break;
			case 3:
				break;
			default:
				break;
			}
			break;
		case 2:
			switch (point[1])
			{
			case 1:
				if (mass == 0)
				{
					printf("���������� ��������� �������� ��� ��� �� �� ��������� ������� � �������� � ����������� �������.");
					system("pause");
					break;
				}
				else if (mass_CPU == 0)
				{
					printf("���������� ��������� �������� ��� ��� �� �� ��������� ������ � �������� � ����������� CPU.");
					system("pause");
					break;
				}
				buble_mass = (int*)malloc(count * sizeof(int));
				counting_mass = (int*)malloc(count * sizeof(int));   // ������� 4 ������� ��� ����������� ������ 4-� ����������
				merge_mass = (int*)malloc(count * sizeof(int));
				shell_mass = (int*)malloc(count * sizeof(int));
				for (int i = 0; i < count; i++)
				{
					buble_mass[i] = mass[i];
					counting_mass[i] = mass[i];  // ��������� ������ �� ��������
					merge_mass[i] = mass[i];
					shell_mass[i] = mass[i];
				}
				int runningBuble = 0;
				int runningCounting = 0;
				int runningMerge = 0;
				int runningShell = 0;
				double _runningBuble = 0;       // ���������� ��� ���������� ����������� ������
				double _runningCounting = 0;
				double _runningMerge = 0;
				double _runningShell = 0;
				_runningBuble = bubbleSort(buble_mass, count, param_buble);
				runningBuble = checkSort(buble_mass, count);
				_runningCounting = countingSort(counting_mass, count, param_counting);
				runningCounting = checkSort(counting_mass, count);
				double startTimeMerge = omp_get_wtime();
				_running = mergeSort(merge_mass, 0, count - 1, param_merge);    // ��������� ���������� � ��������
				double finishTimeMerge = omp_get_wtime();
				_runningMerge = finishTimeMerge - startTimeMerge;
				runningMerge = checkSort(merge_mass, count);
				_runningShell = shellSort(shell_mass, count, param_shell);
				runningShell = checkSort(shell_mass, count);
				printf("|______________________________________________|\n");
				printf("|����������|   �����   |  ���-��    |  ���-��  |\n");//10|10|12|10
				printf("|          |   ������  |������������|��������� |\n");
				if (runningBuble == -1) { // ������ ���� ���������� ���������� ��������� � �����������
					printf("|______________________________________________|\n");
					printf("|   buble  |%-2.9f|%4s%-8d|%2s%-8d|\n", _runningBuble, "", param_buble[0], "", param_buble[1]);
				}
				else {
					printf("������ �� ��������: %d\n", running);
				}
				if (runningCounting == -1) {
					printf("|______________________________________________|\n");
					printf("|��������� |%-2.9f|%4s%-8d|%2s%-8d|\n", _runningCounting, "", param_counting[0], "", param_counting[1]);
				}
				else {
					printf("������ �� ��������: %d\n", running);
				}
				if (runningMerge == -1) {
					printf("|______________________________________________|\n");
					printf("| �������� |%-2.9f|%4s%-8d|%2s%-8d|\n", _runningMerge, "", param_merge[0], "", param_merge[1]);

				}
				else {
					printf("������ �� ��������: %d\n", running);
				}
				if (runningShell == -1) {
					printf("|______________________________________________|\n");
					printf("|   �����  |%-2.9f|%4s%-8d|%2s%-8d|\n", _runningShell, "", param_shell[0], "", param_shell[1]);
					printf("|______________________________________________|\n");
				}
				else {
					printf("������ �� ��������: %d\n", running);
				}
				system("pause");
				break;
			case 2:
				system("cls");
				printf("�������� ����������: \n1. ���������� ���������\n2. ���������� ���������\n3. ���������� ��������\n4. ���������� �����\n ��� �����: ");
				int turn = 0;
				scanf_s("%d", &turn);
				switch (turn)
				{
				case 1:
					_running = bubbleSort(mass, count, param_buble); // ��������� ���������� 
					running = checkSort(mass, count);  // ��������� �������� ����������
					if (running == -1) {  // ����� 
						printf("��������� ���������� buble (�������� �������������): ������������ = %d, ��������� = %d, ����� ������ ������ = %15.10lf ��\n", param_buble[0], param_buble[1], _running);
					}
					else {
						printf("������ �� ��������: %d\n", running);
					}
					system("pause");
					break;
				case 2:
					_running = countingSort(mass, count, param_counting);  // ��������� ����������
					running = checkSort(mass, count); //  ��������� �������� ����������
					if (running == -1) {  // �����
						printf("��������� ���������� ��������� (�������� �������������): ������������ = %d, ��������� = %d, ����� ������ ������ = %15.10lf ��\n", param_counting[0], param_counting[1], _running);
					}
					else {
						printf("������ �� ��������: %d\n", running);
					}
					system("pause");
					break;
				case 3:
					printf("\n");
					double startTime;
					double finishTime; // ���������� ��� ������� �������
					double resTime;
					startTime = omp_get_wtime(); // �������� ������� �������
					_running = mergeSort(mass, 0, count - 1, param_merge); // ��������� ����������
					finishTime = omp_get_wtime();  // ����������� ������� �������
					resTime = finishTime - startTime; // ������� ������� ������� ���� ���������
					running = checkSort(mass, count);  // ��������� �������� ����������
					if (running == -1) { // �����
						printf("��������� ���������� �������� (�������� �������������): ������������ = %d, ��������� = %d, ����� ������ ������ = %15.10lf ��\n", param_merge[0], param_merge[1], resTime);
					}
					else {
						printf("������ �� ��������: %d\n", running);
					}
					system("pause");
					break;
				case 4:
					_running = shellSort(mass, count, param_shell); // ��������� ����������
					running = checkSort(mass, count);  // ��������� ��������
					if (running == -1) {  // �����
						printf("��������� ���������� ����� (�������� �������������): ������������ = %d, ��������� = %d, ����� ������ ������ = %15.10lf ��\n", param_shell[0], param_shell[1], _running);
					}
					else {
						printf("������ �� ��������: %d\n", running);
					}
					system("pause");
					break;
				default:
					break;
				}
				break;
			case 3:
				break;
			default:
				break;
			}
			break;
		case 3:
			running = fird_punct(); // ��������� ���� �� menu.c
			switch (running)
			{
			case 1:
				if (count < 20) // ��������� ��� ������� ������ 20
				{
					mass_for_fird = (int*)malloc(count * sizeof(int)); // ������� ������ ������� ����� �����������
					for (int i = 0; i < count; i++)
					{
						mass_for_fird[i] = mass[i]; // ���������� � ���� ��������
					}
					_running = bubbleSort(mass_for_fird, count, param_buble); // ��������� �������� ��������� ������
					system("cls");
					printf("|_________________________________________________________________|\n");
					printf("|  �����   |  �����   |��������� |  �����   |  �����   |����������|\n");
					printf("| �������� |������� ��|��������� |����������|����������| ����� �� |\n");  // ����� ��������� ��������
					printf("|          |          |����� ��  |  ������  |  ������  |          |\n");
					for (int i = 0; i < CPU_count; i++)
					{
						int dynamictime = mass_CPU[i]; // ���������� ����� CPU ��� ������ ��������
						while (dynamictime > 0)
						{
							int _count = 0;
							int _num;
							int _dynamictime = dynamictime;

							running = binarySearch(mass_for_fird, count, dynamictime); // ���� ����������� ������������ �� ������� CPU �������� � ������� ��������� ������
							if (running == -1)
							{
								break;
							}
							_num = mass_for_fird[running]; // ���������� ��� �������� � ����������
							for (int i = running; i > 0; i--) // ��� �� ��� ����� ������ �� ���������� �� ����������� ��� � 0 � ���������� � ������ �������
							{
								mass_for_fird[i] = mass_for_fird[i - 1];
							}
							mass_for_fird[_count] = 0;
							_count++;
							for (int i = 0; i < count; i++) // ���� ���� ����� � ����������������� ������� � ���������� ��� �����
							{
								if (mass[i] == _num)
								{
									running = i;
								}
							}
							dynamictime = dynamictime - _num; // ������� ���������� �����
							printf("|_________________________________________________________________|\n");
							printf("|%2s%-8d|%2s%-8d|%2s%-8d|%2s%-8d|%2s%-8d|%2s%-8d|\n", "", i, "", mass_CPU[i], "", _dynamictime, "", running + 1, "", _num, "", dynamictime); // ������ ������ �������
						}
					}
					printf("|_________________________________________________________________|\n");
					ost_time = CPU_summ - summ;
					if (ost_time < 0)
					{
						printf("��� ���������� ���� ������� �� �������: %d ������\n", ost_time);
					}
					else if (ost_time > 0)
					{
						printf("�������� �����: %d\n", ost_time);
					}
					system("pause");
				}
				else
				{
					FILE* file;
					fopen_s(&file, "ans_buble.txt", "w"); // ��������� ���� ans_buble.txt ��� ������ ��� ���� ������ ����� ��� ������� ���
					if (file == NULL) {
						printf("�� ������� ������� ����.");
						return 1;
					}
					mass_for_fird = (int*)malloc(count * sizeof(int)); // ������� ��������� ������ ��� ����������
					for (int i = 0; i < count; i++)
					{
						mass_for_fird[i] = mass[i]; // ���������� � ���� ��������
					}
					_running = bubbleSort(mass_for_fird, count, param_buble); // ��������� ������
					fprintf(file, "|_________________________________________________________________|\n");
					fprintf(file, "|  �����   |  �����   |��������� |  �����   |  �����   |����������|\n");
					fprintf(file, "| �������� |������� ��|��������� |����������|����������| ����� �� |\n"); // ������ ����� �������
					fprintf(file, "|          |          |����� ��  |  ������  |  ������  |          |\n");
					for (int i = 0; i < CPU_count; i++)
					{
						int dynamictime = mass_CPU[i]; // ���������� ����� CPU ��� ������ ��������
						while (dynamictime > 0)
						{

							int _count = 0;
							int _num;
							int _dynamictime = dynamictime;

							running = binarySearch(mass_for_fird, count, dynamictime); // ���� ����������� ������������ �� ������� CPU �������� � ������� ��������� ������
							if (running == -1)
							{
								break;
							}
							_num = mass_for_fird[running]; // ���������� ��� �������� � ����������
							for (int i = running; i > 0; i--) // ��� �� ��� ����� ������ �� ���������� �� ����������� ��� � 0 � ���������� � ������ �������
							{
								mass_for_fird[i] = mass_for_fird[i - 1];
							}
							mass_for_fird[_count] = 0;
							_count++;
							for (int i = 0; i < count; i++) // ���� ���� ����� � ����������������� ������� � ���������� ��� �����
							{
								if (mass[i] == _num)
								{
									running = i;
								}
							}
							dynamictime = dynamictime - _num; // ������� ���������� �����
							fprintf(file, "|_________________________________________________________________|\n");
							fprintf(file, "|%2s%-8d|%2s%-8d|%2s%-8d|%2s%-8d|%2s%-8d|%2s%-8d|\n", "", i, "", mass_CPU[i], "", _dynamictime, "", running + 1, "", _num, "", dynamictime); // ������ ������ �������
						}
					}
					fprintf(file, "|_________________________________________________________________|\n");
					ost_time = CPU_summ - summ;
					if (ost_time < 0)
					{
						fprintf(file, "��� ���������� ���� ������� �� �������: %d ������\n", ost_time);
					}
					else if (ost_time > 0)
					{
						fprintf(file, "�������� �����: %d\n", ost_time);
					}
					printf("���� ������� ������!\n������� ����� ������� ��� �� ����������.");
					fclose(file);
					system("pause");
				}
				break;
				// ������ ��� ������ ���� ��� ��� ���������� ���������� BUBLE.
			case 2:
				if (count < 20)
				{
					mass_for_fird = (int*)malloc(count * sizeof(int));
					for (int i = 0; i < count; i++)
					{
						mass_for_fird[i] = mass[i];
					}
					_running = countingSort(mass_for_fird, count, param_counting);
					system("cls");
					printf("|_________________________________________________________________|\n");
					printf("|  �����   |  �����   |��������� |  �����   |  �����   |����������|\n");
					printf("| �������� |������� ��|��������� |����������|����������| ����� �� |\n");
					printf("|          |          |����� ��  |  ������  |  ������  |          |\n");
					for (int i = 0; i < CPU_count; i++)
					{
						int dynamictime = mass_CPU[i];
						while (dynamictime > 0)
						{

							int _count = 0;
							int _num;
							int _dynamictime = dynamictime;

							running = binarySearch(mass_for_fird, count, dynamictime);
							if (running == -1)
							{
								break;
							}
							_num = mass_for_fird[running];
							for (int i = running; i > 0; i--)
							{
								mass_for_fird[i] = mass_for_fird[i - 1];
							}
							mass_for_fird[_count] = 0;
							_count++;
							for (int i = 0; i < count; i++)
							{
								if (mass[i] == _num)
								{
									running = i;
								}
							}
							dynamictime = dynamictime - _num;
							printf("|_________________________________________________________________|\n");
							printf("|%2s%-8d|%2s%-8d|%2s%-8d|%2s%-8d|%2s%-8d|%2s%-8d|\n", "", i, "", mass_CPU[i], "", _dynamictime, "", running + 1, "", _num, "", dynamictime);
						}
					}
					printf("|_________________________________________________________________|\n");
					ost_time = CPU_summ - summ;
					if (ost_time < 0)
					{
						printf("��� ���������� ���� ������� �� �������: %d ������\n", ost_time);
					}
					else if (ost_time > 0)
					{
						printf("�������� �����: %d\n", ost_time);
					}
					system("pause");
				}
				else
				{

					FILE* file;
					fopen_s(&file, "ans_counting.txt", "w");
					if (file == NULL) {
						printf("�� ������� ������� ����.");
						return 1;
					}

					mass_for_fird = (int*)malloc(count * sizeof(int));
					for (int i = 0; i < count; i++)
					{
						mass_for_fird[i] = mass[i];
					}
					_running = countingSort(mass_for_fird, count, param_counting);
					fprintf(file, "|_________________________________________________________________|\n");
					fprintf(file, "|  �����   |  �����   |��������� |  �����   |  �����   |����������|\n");
					fprintf(file, "| �������� |������� ��|��������� |����������|����������| ����� �� |\n");
					fprintf(file, "|          |          |����� ��  |  ������  |  ������  |          |\n");
					for (int i = 0; i < CPU_count; i++)
					{
						int dynamictime = mass_CPU[i];
						while (dynamictime > 0)
						{

							int _count = 0;
							int _num;
							int _dynamictime = dynamictime;

							running = binarySearch(mass_for_fird, count, dynamictime);
							if (running == -1)
							{
								break;
							}
							_num = mass_for_fird[running];
							for (int i = running; i > 0; i--)
							{
								mass_for_fird[i] = mass_for_fird[i - 1];
							}
							mass_for_fird[_count] = 0;
							_count++;
							for (int i = 0; i < count; i++)
							{
								if (mass[i] == _num)
								{
									running = i;
								}
							}
							dynamictime = dynamictime - _num;
							fprintf(file, "|_________________________________________________________________|\n");
							fprintf(file, "|%2s%-8d|%2s%-8d|%2s%-8d|%2s%-8d|%2s%-8d|%2s%-8d|\n", "", i, "", mass_CPU[i], "", _dynamictime, "", running + 1, "", _num, "", dynamictime);
						}
					}
					fprintf(file, "|_________________________________________________________________|\n");
					ost_time = CPU_summ - summ;
					if (ost_time < 0)
					{
						fprintf(file, "��� ���������� ���� ������� �� �������: %d ������\n", ost_time);
					}
					else if (ost_time > 0)
					{
						fprintf(file, "�������� �����: %d\n", ost_time);
					}
					printf("���� ������� ������!\n������� ����� ������� ��� �� ����������.");
					fclose(file);
					system("pause");
				}
				break;
			case 3:
				if (count < 20)
				{
					mass_for_fird = (int*)malloc(count * sizeof(int));
					for (int i = 0; i < count; i++)
					{
						mass_for_fird[i] = mass[i];
					}
					_running = mergeSort(mass_for_fird, 0, count - 1, param_merge);
					system("cls");
					printf("|_________________________________________________________________|\n");
					printf("|  �����   |  �����   |��������� |  �����   |  �����   |����������|\n");
					printf("| �������� |������� ��|��������� |����������|����������| ����� �� |\n");
					printf("|          |          |����� ��  |  ������  |  ������  |          |\n");
					for (int i = 0; i < CPU_count; i++)
					{
						int dynamictime = mass_CPU[i];
						while (dynamictime > 0)
						{

							int _count = 0;
							int _num;
							int _dynamictime = dynamictime;

							running = binarySearch(mass_for_fird, count, dynamictime);
							if (running == -1)
							{
								break;
							}
							_num = mass_for_fird[running];
							for (int i = running; i > 0; i--)
							{
								mass_for_fird[i] = mass_for_fird[i - 1];
							}
							mass_for_fird[_count] = 0;
							_count++;
							for (int i = 0; i < count; i++)
							{
								if (mass[i] == _num)
								{
									running = i;
								}
							}
							dynamictime = dynamictime - _num;
							printf("|_________________________________________________________________|\n");
							printf("|%2s%-8d|%2s%-8d|%2s%-8d|%2s%-8d|%2s%-8d|%2s%-8d|\n", "", i, "", mass_CPU[i], "", _dynamictime, "", running + 1, "", _num, "", dynamictime);
						}
					}
					printf("|_________________________________________________________________|\n"); ost_time = CPU_summ - summ;
					if (ost_time < 0)
					{
						printf("��� ���������� ���� ������� �� �������: %d ������\n", ost_time);
					}
					else if (ost_time > 0)
					{
						printf("�������� �����: %d\n", ost_time);
					}
					system("pause");
				}
				else
				{

					FILE* file;
					fopen_s(&file, "ans_merge.txt", "w");
					if (file == NULL) {
						printf("�� ������� ������� ����.");
						return 1;
					}

					if (file == NULL) {
						printf("�� ������� ������� ����.");
						return 1;
					}

					mass_for_fird = (int*)malloc(count * sizeof(int));
					for (int i = 0; i < count; i++)
					{
						mass_for_fird[i] = mass[i];
					}
					_running = mergeSort(mass_for_fird, 0, count - 1, param_merge);
					fprintf(file, "|_________________________________________________________________|\n");
					fprintf(file, "|  �����   |  �����   |��������� |  �����   |  �����   |����������|\n");
					fprintf(file, "| �������� |������� ��|��������� |����������|����������| ����� �� |\n");
					fprintf(file, "|          |          |����� ��  |  ������  |  ������  |          |\n");
					for (int i = 0; i < CPU_count; i++)
					{
						int dynamictime = mass_CPU[i];
						while (dynamictime > 0)
						{
							int _count = 0;
							int _num;
							int _dynamictime = dynamictime;

							running = binarySearch(mass_for_fird, count, dynamictime);
							if (running == -1)
							{
								break;
							}
							_num = mass_for_fird[running];
							for (int i = running; i > 0; i--)
							{
								mass_for_fird[i] = mass_for_fird[i - 1];
							}
							mass_for_fird[_count] = 0;
							_count++;
							for (int i = 0; i < count; i++)
							{
								if (mass[i] == _num)
								{
									running = i;
								}
							}
							dynamictime = dynamictime - _num;
							fprintf(file, "|_________________________________________________________________|\n");
							fprintf(file, "|%2s%-8d|%2s%-8d|%2s%-8d|%2s%-8d|%2s%-8d|%2s%-8d|\n", "", i, "", mass_CPU[i], "", _dynamictime, "", running + 1, "", _num, "", dynamictime);
						}
					}
					fprintf(file, "|_________________________________________________________________|\n");
					ost_time = CPU_summ - summ;
					if (ost_time < 0)
					{
						fprintf(file, "��� ���������� ���� ������� �� �������: %d ������\n", ost_time);
					}
					else if (ost_time > 0)
					{
						fprintf(file, "�������� �����: %d\n", ost_time);
					}
					printf("���� ������� ������!\n������� ����� ������� ��� �� ����������.");
					fclose(file);
					system("pause");
				}
				break;
			case 4:
				if (count < 20)
				{
					mass_for_fird = (int*)malloc(count * sizeof(int));
					for (int i = 0; i < count; i++)
					{
						mass_for_fird[i] = mass[i];
					}
					_running = shellSort(mass, count, param_shell);
					system("cls");
					printf("|_________________________________________________________________|\n");
					printf("|  �����   |  �����   |��������� |  �����   |  �����   |����������|\n");
					printf("| �������� |������� ��|��������� |����������|����������| ����� �� |\n");
					printf("|          |          |����� ��  |  ������  |  ������  |          |\n");
					for (int i = 0; i < CPU_count; i++)
					{
						int dynamictime = mass_CPU[i];
						while (dynamictime > 0)
						{
							int _count = 0;
							int _num;
							int _dynamictime = dynamictime;

							running = binarySearch(mass_for_fird, count, dynamictime);
							if (running == -1)
							{
								break;
							}
							_num = mass_for_fird[running];
							for (int i = running; i > 0; i--)
							{
								mass_for_fird[i] = mass_for_fird[i - 1];
							}
							mass_for_fird[_count] = 0;
							_count++;
							for (int i = 0; i < count; i++)
							{
								if (mass[i] == _num)
								{
									running = i;
								}
							}
							dynamictime = dynamictime - _num;
							printf("|_________________________________________________________________|\n");
							printf("|%2s%-8d|%2s%-8d|%2s%-8d|%2s%-8d|%2s%-8d|%2s%-8d|\n", "", i, "", mass_CPU[i], "", _dynamictime, "", running + 1, "", _num, "", dynamictime);
						}
					}
					printf("|_________________________________________________________________|\n");
					ost_time = CPU_summ - summ;
					if (ost_time < 0)
					{
						printf("��� ���������� ���� ������� �� �������: %d ������\n", ost_time);
					}
					else if (ost_time > 0)
					{
						printf("�������� �����: %d\n", ost_time);
					}
					system("pause");
				}
				else
				{

					FILE* file;
					fopen_s(&file, "ans_shell.txt", "w");
					if (file == NULL) {
						printf("�� ������� ������� ����.");
						return 1;
					}

					if (file == NULL) {
						printf("�� ������� ������� ����.");
						return 1;
					}

					mass_for_fird = (int*)malloc(count * sizeof(int));
					for (int i = 0; i < count; i++)
					{
						mass_for_fird[i] = mass[i];
					}
					_running = shellSort(mass, count, param_shell);
					fprintf(file, "|_________________________________________________________________|\n");
					fprintf(file, "|  �����   |  �����   |��������� |  �����   |  �����   |����������|\n");
					fprintf(file, "| �������� |������� ��|��������� |����������|����������| ����� �� |\n");
					fprintf(file, "|          |          |����� ��  |  ������  |  ������  |          |\n");
					for (int i = 0; i < CPU_count; i++)
					{
						int dynamictime = mass_CPU[i];
						while (dynamictime > 0)
						{
							int _count = 0;
							int _num;
							int _dynamictime = dynamictime;

							running = binarySearch(mass_for_fird, count, dynamictime);
							if (running == -1)
							{
								break;
							}
							_num = mass_for_fird[running];
							for (int i = running; i > 0; i--)
							{
								mass_for_fird[i] = mass_for_fird[i - 1];
							}
							mass_for_fird[_count] = 0;
							_count++;
							for (int i = 0; i < count; i++)
							{
								if (mass[i] == _num)
								{
									running = i;
								}
							}
							dynamictime = dynamictime - _num;
							fprintf(file, "|_________________________________________________________________|\n");
							fprintf(file, "|%2s%-8d|%2s%-8d|%2s%-8d|%2s%-8d|%2s%-8d|%2s%-8d|\n", "", i, "", mass_CPU[i], "", _dynamictime, "", running + 1, "", _num, "", dynamictime);
						}
					}
					fprintf(file, "|_________________________________________________________________|\n");
					ost_time = CPU_summ - summ;
					if (ost_time < 0)
					{
						fprintf(file, "��� ���������� ���� ������� �� �������: %d ������\n", ost_time);
					}
					else if (ost_time > 0)
					{
						fprintf(file, "�������� �����: %d\n", ost_time);
					}
					printf("���� ������� ������!\n������� ����� ������� ��� �� ����������.");
					fclose(file);
					system("pause");
				}
				break;
			default:
				break;
			}
		case 4:
			return 0;
		default:
			break;
		}
	}
}
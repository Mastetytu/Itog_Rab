#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <omp.h>
#include <time.h>
#include <malloc.h>

#define MAX_FILENAME_LENGTH 100
#define MAX_VALUE 100

int sort1(int fl,int CPU_count,int* mass_CPU,int running,int* mass_for_fird,int count,int* mass,int ost_time,int CPU_summ,int summ, FILE* file) {
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
	if (fl = 1) {
		printf_s("|_________________________________________________________________|\n");
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
	else {
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
	
}
int sort(int runningquickSort ,int runningcheckSort, int runningShell ,int _runningquickSort,int _runningcheckSort,int _runningShell, int* param_quickSort, int* param_shekerSort, int* param_shell,int running){
	printf("|______________________________________________|\n");
				printf("|����������|   �����   |  ���-��    |  ���-��  |\n");
				printf("|          |   ������  |������������|��������� |\n");
				if (runningquickSort == -1) {
					printf("|______________________________________________|\n");
					printf("|   ���������� �����  |%-2.9f|%4s%-8d|%2s%-8d|\n", _runningquickSort, "", param_quickSort[0], "", param_quickSort[1]);
				}
				else {
					printf("������ �� ��������: %d\n", running);
				}
				if (runningcheckSort == -1) {
					printf("|______________________________________________|\n");
					printf("|��������� ���������� |%-2.9f|%4s%-8d|%2s%-8d|\n", _runningcheckSort, "", param_shekerSort[0], "", param_shekerSort[1]);
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
}
int shekerSort(double* mass, int count, int* params)
{
	int left = 0, right = count - 1;
	int flag = 1;
	int startTime;
	int finishTime;
	int resTime;
	int swaps = 0;
	int cmps = 0;
	startTime = omp_get_wtime();
	while ((left < right) && flag > 0)
	{

		flag = 0;
		for (int i = left; i < right; i++)
		{
			if (mass[i] > mass[i + 1])
			{
				cmps += 1;
				double t = mass[i];
				mass[i] = mass[i + 1];
				mass[i + 1] = t;
				flag = 1;
				swaps += 1;
			}
		}
		right--;
		for (int i = right; i > left; i--)
		{
			if (mass[i - 1] > mass[i])
			{
				cmps += 1;
				double t = mass[i];
				mass[i] = mass[i - 1];
				mass[i - 1] = t;
				flag = 1;
				swaps += 1;
			}
		}
		left++;
	}
	params[0] = swaps;
	params[1] = cmps;
	finishTime = omp_get_wtime();
	resTime = finishTime - startTime;
	return resTime;
}
int binarySearch(int* mass, int size, int target)
{
	int low, high, middle;
	low = 0;
	high = size - 1;
	while (low <= high)
	{
		middle = (low + high) / 2;
		if (target < mass[middle])
			high = middle - 1;
		else if (target > mass[middle])
			low = middle + 1;
		else
		{
			if (mass[middle] == 0)
			{
				return -1;
			}
			else
			{
				return middle;
			}
		}
	}
	if (target <= 0)
	{
		return -1;
	}
	return binarySearch(mass, size, target - 1);
}
int checkSort(int arr[], int size) {
	int i;
	for (i = 1; i < size; i++) {
		if (arr[i] < arr[i - 1]) {
			return i; // ���������� ����� �������� � �������
		}
	}
	return -1; // ��� �������� ������������� �����
}
int quickSort(int* numbers, int left, int right, int* params)
{
	
	int startTime;
	int finishTime;
	int resTime;
	int swaps = 0;
	int cmps = 0;
	startTime = omp_get_wtime();
	int pivot;
	int l_hold = left;
	int r_hold = right;
	pivot = numbers[left];
	while (left < right)
	{
		while ((numbers[right] >= pivot) && (left < right))
			cmps += 1;
		right--;
		if (left != right)
		{
			numbers[left] = numbers[right];
			left++;
			swaps += 1;
		}
		while ((numbers[left] <= pivot) && (left < right))
			cmps += 1;
		left++;
		if (left != right)
		{
			numbers[right] = numbers[left];
			right--;
			swaps += 1;
		}
	}
	numbers[left] = pivot;
	pivot = left;
	left = l_hold;
	right = r_hold;
	if (left < pivot)
		quickSort(numbers, left, pivot - 1, params);
	if (right > pivot)
		quickSort(numbers, pivot + 1, right, params);
	params[0] = swaps;
	params[1] = cmps;
	finishTime = omp_get_wtime();
	resTime = finishTime - startTime;
	return resTime;
}
int shellSort(int* arr, int n, int* params) {
	int startTime;
	int finishTime;
	int resTime;
	int swaps = 0;
	int cmps = 0;
	startTime = omp_get_wtime();

	for (int gap = n / 2; gap > 0; gap /= 2) {
		for (int i = gap; i < n; i++) {
			cmps += 1;
			int temp = arr[i];
			int j;
			for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
				arr[j] = arr[j - gap];
				swaps += 1;
			}
			arr[j] = temp;
		}
	}
	params[0] = swaps;
	params[1] = cmps;
	finishTime = omp_get_wtime();
	resTime = finishTime - startTime;
	return resTime;
}


int menu(int* point)
{
	int _turn;
	int turn;
	printf_s("����:\n1. ������� ���������� ������ �����:\n     �������:\n       1. ������������� �������� (���������� ������� ������ ������������)\n       2. ��������� �� �����\n       3. �����\n2. �������� ����������� �� �������������:\n     �������:\n       1. ���� ����������\n       2. ��������� ����������\n       3. �����\n  3. ������������� ������� ������ �������\n  4. �����\n");
	printf_s("��� �����:");
	scanf_s("%d", &turn);
	while (turn < 1 || turn > 4)
	{
		printf_s("������������ ����, ���������� ��� ���:");
		scanf_s("%d", &turn);
	}
	point[0] = turn;
	if (turn == 1 || turn == 2)
	{
		scanf_s("%d", &_turn);
		while (turn < 1 || turn > 3)
		{
			printf_s("������������ ����, ���������� ��� ���:");
			scanf_s("%d", &_turn);
		}
		point[1] = _turn;
	}
	return turn;
}


int start_menu()
{
	int turn;

	printf_s("����� ������� ������ ������� ����� CPU\n     �������:\n       1. ������������� ��������\n       2. ��������� �� �����\n");
	printf_s("��� �����: ");
	scanf_s("%d", &turn);
	while (turn < 1 || turn > 2)
	{
		printf_s("������������ ����, ���������� ��� ���:");
		scanf_s("%d", &turn);
	}
	return turn;
}

int fird_punct()
{
	int turn;
	system("cls");
	printf_s("1.���������� �����.\n2.���������� �����.\n3.��������� ����������.\n �������� ����������: ");
	scanf_s("%d", &turn);
	while (turn < 1 || turn > 4)
	{
		printf_s("������������ ����, ���������� ��� ���:");
		scanf_s("%d", &turn);
	}
	return turn;
}

int main()
{
	// ������������� ���� ���������� � �������� ����� ��������
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));
	int* mass_CPU = 0;
	int* mass = 0;
	int* mass_for_fird;
	int* shekerSort_mass;
	int* quickSort_mass;
	int* shell_mass;
	int running;
	int _running;
	int count;
	int CPU_count;
	int CPU_summ = 0;
	int summ = 0;
	int ost_time=0;
	int point[2] = { 0, 0 };
	int param_quickSort[2] = { 0, 0 };
	int param_shekerSort[2] = { 0, 0 };
	int param_merge[2] = { 0, 0 };
	int param_shell[2] = { 0, 0 };
	int fl;

	running = start_menu();
	switch (running)
	{
	case 1:
		printf_s("������� ���������� ������� : ");
		scanf_s("%d", &CPU_count); // �������� ���������� ������� CPU
		mass_CPU = (int*)malloc(CPU_count * sizeof(int));
		for (int i = 0; i < CPU_count; i++)
		{
			mass_CPU[i] = 1 + rand() % 1001; // ������ ����������� ���������� ����������.
		}
		break;
	case 2:
		printf_s("������� ���������� �����: ");
		scanf_s("%d", &CPU_count);

		mass_CPU = (int*)malloc(CPU_count * sizeof(int));

		printf_s("������� ������ � Max.txt (\\Itog_Rab\\Itog_Rab), ����� ���� ������������� ���������\n");
		system("pause");


		char adr[100] = "\\Itog_Rab\\Itog_Rab";
		char CPU_file[100] = "Max.txt";
		char CPU_way[200];

		FILE* input_file_CPU = NULL;
		errno_t error1;
		errno_t error2;

		strcpy_s(CPU_way, sizeof CPU_way, adr);
		strncat_s(CPU_way, 100, CPU_file, 100);
		error1 = fopen_s(&input_file_CPU, CPU_way, "r+");

		if (input_file_CPU == 0)
		{
			printf_s("�� ������� ������� ����.");
			break;
		}

		for (int i = 0; i < CPU_count; i++) {
			fscanf_s(input_file_CPU, "%d", &mass_CPU[i]);
		}

		fclose(input_file_CPU);
		printf_s("������ ������� ������!\n������� ����� ������� ��� �� ����������.");
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
		running = menu(point);
		switch (point[0])
		{
		case 1:
			switch (point[1])
			{
			case 1:
				printf("������� ���������� �������: ");
				scanf_s("%d", &count);
				mass = (int*)malloc(count * sizeof(int));
				for (int i = 0; i < count; i++)
				{
					mass[i] = 1 + rand() % 255;
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
				printf("������� ���������� �����: ");
				scanf_s("%d", &count);

				mass = (int*)malloc(count * sizeof(int));

				printf("������� ������ � ports.txt (\\Itog_Rab\\Itog_Rab), ����� ���� ������������� ���������\n");
				system("pause");



				char adr[100] = "\\Itog_Rab\\Itog_Rab";
				char Flow_file[100] = "ports.txt";
				char Flow_way[200];

				FILE* input_file_Flow = NULL;
				errno_t error1;
				errno_t error2;

				strcpy_s(Flow_way, sizeof Flow_way, adr);
				strncat_s(Flow_way, 100, Flow_file, 100);
				error1 = fopen_s(&input_file_Flow, Flow_way, "r+");

				if (input_file_Flow == 0)
				{
					printf("�� ������� ������� ����.");
					break;
				}

				for (int i = 0; i < count; i++) {
					fscanf_s(input_file_Flow, "%d", &mass[i]);
				}

				fclose(input_file_Flow);
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

				quickSort_mass = (int*)malloc(count * sizeof(int));
				shekerSort_mass = (int*)malloc(count * sizeof(int));
				shell_mass = (int*)malloc(count * sizeof(int));
				for (int i = 0; i < count; i++)
				{
					quickSort_mass[i] = mass[i];
					shekerSort_mass[i] = mass[i];
					shell_mass[i] = mass[i];
				}
				int runningquickSort = 0;
				int runningcheckSort = 0;
				int runningShell = 0;
				int _runningquickSort = 0;
				int _runningcheckSort = 0;
				int _runningShell = 0;
				_runningquickSort = quickSort(quickSort_mass, 0, -1, param_quickSort);
				runningquickSort = checkSort(quickSort_mass, count);
				_runningcheckSort = shekerSort(shekerSort_mass, count, param_shekerSort);
				runningcheckSort = checkSort(shekerSort_mass, count);
				_runningShell = shellSort(shell_mass, count, param_shell);
				runningShell = checkSort(shell_mass, count);
				sort(runningquickSort, runningcheckSort, runningShell, _runningquickSort, _runningcheckSort, _runningShell, param_quickSort, param_shekerSort, param_shell, running);
				break;
			case 2:
				system("cls");
				printf_s("1. ���������� �����.\n2.  ���������� �����.\n3. ��������� ����������.\n �������� ����������: ");
				int turn = 0;
				scanf_s("%d", &turn);
				switch (turn)
				{
				case 1:
					_running = quickSort(mass, 0, 1, param_quickSort);
					running = checkSort(mass, count);  // ��������� �������� ����������
					if (running == -1) {
						printf("��������� ���������� ���������� ����� (�������� �������������): ������������ = %d, ��������� = %d, ����� ������ ������ = %15.10lf ��\n", param_quickSort[0], param_quickSort[1], _running);
					}
					else {
						printf("������ �� ��������: %d\n", running);
					}
					system("pause");
					break;
				case 2:
					_running = shekerSort(mass, count, param_shekerSort);
					running = checkSort(mass, count);
					if (running == -1) {
						printf("��������� ����������  ��������� ���������� (�������� �������������): ������������ = %d, ��������� = %d, ����� ������ ������ = %15.10lf ��\n", param_shekerSort[0], param_shekerSort[1], _running);
					}
					else {
						printf("������ �� ��������: %d\n", running);
					}
					system("pause");
					break;
				case 3:
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
			running = fird_punct();
			switch (running)
			{
			case 1:
				if (count < 20)
				{
					FILE* file;
					fopen_s(&file, "ans_shell.txt", "w");
					mass_for_fird = (int*)malloc(count * sizeof(int));
					for (int i = 0; i < count; i++)
					{
						mass_for_fird[i] = mass[i];
					}
					_running = quickSort(mass, 0, -1, param_quickSort); // ��������� �������� ��������� ������
					fl = 1;
					sort1(fl, CPU_count, mass_CPU, running, mass_for_fird, count, mass, ost_time, CPU_summ, summ, file);
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
					_running = quickSort(mass, 0, count - 1, param_quickSort); // ��������� ������
					fl = 1;
					sort1(fl, CPU_count, mass_CPU, running, mass_for_fird, count, mass, ost_time, CPU_summ, summ, file);
					break;

			case 2:
				if (count < 20)
				{
					FILE* file;
					fopen_s(&file, "ans_shell.txt", "w");
					mass_for_fird = (int*)malloc(count * sizeof(int));
					for (int i = 0; i < count; i++)
					{
						mass_for_fird[i] = mass[i];
					}
					_running = shekerSort(mass, count, param_shekerSort);
					fl = 1;
					sort1(fl, CPU_count, mass_CPU, running, mass_for_fird, count, mass, ost_time, CPU_summ, summ, file);
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
					_running = shekerSort(mass, count, param_shekerSort);
					fl = 1;
					sort1(fl, CPU_count, mass_CPU, running, mass_for_fird, count, mass, ost_time, CPU_summ, summ, file);
				}
				break;

			case 3:
				if (count < 20)
				{
					FILE* file;
					fopen_s(&file, "ans_shell.txt", "w");
					mass_for_fird = (int*)malloc(count * sizeof(int));
					for (int i = 0; i < count; i++)
					{
						mass_for_fird[i] = mass[i];
					}
					_running = shellSort(mass, count, param_shell);
					fl = 1;
					sort1(fl, CPU_count, mass_CPU, running, mass_for_fird, count, mass, ost_time, CPU_summ, summ, file);
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
					fl = 1;
					sort1(fl, CPU_count, mass_CPU, running, mass_for_fird, count, mass, ost_time, CPU_summ, summ, file);
				}
				break;
			default:
				break;
				}
			case 4:
				return 0;
			
			}
		case 4:
			return 0;
		}
		
	}
}
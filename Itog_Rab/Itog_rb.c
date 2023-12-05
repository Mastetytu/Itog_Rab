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


double bubbleSort(int arr[], int size, int* params)
{
    double startTime;
    double finishTime;
    double resTime;
    int swaps = 0;
    int cmps = 0;
    startTime = omp_get_wtime();
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                cmps += 1;
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swaps += 1;
            }
        }
    }
    params[0] = swaps;
    params[1] = cmps;
    finishTime = omp_get_wtime();
    resTime = finishTime - startTime;
    return resTime;
}

double countingSort(int arr[], int size, int* params) {

    double startTime;
    double finishTime;
    double resTime;
    int swaps = 0;
    int cmps = 0;
    int* sorted_arr;

    startTime = omp_get_wtime();

    sorted_arr = (int*)malloc(size * sizeof(int));
    int k = 0;
    for (int i = 0; i < size; i++)
    {
        k = 0;
        for (int j = 0; j < size; j++)
        {
            if (arr[i] > arr[j])
                k++;
        }
        sorted_arr[k] = arr[i];
        swaps++;
    }

    for (int c = 0; c < size; c++)
    {
        arr[c] = sorted_arr[c];
    }
    params[0] = swaps;
    params[1] = k;
    finishTime = omp_get_wtime();
    resTime = finishTime - startTime;
    return resTime;
}

void merge(int arr[], int left, int mid, int right, int params[]) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int* L;
    int* R;

    L = (int*)malloc(n1 * sizeof(int));
    R = (int*)malloc(n2 * sizeof(int));
    for (i = 0; i < n1; i++)
    {
        L[i] = arr[left + i];
        params[0] += 1;
    }
    for (j = 0; j < n2; j++)
    {
        R[j] = arr[mid + 1 + j];
        params[0] += 1;
    }

    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2) {
        params[1] += 1;
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
            params[0] += 1;
        }
        else {
            arr[k] = R[j];
            j++;
            params[0] += 1;
        }
        k++;
    }

    while (i < n1) {
        params[1] += 1;
        arr[k] = L[i];
        i++;
        k++;
        params[0] += 1;
    }

    while (j < n2) {
        params[1] += 1;
        arr[k] = R[j];
        j++;
        k++;
        params[0] += 1;
    }
}

int mergeSort(int arr[], int left, int right, int params[]) {
    if (left < right) {
        params[1] += 1;
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid, params);
        mergeSort(arr, mid + 1, right, params);

        merge(arr, left, mid, right, params);
    }
    return 0;
}

double shellSort(int arr[], int n, int params[]) {
    double startTime;
    double finishTime;
    double resTime;
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

#include <stdio.h>

int checkSort(int arr[], int size) {
    int i;
    for (i = 1; i < size; i++) {
        if (arr[i] < arr[i - 1]) {
            return i; // ���������� ����� �������� � �������
        }
    }
    return -1; // ��� �������� ������������� �����
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
		scanf_s("%d", &count); // �������� ���������� ������� CPU

		mass = (int*)malloc(count * sizeof(int)); // �� ������ ���������� ��������� ������������ ������.

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

		for (int i = 0; i < count; i++) {
			fscanf_s(input_file_CPU, "%d", &mass[i]); // ���������� ������ �� ����� � ������
		}

		fclose(input_file_CPU); // ��������� ����
		printf("������ ������� ������!\n������� ����� ������� ��� �� ����������.");
		system("pause");
		break;
	default:
		break;
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
				if (runningBuble == -1) { // ������ ���� ���������� ���������� ��������� � �����������
					printf("��������� ���������� buble (�������� �������������): ������������ = %d, ��������� = %d, ����� ������ ������ = %15.10lf ��\n", param_buble[0], param_buble[1], _runningBuble);
				}
				else {
					printf("������ �� ��������: %d\n", running);
				}
				if (runningCounting == -1) {
					printf("��������� ���������� ��������� (�������� �������������): ������������ = %d, ��������� = %d, ����� ������ ������ = %15.10lf ��\n", param_counting[0], param_counting[1], _runningCounting);
				}
				else {
					printf("������ �� ��������: %d\n", running);
				}
				if (runningMerge == -1) {
					printf("��������� ���������� �������� (�������� �������������): ������������ = %d, ��������� = %d, ����� ������ ������ = %15.10lf ��\n", param_merge[0], param_merge[1], _runningMerge);
				}
				else {
					printf("������ �� ��������: %d\n", running);
				}
				if (runningShell == -1) {
					printf("��������� ���������� ����� (�������� �������������): ������������ =%d, ��������� = %d, ����� ������ ������ = %15.10lf ��\n", param_shell[0], param_shell[1], _runningShell);
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
					printf("|_________________________________________________________________|\n");
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
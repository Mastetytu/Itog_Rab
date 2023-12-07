#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <omp.h>
#include <time.h>
#include <malloc.h>

#define MAX_FILENAME_LENGTH 100
#define MAX_VALUE 100

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
			return i; // Возвращаем номер итерации с ошибкой
		}
	}
	return -1; // Все элементы отсортированы верно
}
int menu(int* point)
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
	printf_s("1. Сортировка Хоара.\n2. . Сортировка Шелла.\n3. Шейкерная сортировка.\n Выберите сортировку: ");
	scanf_s("%d", &turn);
	while (turn < 1 || turn > 4)
	{
		printf("Некорректный ввод, попробуйте еще раз:");
		scanf_s("%d", &turn);
	}
	return turn;
}
double quickSort(int* numbers, int left, int right, int* params)
{
	double startTime;
	double finishTime;
	double resTime;
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
double shellSort(int arr[], int n, int* params) {
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

double shekerSort(double* mass, int count, int* params)
{
	int left = 0, right = count - 1;
	int flag = 1;
	double startTime;
	double finishTime;
	double resTime;
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
int main()
{
	// Инициализация всех переменных с которыми будем работать
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));
	int* mass_CPU = 0;
	int* mass = 0;
	int* mass_for_fird;
	int* shekerSort_mass;
	int* quickSort_mass;
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

	
	running = start_menu();
	switch (running)
	{
	case 1:
		printf_s("Введите количество потоков : ");
		scanf_s("%d", &CPU_count); // задается количество потоков CPU
		mass_CPU = (int*)malloc(CPU_count * sizeof(int)); 
		for (int i = 0; i < CPU_count; i++)
		{
			mass_CPU[i] = 1 + rand() % 1001; // массив заполняется рандомными значениями.
		}
		break;
	case 2:
		printf_s("Введите количество чисел: ");
		scanf_s("%d", &CPU_count);

		mass_CPU = (int*)malloc(CPU_count * sizeof(int)); 

		printf_s("Введите данные в ports.txt (\\Itog_Rab\\Itog_Rab), после чего перезапустите программу\n");
		system("pause");

		
		char adr[100] = "\\Itog_Rab\\Itog_Rab"; 
		char CPU_file[100] = "Max.txt"; 
		char CPU_way[200];

		FILE* input_file_CPU = NULL;
		errno_t error1;
		errno_t error2;

		strcpy_s(CPU_way, sizeof CPU_way, adr); // Записываем в файл сначала путь а потом название файла и получаем полный адресс файла
		strncat_s(CPU_way, 100, CPU_file, 100);
		error1 = fopen_s(&input_file_CPU, CPU_way, "r+"); // Открываем файл

		if (input_file_CPU == 0)
		{
			printf_s("Не удалось открыть файл.");
			break;
		}

		for (int i = 0; i < CPU_count; i++) {
			fscanf_s(input_file_CPU, "%d", &mass_CPU[i]); // Записываем данные из файла в массив
		}

		fclose(input_file_CPU); // закрываем файл
		printf_s("Массив успешно создан!\nНажмите любую клавишу что бы продолжить.");
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
				printf("Введите количество потоков: "); 
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
				printf("Массив успешно создан!\nНажмите любую клавишу что бы продолжить.");
				system("pause");
				break;
			case 2:
				printf("Введите количество чисел: ");
				scanf_s("%d", &count);

				mass = (int*)malloc(count * sizeof(int));

				printf("Введите данные в ports.txt (\\Itog_Rab\\Itog_Rab), после чего перезапустите программу\n");
				system("pause");

				

				char adr[100] = "\\Itog_Rab\\Itog_Rab"; 
				char Flow_file[100] = "ports.txt"; 
				char Flow_way[200]; // Переменная в которой будет содержаться полный адресс файла

				FILE* input_file_Flow = NULL;
				errno_t error1;
				errno_t error2;

				strcpy_s(Flow_way, sizeof Flow_way, adr); // Записываем в файл сначала путь а потом название файла и получаем полный адресс файла
				strncat_s(Flow_way, 100, Flow_file, 100);
				error1 = fopen_s(&input_file_Flow, Flow_way, "r+"); // Открываем файл

				if (input_file_Flow == 0)
				{
					printf("Не удалось открыть файл.");
					break;
				}

				for (int i = 0; i < count; i++) {
					fscanf_s(input_file_Flow, "%d", &mass[i]); // сканируем данные из файла в массив
				}

				fclose(input_file_Flow); // Закрываем файл
				for (int i = 0; i < CPU_count; i++)
				{
					summ += mass[i];
				}
				printf("Массив успешно создан!\nНажмите любую клавишу что бы продолжить.");
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
					printf("Невозможно выполнить действие так как вы не заполнили данноые о временем и количеством потоков.");
					system("pause");
					break;
				}
				else if (mass_CPU == 0)
				{
					printf("Невозможно выполнить действие так как вы не заполнили данные о временем и количеством CPU.");
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
				double _runningquickSort = 0;       
				double _runningcheckSort = 0;
				double _runningShell = 0;
				_runningquickSort = quickSort(quickSort_mass,0, -1, param_buble);
				runningquickSort = checkSort(quickSort_mass, count);
				_runningcheckSort = shekerSort(shekerSort_mass, count, param_counting);
				runningcheckSort = checkSort(shekerSort_mass, count);				
				_runningShell = shellSort(shell_mass, count, param_shell);
				runningShell = checkSort(shell_mass, count);
				printf("|______________________________________________|\n");
				printf("|Сортировка|   Время   |  Кол-во    |  Кол-во  |\n");
				printf("|          |   работы  |перестановок|сравнений |\n");
				if (runningquickSort == -1) { 
					printf("|______________________________________________|\n");
					printf("|   Сортировка Хоара  |%-2.9f|%4s%-8d|%2s%-8d|\n", _runningquickSort, "", param_buble[0], "", param_buble[1]);
				}
				else {
					printf("Ошибка на итерации: %d\n", running);
				}
				if (runningcheckSort == -1) {
					printf("|______________________________________________|\n");
					printf("|Шейкерная сортировка |%-2.9f|%4s%-8d|%2s%-8d|\n", _runningcheckSort, "", param_counting[0], "", param_counting[1]);
				}
				else {
					printf("Ошибка на итерации: %d\n", running);
				}
				
				if (runningShell == -1) {
					printf("|______________________________________________|\n");
					printf("|   Шелла  |%-2.9f|%4s%-8d|%2s%-8d|\n", _runningShell, "", param_shell[0], "", param_shell[1]);
					printf("|______________________________________________|\n");
				}
				else {
					printf("Ошибка на итерации: %d\n", running);
				}
				system("pause");
				break;
			case 2:
				system("cls");
				printf_s("1. Сортировка Хоара.\n2. . Сортировка Шелла.\n3. Шейкерная сортировка.\n Выберите сортировку: ");
				int turn = 0;
				scanf_s("%d", &turn);
				switch (turn)
				{
				case 1:
					_running = quickSort(mass, 0, -1, param_buble);
					running = checkSort(mass, count);  // запускаем проверку сортировки
					if (running == -1) {  
						printf("Результат сортировки buble (критерии эффективности): перестановок = %d, сравнений = %d, время работы метода = %15.10lf мс\n", param_buble[0], param_buble[1], _running);
					}
					else {
						printf("Ошибка на итерации: %d\n", running);
					}
					system("pause");
					break;
				case 2:
					_running = shekerSort(mass, count, param_counting);
					running = checkSort(mass, count); 
					if (running == -1) {  
						printf("Результат сортировки подсчетом (критерии эффективности): перестановок = %d, сравнений = %d, время работы метода = %15.10lf мс\n", param_counting[0], param_counting[1], _running);
					}
					else {
						printf("Ошибка на итерации: %d\n", running);
					}
					system("pause");
					break;
				case 3:
					_running = shellSort(mass, count, param_shell); // Запускаем сортировку
					running = checkSort(mass, count);  // запускаем проверку
					if (running == -1) {  // Вывод
						printf("Результат сортировки Шелла (критерии эффективности): перестановок = %d, сравнений = %d, время работы метода = %15.10lf мс\n", param_shell[0], param_shell[1], _running);
					}
					else {
						printf("Ошибка на итерации: %d\n", running);
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
					mass_for_fird = (int*)malloc(count * sizeof(int)); 
					for (int i = 0; i < count; i++)
					{
						mass_for_fird[i] = mass[i]; 
					}
					_running = quickSort(mass, 0, -1, param_buble); // сортируем отдельно созданный массив
					system("cls");
					printf("|_________________________________________________________________|\n");
					printf("|  Номер   |  Квант   |Суммарное |  Номер   |  Время   |Оставшееся|\n");
					printf("| итерации |времени ЦП|Доступное |выбранного|выбранного| время ЦП |\n");  
					printf("|          |          |Время ЦП  |  потока  |  потока  |          |\n");
					for (int i = 0; i < CPU_count; i++)
					{
						int dynamictime = mass_CPU[i]; 
						while (dynamictime > 0)
						{
							int _count = 0;
							int _num;
							int _dynamictime = dynamictime;

							running = binarySearch(mass_for_fird, count, dynamictime); // Ищем максимально приблеженное ко времени CPU Значения с помощью бинарного поиска
							if (running == -1)
							{
								break;
							}
							_num = mass_for_fird[running]; // Записываем это занчение в переменную
							for (int i = running; i > 0; i--) // Что бы это число больше не появлялось мы преобразуем его в 0 и перемещаем в начало массива
							{
								mass_for_fird[i] = mass_for_fird[i - 1];
							}
							mass_for_fird[_count] = 0;
							_count++;
							for (int i = 0; i < count; i++) // Ищем Этот поток в неотсортированном массиве и записываем его номер
							{
								if (mass[i] == _num)
								{
									running = i;
								}
							}
							dynamictime = dynamictime - _num; // Считаем оставшееся время
							printf("|_________________________________________________________________|\n");
							printf("|%2s%-8d|%2s%-8d|%2s%-8d|%2s%-8d|%2s%-8d|%2s%-8d|\n", "", i, "", mass_CPU[i], "", _dynamictime, "", running + 1, "", _num, "", dynamictime); // Рисуем строку таблицы
						}
					}
					printf("|_________________________________________________________________|\n");
					ost_time = CPU_summ - summ;
					if (ost_time < 0)
					{
						printf("Для выполнения всех потоков не хватило: %d секунд\n", ost_time);
					}
					else if (ost_time > 0)
					{
						printf("Излишнее время: %d\n", ost_time);
					}
					system("pause");
				}
				else
				{
					FILE* file;
					fopen_s(&file, "ans_buble.txt", "w"); // Открываем файл ans_buble.txt Для записи или если такого файла нет создаем его
					if (file == NULL) {
						printf("Не удалось открыть файл.");
						return 1;
					}
					mass_for_fird = (int*)malloc(count * sizeof(int)); // Создаем отдельный массив для сортировки
					for (int i = 0; i < count; i++)
					{
						mass_for_fird[i] = mass[i]; // Записываем в него значения
					}
					_running = quickSort(mass, 0,count-1, param_buble); // Сортируем массив
					fprintf(file, "|_________________________________________________________________|\n");
					fprintf(file, "|  Номер   |  Квант   |Суммарное |  Номер   |  Время   |Оставшееся|\n");
					fprintf(file, "| итерации |времени ЦП|Доступное |выбранного|выбранного| время ЦП |\n");
					fprintf(file, "|          |          |Время ЦП  |  потока  |  потока  |          |\n");
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
						fprintf(file, "Для выполнения всех потоков не хватило: %d секунд\n", ost_time);
					}
					else if (ost_time > 0)
					{
						fprintf(file, "Излишнее время: %d\n", ost_time);
					}
					printf("Файл успешно создан!\nНажмите любую клавишу что бы продолжить.");
					fclose(file);
					system("pause");
				}
				break;
				
			case 2:
				if (count < 20)
				{
					mass_for_fird = (int*)malloc(count * sizeof(int));
					for (int i = 0; i < count; i++)
					{
						mass_for_fird[i] = mass[i];
					}
					_running = shekerSort(mass, count, param_counting);
					system("cls");
					printf("|_________________________________________________________________|\n");
					printf("|  Номер   |  Квант   |Суммарное |  Номер   |  Время   |Оставшееся|\n");
					printf("| итерации |времени ЦП|Доступное |выбранного|выбранного| время ЦП |\n");
					printf("|          |          |Время ЦП  |  потока  |  потока  |          |\n");
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
						printf("Для выполнения всех потоков не хватило: %d секунд\n", ost_time);
					}
					else if (ost_time > 0)
					{
						printf("Излишнее время: %d\n", ost_time);
					}
					system("pause");
				}
				else
				{

					FILE* file;
					fopen_s(&file, "ans_counting.txt", "w");
					if (file == NULL) {
						printf("Не удалось открыть файл.");
						return 1;
					}

					mass_for_fird = (int*)malloc(count * sizeof(int));
					for (int i = 0; i < count; i++)
					{
						mass_for_fird[i] = mass[i];
					}
					_running = shekerSort(mass, count, param_counting);
					fprintf(file, "|_________________________________________________________________|\n");
					fprintf(file, "|  Номер   |  Квант   |Суммарное |  Номер   |  Время   |Оставшееся|\n");
					fprintf(file, "| итерации |времени ЦП|Доступное |выбранного|выбранного| время ЦП |\n");
					fprintf(file, "|          |          |Время ЦП  |  потока  |  потока  |          |\n");
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
						fprintf(file, "Для выполнения всех потоков не хватило: %d секунд\n", ost_time);
					}
					else if (ost_time > 0)
					{
						fprintf(file, "Излишнее время: %d\n", ost_time);
					}
					printf("Файл успешно создан!\nНажмите любую клавишу что бы продолжить.");
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
					_running = shellSort(mass, count, param_shell);
					system("cls");
					printf("|_________________________________________________________________|\n");
					printf("|  Номер   |  Квант   |Суммарное |  Номер   |  Время   |Оставшееся|\n");
					printf("| итерации |времени ЦП|Доступное |выбранного|выбранного| время ЦП |\n");
					printf("|          |          |Время ЦП  |  потока  |  потока  |          |\n");
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
						printf("Для выполнения всех потоков не хватило: %d секунд\n", ost_time);
					}
					else if (ost_time > 0)
					{
						printf("Излишнее время: %d\n", ost_time);
					}
					system("pause");
				}
				else
				{

					FILE* file;
					fopen_s(&file, "ans_shell.txt", "w");
					if (file == NULL) {
						printf("Не удалось открыть файл.");
						return 1;
					}

					if (file == NULL) {
						printf("Не удалось открыть файл.");
						return 1;
					}

					mass_for_fird = (int*)malloc(count * sizeof(int));
					for (int i = 0; i < count; i++)
					{
						mass_for_fird[i] = mass[i];
					}
					_running = shellSort(mass, count, param_shell);
					fprintf(file, "|_________________________________________________________________|\n");
					fprintf(file, "|  Номер   |  Квант   |Суммарное |  Номер   |  Время   |Оставшееся|\n");
					fprintf(file, "| итерации |времени ЦП|Доступное |выбранного|выбранного| время ЦП |\n");
					fprintf(file, "|          |          |Время ЦП  |  потока  |  потока  |          |\n");
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
						fprintf(file, "Для выполнения всех потоков не хватило: %d секунд\n", ost_time);
					}
					else if (ost_time > 0)
					{
						fprintf(file, "Излишнее время: %d\n", ost_time);
					}
					printf("Файл успешно создан!\nНажмите любую клавишу что бы продолжить.");
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
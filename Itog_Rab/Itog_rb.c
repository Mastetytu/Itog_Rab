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
            return i; // Возвращаем номер итерации с ошибкой
        }
    }
    return -1; // Все элементы отсортированы верно
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
	// Инициализация всех переменных с которыми будем работать
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

	//Запуск стартового меню из menu.c
	running = start_menu();
	switch (running)
	{
	case 1:
		printf("Введите количество потоков : ");
		scanf_s("%d", &CPU_count); // задается количество потоков CPU
		mass_CPU = (int*)malloc(CPU_count * sizeof(int)); // На основе количества создается динамический массив.
		for (int i = 0; i < CPU_count; i++)
		{
			mass_CPU[i] = 1 + rand() % 1001; // массив заполняется рандомными значениями.
		}
		break;
	case 2:
		printf("Введите количество чисел: ");
		scanf_s("%d", &count); // задается количество потоков CPU

		mass = (int*)malloc(count * sizeof(int)); // На основе количества создается динамический массив.

		printf("Введите данные в ports.txt (\\Itog_Rab\\Itog_Rab), после чего перезапустите программу\n");
		system("pause");

		

		char adr[100] = "\\Itog_Rab\\Itog_Rab"; // Путь к файлу из которго будут взяты данные 
		char CPU_file[100] = "Max.txt"; // Название файла из которго будут взяты данные 
		char CPU_way[200];

		FILE* input_file_CPU = NULL;
		errno_t error1;
		errno_t error2;

		strcpy_s(CPU_way, sizeof CPU_way, adr); // Записываем в файл сначала путь а потом название файла и получаем полный адресс файла
		strncat_s(CPU_way, 100, CPU_file, 100);
		error1 = fopen_s(&input_file_CPU, CPU_way, "r+"); // Открываем файл

		if (input_file_CPU == 0)
		{
			printf("Не удалось открыть файл.");
			break;
		}

		for (int i = 0; i < count; i++) {
			fscanf_s(input_file_CPU, "%d", &mass[i]); // Записываем данные из файла в массив
		}

		fclose(input_file_CPU); // закрываем файл
		printf("Массив успешно создан!\nНажмите любую клавишу что бы продолжить.");
		system("pause");
		break;
	default:
		break;
	}
	while (1)
	{
		system("cls");
		running = menu(point); // открываем главное меню, передавая в него массив поинт из двух элементов в котором будет храниться выбор пользователя
		switch (point[0])
		{
		case 1:
			switch (point[1])
			{
			case 1:
				printf("Введите количество потоков: "); // задается количество потоков 
				scanf_s("%d", &count);
				mass = (int*)malloc(count * sizeof(int)); // на основе количества потоков задается динамический массив
				for (int i = 0; i < count; i++)
				{
					mass[i] = 1 + rand() % 255; // массив заполняется случайными значениями
				}
				system("cls");
				printf("Массив успешно создан!\nНажмите любую клавишу что бы продолжить.");
				system("pause");
				break;
			case 2:
				printf("Введите количество чисел: "); // задается количество потоков
				scanf_s("%d", &count);

				mass = (int*)malloc(count * sizeof(int)); // на основе Этого создается динамический массив

				printf("Введите данные в ports.txt (\\Itog_Rab\\Itog_Rab), после чего перезапустите программу\n");
				system("pause");

				

				char adr[100] = "\\Itog_Rab\\Itog_Rab"; // Путь к файлу с потоками
				char Flow_file[100] = "ports.txt"; // Название файла с потоками
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
				buble_mass = (int*)malloc(count * sizeof(int));
				counting_mass = (int*)malloc(count * sizeof(int));   // Создаем 4 массива для паралельной работы 4-х сортировок
				merge_mass = (int*)malloc(count * sizeof(int));
				shell_mass = (int*)malloc(count * sizeof(int));
				for (int i = 0; i < count; i++)
				{
					buble_mass[i] = mass[i];
					counting_mass[i] = mass[i];  // Заполняем каждый из массивов
					merge_mass[i] = mass[i];
					shell_mass[i] = mass[i];
				}
				int runningBuble = 0;
				int runningCounting = 0;
				int runningMerge = 0;
				int runningShell = 0;
				double _runningBuble = 0;       // Переменные для заполнения предложения вывода
				double _runningCounting = 0;
				double _runningMerge = 0;
				double _runningShell = 0;
				_runningBuble = bubbleSort(buble_mass, count, param_buble);
				runningBuble = checkSort(buble_mass, count);
				_runningCounting = countingSort(counting_mass, count, param_counting);
				runningCounting = checkSort(counting_mass, count);
				double startTimeMerge = omp_get_wtime();
				_running = mergeSort(merge_mass, 0, count - 1, param_merge);    // ЗАпускаем сортировки и проверки
				double finishTimeMerge = omp_get_wtime();
				_runningMerge = finishTimeMerge - startTimeMerge;
				runningMerge = checkSort(merge_mass, count);
				_runningShell = shellSort(shell_mass, count, param_shell);
				runningShell = checkSort(shell_mass, count);
				if (runningBuble == -1) { // Выводы если сортировки отработали корректно и некорректно
					printf("Результат сортировки buble (критерии эффективности): перестановок = %d, сравнений = %d, время работы метода = %15.10lf мс\n", param_buble[0], param_buble[1], _runningBuble);
				}
				else {
					printf("Ошибка на итерации: %d\n", running);
				}
				if (runningCounting == -1) {
					printf("Результат сортировки Подсчетом (критерии эффективности): перестановок = %d, сравнений = %d, время работы метода = %15.10lf мс\n", param_counting[0], param_counting[1], _runningCounting);
				}
				else {
					printf("Ошибка на итерации: %d\n", running);
				}
				if (runningMerge == -1) {
					printf("Результат сортировки Слиянием (критерии эффективности): перестановок = %d, сравнений = %d, время работы метода = %15.10lf мс\n", param_merge[0], param_merge[1], _runningMerge);
				}
				else {
					printf("Ошибка на итерации: %d\n", running);
				}
				if (runningShell == -1) {
					printf("Результат сортировки Шелла (критерии эффективности): перестановок =%d, сравнений = %d, время работы метода = %15.10lf мс\n", param_shell[0], param_shell[1], _runningShell);
				}
				else {
					printf("Ошибка на итерации: %d\n", running);
				}
				system("pause");
				break;
			case 2:
				system("cls");
				printf("Выберите сортировку: \n1. Сортировка пузырьком\n2. Сортировка подсчетом\n3. Сортировка Слиянием\n4. Сортировка Шелла\n Ваш выбор: ");
				int turn = 0;
				scanf_s("%d", &turn);
				switch (turn)
				{
				case 1:
					_running = bubbleSort(mass, count, param_buble); // запускаем сортировку 
					running = checkSort(mass, count);  // запускаем проверку сортировки
					if (running == -1) {  // Вывод 
						printf("Результат сортировки buble (критерии эффективности): перестановок = %d, сравнений = %d, время работы метода = %15.10lf мс\n", param_buble[0], param_buble[1], _running);
					}
					else {
						printf("Ошибка на итерации: %d\n", running);
					}
					system("pause");
					break;
				case 2:
					_running = countingSort(mass, count, param_counting);  // запускаем сортировку
					running = checkSort(mass, count); //  запускаем проверку сортировки
					if (running == -1) {  // Вывод
						printf("Результат сортировки подсчетом (критерии эффективности): перестановок = %d, сравнений = %d, время работы метода = %15.10lf мс\n", param_counting[0], param_counting[1], _running);
					}
					else {
						printf("Ошибка на итерации: %d\n", running);
					}
					system("pause");
					break;
				case 3:
					printf("\n");
					double startTime;
					double finishTime; // Переменные для замерки времени
					double resTime;
					startTime = omp_get_wtime(); // Начинаем замерку времени
					_running = mergeSort(mass, 0, count - 1, param_merge); // Запускаем сортировку
					finishTime = omp_get_wtime();  // Заканчиваем замерку Времени
					resTime = finishTime - startTime; // Считаем сколько времени было затрачено
					running = checkSort(mass, count);  // Запускаем проверку сортировки
					if (running == -1) { // вывод
						printf("Результат сортировки Слиянием (критерии эффективности): перестановок = %d, сравнений = %d, время работы метода = %15.10lf мс\n", param_merge[0], param_merge[1], resTime);
					}
					else {
						printf("Ошибка на итерации: %d\n", running);
					}
					system("pause");
					break;
				case 4:
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
			running = fird_punct(); // Запускаем меню из menu.c
			switch (running)
			{
			case 1:
				if (count < 20) // Проверяем что потоков меньше 20
				{
					mass_for_fird = (int*)malloc(count * sizeof(int)); // создаем массив который Будем сортировать
					for (int i = 0; i < count; i++)
					{
						mass_for_fird[i] = mass[i]; // Записываем в него значения
					}
					_running = bubbleSort(mass_for_fird, count, param_buble); // сортируем отдельно созданный массив
					system("cls");
					printf("|_________________________________________________________________|\n");
					printf("|  Номер   |  Квант   |Суммарное |  Номер   |  Время   |Оставшееся|\n");
					printf("| итерации |времени ЦП|Доступное |выбранного|выбранного| время ЦП |\n");  // вывод заголовка таблички
					printf("|          |          |Время ЦП  |  потока  |  потока  |          |\n");
					for (int i = 0; i < CPU_count; i++)
					{
						int dynamictime = mass_CPU[i]; // Записываем Время CPU Для данной итерации
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
					_running = bubbleSort(mass_for_fird, count, param_buble); // Сортируем массив
					fprintf(file, "|_________________________________________________________________|\n");
					fprintf(file, "|  Номер   |  Квант   |Суммарное |  Номер   |  Время   |Оставшееся|\n");
					fprintf(file, "| итерации |времени ЦП|Доступное |выбранного|выбранного| время ЦП |\n"); // Рисуем шапку таблицы
					fprintf(file, "|          |          |Время ЦП  |  потока  |  потока  |          |\n");
					for (int i = 0; i < CPU_count; i++)
					{
						int dynamictime = mass_CPU[i]; // Записываем Время CPU Для данной итерации
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
							fprintf(file, "|_________________________________________________________________|\n");
							fprintf(file, "|%2s%-8d|%2s%-8d|%2s%-8d|%2s%-8d|%2s%-8d|%2s%-8d|\n", "", i, "", mass_CPU[i], "", _dynamictime, "", running + 1, "", _num, "", dynamictime); // Рисуем строку таблицы
						}
					}
					fprintf(file, "|_________________________________________________________________|\n");
					printf("Файл успешно создан!\nНажмите любую клавишу что бы продолжить.");
					fclose(file);
					system("pause");
				}
				break;
				// Дальше мне писать влом там Все аналогично сортировке BUBLE.
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
					_running = countingSort(mass_for_fird, count, param_counting);
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
					_running = mergeSort(mass_for_fird, 0, count - 1, param_merge);
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
					system("pause");
				}
				else
				{

					FILE* file;
					fopen_s(&file, "ans_merge.txt", "w");
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
					_running = mergeSort(mass_for_fird, 0, count - 1, param_merge);
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
					printf("Файл успешно создан!\nНажмите любую клавишу что бы продолжить.");
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
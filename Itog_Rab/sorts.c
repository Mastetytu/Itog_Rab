#define MAX_VALUE 100
#include <omp.h>
#include <time.h>

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
        params[0]+=1;
    }
    for (j = 0; j < n2; j++)
    {
        R[j] = arr[mid + 1 + j];
        params[0]+=1;
    }

    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2) {
        params[1]+=1;
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
            params[0]+=1;
        }
        else {
            arr[k] = R[j];
            j++;
            params[0]+=1;
        }
        k++;
    }

    while (i < n1) {
        params[1]+=1;
        arr[k] = L[i];
        i++;
        k++;
        params[0]+=1;
    }

    while (j < n2) {
        params[1]+=1;
        arr[k] = R[j];
        j++;
        k++;
        params[0]+=1;
    }
}

int mergeSort(int arr[], int left, int right, int params[]) {
    if (left < right) {
        params[1]+=1;
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

int binarySearch(int *mass, int size, int target)
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
//мое
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
            swaps -= 1;
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
    params[0] = swaps;
    params[1] = cmps;
    finishTime = omp_get_wtime();
    resTime = finishTime - startTime;
    return resTime;
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

double shekerSort(double* mass, int count)
{
    int left = 0, right = count - 1;
    int flag = 1;
    double startTime;
    double finishTime;
    double resTime;
    int swaps = 0;
    int cmps = 0;

    while ((left < right) && flag > 0)
    {
        cmps += 1;
        flag = 0;
        for (int i = left; i < right; i++)
        {
            if (mass[i] > mass[i + 1])
            {
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

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// тип элемента - int, числа упорядочиваются по неубыванию модулей, сортировки: методом Шелла и быстрая сортировка

static int num_of_comp = 0, num_of_exch = 0; // глобальные счетчики сравнений и перемещений элементов

int abs(int x) {  // функция для вычисления модуля числа
    return (x >= 0) ? x : -x; 
}

void array_str(int *a, int n) { // функция создания массива упорядоченных элементов
    
    a[0] = 0;
    int pos = 1, neg = -1;
    for(int i = 1; i < n; i++) {
        if (i % 2) { // чередуем положительные и отрицательные числа
            a[i] = pos;
            pos++;
        }
        else {
            a[i] = neg;
            neg--;
        }
    }
    
}

void array_rev(int *a, int n) { // функция создания массива упорядоченных в обратном порядке элементов
    
    int k = n / 2;
    a[0] = k;
    int pos = k - 1, neg = -(k - 1);
    for(int i = 1; i < n; i++) {
        if (i % 2) { // чередуем положительные и отрицательные числа
            a[i] = neg;
            neg++;
        }
        else {
            a[i] = pos;
            pos--;
        }
    }
    
}

void array_rand(int *a, int n) { // функция создания массива со случайной расстановкой элементов
    
    srand(time(NULL));
    for(int i = 0; i < n; i++) {
        if(i % 2) a[i] = rand() % n; // чередуем положительные и отрицательные числа; берём значения (-n, n)
        else a[i] = -(rand() % n);
    }
    
}

void print(int *a, int n) { // функция вывода массива
    
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\n");
   
}

void shell_sort (int *a, int n) { // сортировка методом Шелла
    
    int i, j, step, tmp; 
    for (step = n / 2; step > 0; step /= 2) { // задаём шаг сортировки (вначале он равен n/2, а затем шаг каждый раз уменьшается вдвое)
    
        for (i = step; i < n; i++) { // упорядочиваем подпоследовательности элементов, отстоящих друг от друга на step позиций
        
            tmp = a[i]; 
            for (j = i; j >= step; j -= step) {
                num_of_comp++;
                if (abs(tmp) < abs(a[j - step])) { // сравниваем элементы на позициях, отличающихся на step
                    a[j] = a[j - step];
                    num_of_exch++;
                }
                else {
                    break;
                }
            }
            a[j] = tmp;
            
        }
    }
    
}

static int start = 0; // начало рассматриваемого массива

void quick_sort(int *a, int n) { // быстрая сортировка, рекурсивная реализация 
    
    int sup = abs(a[start + ((n - start) / 2)]); // выбираем опорный элемент (стоящий в середине подмассива)
    int left = start, right = n - 1; // индексы начала и конца рассматриваемого подмассива

    while(left <= right) {  
        
        num_of_comp++;
        while (abs(a[left]) < sup) { // увеличиваем left, пока элемент меньше опорного
            num_of_comp++;
            left++;
        }
        
        num_of_comp++;
        while (abs(a[right]) > sup) { // уменьшаем right, пока элемент больше опорного
            num_of_comp++;
            right--;
        }
        
        if (left <= right) { 
            num_of_comp++;
            if(abs(a[left]) != abs(a[right])) { // если элементы не равны, то меняем их местами
                num_of_exch++;
                int rem = a[left];
                a[left] = a[right];
                a[right] = rem;
            }
            left++;  // увеличиваем left на 1
            right--; // уменьшаем right на 1
        }
    }
    
    // повторяем рекурсивно, пока не дойдём до массива из 1 элемента
    if (right > start) { 
        quick_sort(a, right + 1); // сортируем левый подмассив (из элементов, меньше опорного)
    }
    if (left < n - 1) {
        start = left; // меняем начало сортируемого подмассива
        quick_sort(a, n); // сортируем правый подмассив (из элементов, больше опорного)
    }
    start = 0; // обнуляем переменную после завершения сортировки
    
}

void check(int *a, int n) { // функция проверки отсортированности массива

    for(int i = 1; i < n; i++) {
        if (abs(a[i - 1]) > abs(a[i])) { // условие нарушения порядка сортировки
            printf("The array isn't sorted\n");
            return;
        }
    }
    printf("The array is sorted\n");
    
}

int main(void) {
    
    int *a;
    
    for(int n = 10; n <= 10000; n*=10) {
        
        printf("\nN = %d\n", n);
        a = malloc(sizeof(int) * n); // динамически выделяем память под массив
        
        for(int sort_type = 1; sort_type <= 2; sort_type++) { // тип сортировки: 1 - сортировка методом Шелла, 2 - быстрая сортировка
            
            if(sort_type == 1) printf("\nShell sort:\n");
            else printf("\nQuick sort:\n");
            
            for(int array_type = 1; array_type < 4; array_type++) {
            
                if(array_type == 1) { // упорядоченный массив
                    printf("\nArray straight: ");
                    array_str(a, n);
                } else if (array_type == 2) { // упорядоченный в обратном порядке массив
                    printf("\nArray reverse: ");
                    array_rev(a, n);
                } else {
                    
                    printf("\nArray random: "); // массив случайных элементов
                    array_rand(a, n);
                }
                
                if (n == 10) print(a, n);
                
                if (sort_type == 1) {
                    shell_sort(a, n);
                    printf("Shell sort: comparisons = %d, exchanges = %d\n", num_of_comp, num_of_exch);
                } else {
                    quick_sort(a, n);
                    printf("Quick sort: comparisons = %d, exchanges = %d\n", num_of_comp, num_of_exch);
                }
                num_of_comp = 0, num_of_exch = 0; // обнуляем глобальные счетчики 
                
                if (n == 10) { 
                    printf("The result array: ");
                    print(a, n);
                }
                
                check(a, n); // проверка отсортированности получившегося массива
            }
        }
    }
    
    free(a);
    return 0;
    
}

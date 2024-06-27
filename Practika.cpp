#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

void swap(int* start, int* end) {
    int elem = *start;
    *start = *end;
    *end = elem;
}

void cocktailSort(int mass[], int n) {
    int swapped = 1;
    int start = 0;
    int end = n - 1;

    while (swapped) {
        swapped = 0;
        for (int i = start; i < end; i++) {
            if (mass[i] > mass[i + 1]) {
                swap(&mass[i], &mass[i + 1]);
                swapped = 1;
            }
        }

        if (!swapped)
            break;

        swapped = 0;
        end--;

        for (int i = end - 1; i >= start; i--) {
            if (mass[i] > mass[i + 1]) {
                swap(&mass[i], &mass[i + 1]);
                swapped = 1;
            }
        }
        start++;
    }
}

int main() {

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int choice;
    printf("Меню:\n");
    printf("1. Пользователь сам заполняет массив и указывает его размер\n");
    printf("2. Пользователь вводит название файла и он сортируется\n");
    printf("3. Пользователь вводит размер массива и он заполняется случайными числами\n");
    printf("Выберите вариант (1, 2 или 3): ");
    scanf("%d", &choice);

    int n = 0;
    int* mass = NULL;

    if (choice == 1) {
        printf("Введите размер массива: ");
        if (scanf("%d", &n) != 1 || n <= 0) {
            printf("Ошибка: введено некорректное значение. Пожалуйста, введите целое число.\n");
            return 1;
        }
        mass = (int*)malloc(n * sizeof(int));

        printf("Введите элементы массива:\n");
        for (int i = 0; i < n; i++) {
            if (scanf("%d", &mass[i]) != 1) {
                printf("Ошибка: введено некорректное значение. Пожалуйста, введите целое число.\n");
                free(mass);
                return 1;
            }
        }
        printf("\nМассив создан");
    }
    else if (choice == 2) {
        char filename[100];
        printf("Введите название файла: ");
        scanf("%s", filename);

        FILE* file = fopen(filename, "r");
        if (file == NULL) {
            printf("Ошибка при открытии файла.\n");
            return 1;
        }

        int number;
        while (fscanf(file, "%d", &number) == 1) {
            n++;
            mass = (int*)realloc(mass, n * sizeof(int));
            mass[n - 1] = number;
        }
        fclose(file);
        printf("\nМассив создан");
    }
    else if (choice == 3) {
        printf("Введите размер массива: ");
        if (scanf("%d", &n) != 1 || n <= 0) {
            printf("Ошибка: введено некорректное значение. Пожалуйста, введите положительное целое число.\n");
            return 1;
        }
        mass = (int*)malloc(n * sizeof(int));

        srand(time(0));
        FILE* createdFile = fopen("list.txt", "w");
        for (int i = 0; i < n; i++) {
            mass[i] = (rand() % 2001) - 1000;
            fprintf(createdFile, "%d\n", mass[i]);
        }
        fclose(createdFile);
        printf("\nМассив создан, сохранен в файле 'list.txt'");
    }  
    else {
        printf("Неверный выбор. Попробуйте еще раз.\n");
        return 1;
    }

    time_t start = clock();
    cocktailSort(mass, n);
    time_t end = clock();
    double time = ((double)(end - start)) / 1000;

    FILE* sortedFile = fopen("sorted_list.txt", "w");
    for (int i = 0; i < n; i++) {
        fprintf(sortedFile, "%d\n", mass[i]);
    }
    fclose(sortedFile);

    printf("\nМассив отсортирован, сохранен в файле 'sorted_list.txt'");
    printf("\n\nВремя сортировки: %f секунд\n", time);
    free(mass);

    return 0;
}
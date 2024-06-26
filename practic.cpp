#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

// Swap function
void swap(int* arr, int i, int j)
{
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

void shekerSort(int mas[], int size) {
	
	int left = 0, right = size - 1;
	int flag = 1;
	while (left < right && flag>0) {
		flag = 0;
		for (int i = left; i < right; i++) {
			if (mas[i] > mas[i + 1]) { 
				swap(mas, i, i + 1);
				flag = 1;
			}
		}
		right--;
		for (int i = right; i > left; i--) {
			if (mas[i] < mas[i - 1]) {
				swap(mas, i-1, i);
				flag = 1;
			}
		}
		left++;
		if (flag == 0) break;
	}

}



// Function to print an array
void printArray(int arr[], int size)
{
	int i;
	for (i = 0; i < size; i++)
		printf("%d ", arr[i]);
	printf("\n");
}


int main()
{
	int *arr;
	int n;
	system("chcp 1251");
	system("cls");
	printf("Введите размер массива: ");
	scanf("%d", &n);
	// Выделение памяти
	arr = (int*)malloc(n * sizeof(int));
	for (int i=0; i < n; i++)
	{
		arr[i] = rand()%(20001)-10000;
	}
	shekerSort(arr, n);            
	printf("Sorted array: ");
	printArray(arr, n);
	return 0;
}
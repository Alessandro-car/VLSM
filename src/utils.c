#include "../include/utils.h"

void quicksort_desc(int* arr, int low, int high) {
	if (low >= high || low < 0) return;
	int p = partition(arr, low, high);
	quicksort_desc(arr, low, p - 1);
	quicksort_desc(arr, p + 1, high);
}

int partition(int* arr, int low, int high) {
	int pivot = arr[high];

	int i = low;
	for (int j = low; j < high; j++) {
		if (arr[j] >= pivot) {
			int tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
			i++;
		}
	}
	int tmp = arr[i];
	arr[i] = arr[high];
	arr[high] = tmp;
	return i;
}


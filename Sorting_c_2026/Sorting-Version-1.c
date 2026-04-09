/*
* Sorting Algorithms Benchmark
* Author: Alphabet6135
* Date:   April 2026
* Version: 1.0
* 
* Description:
*	Compares runtime performance of 6 sorting algorithms
*	using the same randomly generated input data.
*	Algorithms: Bubble, Selection, Insertion,Quick, Counting, Radix
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>

void bubble_sort(int* arr, int n);
void selection_sort(int* arr, int n);
void insertion_sort(int* arr, int n);
void quick_sort(int* arr, int n);
void counting_sort(int* arr, int n);
void radix_sort(int* arr, int n);

// SortResult: stores name and runtime
typedef struct {
	char name[20];
	double time;
}SortResult;

//prints ASCII bar chart of sort times
void print_bar_chart(SortResult* results, int count) {
	double max_time = results[0].time;
	for (int i = 0;i < count;i++) {
		if (results[i].time > max_time)
			max_time = results[i].time;
	}
	printf("\n==== Visual Comparison ====\n");
	for (int i = 0;i < count;i++) {
		int bar = (int)(results[i].time / max_time * 30);
		printf("%-15s |", results[i].name);
		for (int j = 0;j < bar; j++) printf("#");
		for (int j = bar;j < 30;j++) printf("-");
		printf("| %.4fs\n", results[i].time);
	}
 }

/*
* time_sort: measures prints runtime of a sort
* @arr  : array to sort
* @n:	  array length
* @sort:  function pointer to sort
* @name:  algorithm name for display
* Returns:elapsed time in seconds
*/
double time_sort(int* arr, int n, void (*sort)(int*, int), char* name) {
	clock_t start = clock();
	sort(arr, n);
	clock_t end = clock();
	double time = (double)(end - start) / CLOCKS_PER_SEC;
	printf("%-20s time: %f s\n", name, time);
	return time;
}

int main() {
	srand(time(NULL));
	int n = 50000;
	int* arr1 = (int*)malloc(n * sizeof(int));
	int* arr2 = (int*)malloc(n * sizeof(int));
	int* arr3 = (int*)malloc(n * sizeof(int));
	int* arr4 = (int*)malloc(n * sizeof(int));
	int* arr5 = (int*)malloc(n * sizeof(int));
	int* arr6 = (int*)malloc(n * sizeof(int));

	if (arr1 == NULL)return 1;
	if (arr2 == NULL)return 1;
	if (arr3 == NULL)return 1;
	if (arr4 == NULL)return 1;
	if (arr5 == NULL)return 1;
	if (arr6 == NULL)return 1;

	for (int i = 0;i < n;i++) {
		arr1[i] = rand() % 10000;
	}
	memcpy(arr2, arr1, n * sizeof(int));
	memcpy(arr3, arr1, n * sizeof(int));
	memcpy(arr4, arr1, n * sizeof(int));
	memcpy(arr5, arr1, n * sizeof(int));
	memcpy(arr6, arr1, n * sizeof(int));

	SortResult results[6];

	printf("==== Sorting Comparison(n=%d) ====\n", n);
	strcpy(results[0].name, "bubble");
	results[0].time=time_sort(arr1, n, bubble_sort, "bubble_sort");
	strcpy(results[1].name, "Selection");
	results[1].time = time_sort(arr2, n, selection_sort, "selection_sort");
	strcpy(results[2].name, "Insertion");
	results[2].time = time_sort(arr3, n, insertion_sort, "insertion_sort");
	strcpy(results[3].name, "Quick");
	results[3].time = time_sort(arr4, n, quick_sort, "quick_sort");
	strcpy(results[4].name, "Counting");
	results[4].time = time_sort(arr5, n, counting_sort, "counting_sort");
	strcpy(results[5].name, "Radix");
	results[5].time = time_sort(arr6, n, radix_sort, "radix_sort");
	
	print_bar_chart(results, 6);

	free(arr1);arr1 = NULL;
	free(arr2);arr2 = NULL;
	free(arr3);arr3 = NULL;
	free(arr4);arr4 = NULL;
	free(arr5);arr5 = NULL;
	free(arr6);arr6 = NULL;

	return 0;
}

/*
* bubble_sort
* Time:   O(n²) avg, O(n) best case
* Space:  O(1)
* Stable: YES	
*/
void bubble_sort(int* arr, int n) {
	for (int i = 0;i < n - 1;i++) {
		int count = 0;
		for (int j = 0;j < n-i-1;j++) {
			if (arr[j] > arr[j + 1]) {
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
				count = 1;
			}
		}if (count == 0)break;
	}
}
/*
* selection_sort
* Time:   O(n²)
* Space:  O(1)
* Stable: NO
*/
void selection_sort(int* arr, int n) {
	for (int i = 0;i < n-1;i++) {
		int min = i;
		for (int j = i;j < n;j++) {
			if (arr[j] < arr[min])
				min = j;
		}
		if (min != i) {
			int temp = arr[i];
			arr[i] = arr[min];
			arr[min] = temp;
		}
	}
}
/*
* insertion_sort
* Time:   O(n²) avg, O(n) best case
* Space:  O(1)
* Stable: YES
*/
void insertion_sort(int* arr, int n) {
	for (int i = 1;i < n;i++) {
		int key = arr[i];
		int j = i-1;
		while (j>=0&&arr[j] >key) {
			arr[j + 1] = arr[j];
			j--;}   
		arr[j + 1] = key;
	}
}
/*
* partition: helper for quick_sort
* Uses last element as pivot
*/
int partition(int* arr, int low, int high) {
	int i = low - 1;
	int p = arr[high];
	for (int j = low;j < high;j++) {
		if (arr[j] < p) {
			i++;
			int temp = arr[j];
			arr[j] = arr[i];
			arr[i] = temp; 
		}
	}
		int temp = arr[i + 1];
		arr[i + 1] = arr[high];
		arr[high]=temp;
		return i + 1;
}
/*
* quick_sort
* Time:   O(nlogn) avg, O(n²) worst
* Space:  O(logn)
* Stable: NO
*/
void quick_s(int* arr, int low, int high) {
	if (low < high) {
		int pi = partition(arr, low, high);
		quick_s(arr, low, pi - 1);
		quick_s(arr, pi + 1, high);
	}
}
void quick_sort(int* arr, int n) {
	quick_s(arr, 0, n - 1);
}
/*
* counting_sort
* Time:   O(n+k), k = max value
* Space:  O(k)
* Stable: YES
*/
void counting_sort(int* arr, int n) {
	int max = arr[0];
	for (int i = 0;i < n;i++) { if (max < arr[i]) max = arr[i]; }
	
	int* count = (int*)calloc( max + 1, sizeof(int));
	if (count == NULL)return;
	for (int i = 0;i < n;i++) { count[arr[i]]++; }
	for (int i = 1;i <= max;i++) { count[i] += count[i - 1]; }

	int* output = (int*)malloc(n * sizeof(int));
	if (output == NULL)return;
	for (int i = n - 1;i >= 0;i--) {
		output[count[arr[i]] - 1] = arr[i];
		count[arr[i]]--;
	}
	for (int i = 0;i < n;i++) { arr[i] = output[i]; }
	
	free(count);
	free(output);
}
/*
* r_counting: helper for radix_sort
* Sorts by a single digit position
* @exp: 1=ones,10=tens,100=hundreds
*/
void r_counting(int* arr, int n, int exp) {
	int count[10] = { 0 };
	for (int i = 0;i < n;i++) { count[(arr[i] / exp) % 10]++; }
	for (int i = 1;i < 10;i++) { count[i] += count[i - 1]; }

	int* output = (int*)malloc(n * sizeof(int));
	if (output == NULL)return;
	for (int i = n - 1;i >= 0;i--) {
		output[count[(arr[i] / exp) % 10] - 1] = arr[i];
		count[(arr[i] / exp) % 10]--;
	}
	for (int i = 0;i < n;i++) { arr[i] = output[i]; }

	free(output);
}
/*
* radix_sort
* Time:   O(d*n), d = number of digits
* Space:  O(n)
* Stable: YES
*/
void radix_sort(int* arr, int n) {
	int max = arr[0];
	for (int i = 0;i < n;i++) { if (max < arr[i]) max = arr[i]; }
	for (int exp = 1;max / exp > 0;exp *= 10) {
		r_counting(arr, n, exp);
	}
}

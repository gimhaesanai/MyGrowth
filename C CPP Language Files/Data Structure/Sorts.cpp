/*
	1. 선택 정렬
	2. 버블 정렬
	3. 삽입 정렬
	4. 기수 정렬
	5. 병합 정렬
	6. 퀵	정렬
	7. 힙	정렬
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "QueueListForSorting.h"

#define ARRAY_LENGTH 8
#define TRUE 1
#define FALSE 0

void SelectionSort(int[]);
void BubbleSort(int[]);
void ImprovedBubbleSort(int[]);
void InsertionSort(int[]);
void RadixSort(int[], int);
void MergeSort(int[], int);
void QuickSort(int[]);
void HeapSort(int[]);

void swap(int*, int*);
void Print(int[]);
void MergePrint(int[], int);
void QuickPrint(int[], int, int, int, int, int);
void InitArray(int[]);

void RadixInit(List**);									// 기수정렬시 Queue가 들어갈 배열 초기화
int PowerC(int, int);									// (자릿수, 1)의 매개변수 형식을 가지며 10^자릿수의 값을 반환한다.
int* DivideMergeSort(int[], int);						// 병합정렬시 배열을 나눌 때 사용
int* MergeMergeSort(int[], int[], int);					// 병합정렬시 배열을 합칠 때 사용
int* LeftQuickSort(int[], int, int, int, int);			// 퀵  정렬시 피벗을 기준으로 왼쪽에 있는 자료들을 정렬할 때 사용
int* RightQuickSort(int[], int, int, int, int);			// 퀵  정렬시 피벗을 기준으로 오른쪽에 있는 자료들을 정렬할 때 사용
void InsertHeapSort(int[], int);
int RemoveHeapSort(int[]);

int main() {
	int data[ARRAY_LENGTH];

	SelectionSort(data);
	BubbleSort(data);
	ImprovedBubbleSort(data);
	InsertionSort(data);
	RadixSort(data, 2);
	MergeSort(data, ARRAY_LENGTH);
	QuickSort(data);
	HeapSort(data);

	return 0;
}

void swap(int* n1, int* n2) {
	int temp = *n1;
	*n1 = *n2;
	*n2 = temp;
}

void Print(int data[]) {
	for (int i = 0; i < ARRAY_LENGTH; i++) {
		if (i == 0) printf("{ ");
		printf("%2d ", data[i]);
		if (i == ARRAY_LENGTH - 1) printf("}\n");
	}
}

void MergePrint(int data[], int len) {
	for (int i = 0; i < len; i++) {
		if (i == 0) printf("{ ");
		printf("%d ", data[i]);
		if (i == len - 1) printf("}\n");
	}
}

void QuickPrint(int data[], int s, int low, int high, int pivot, int len) {
	for (int i = s; i < s + len; i++) {
		if (i == s) printf("{ ");
		printf("%3d ", data[i]);
		if (i == s + len - 1) printf("}\n");
	}
	for (int i = s; i < s + len; i++) {
		if (i == s) printf("{ ");
		if ((i == low) && (low == high)) printf(" LH ");
		else if ((i == low) && (low == pivot)) printf(" LP ");
		else if ((i == high) && (high == pivot)) printf(" HP ");
		else {
			if (i == low) printf(" L  ");
			else if (i == high) printf(" H  ");
			else if (i == pivot) printf(" P  ");
			else printf(" -  ");
		}
		if (i == s + len - 1) printf("}\n");
	}
}

void InitArray(int arr[]) {
	int data[ARRAY_LENGTH] = { 56, 82, 24, 10, 99, 45, 37, 76 };

	for (int i = 0; i < ARRAY_LENGTH; i++) {
		arr[i] = data[i];
	}
}

void SelectionSort(int data[]) {
	InitArray(data);
	printf("\n-----------------------------\n");
	printf("| 선택 정렬 - SelectionSort |\n");
	printf("-----------------------------\n\n");

	printf("-- 변환 전\n");
	Print(data);

	int min = 0, idx = 0;
	printf("-- 변환 중\n");
	while (idx != ARRAY_LENGTH - 1) {
		min = idx;
		for (int i = idx; i < ARRAY_LENGTH; i++) {
			if (data[min] > data[i])
				min = i;
		}
		swap(&data[idx], &data[min]);
		Print(data);
		idx++;
	}
	printf("-- 변환 후\n");
	Print(data);
}

void BubbleSort(int data[]) {
	InitArray(data);
	printf("\n--------------------------\n");
	printf("| 버블 정렬 - BubbleSort |\n");
	printf("--------------------------\n\n");

	printf("-- 변환 전\n");
	Print(data);

	int cnt = ARRAY_LENGTH - 1, d1 = 0, d2 = 1;
	printf("-- 변환 중\n");
	while (cnt--) {
		d1 = 0, d2 = 1;
		for (int i = cnt; i >= 0; i--) {
			if (data[d1] > data[d2]) swap(&data[d1], &data[d2]);
			Print(data);
			d1++; d2++;
		}
	}

	printf("-- 변환 후\n");
	Print(data);
}

void ImprovedBubbleSort(int data[]) {
	InitArray(data);
	printf("\n---------------------------------\n");
	printf("| 개선된 버블 정렬 - BubbleSort |\n");
	printf("---------------------------------\n\n");

	printf("변환 전\n");
	Print(data);

	int cnt = ARRAY_LENGTH - 1, d1 = 0, d2 = 1, check = 1;
	printf("-- 변환 중\n");
	while (check && cnt--) {
		check = 0, d1 = 0, d2 = 1;
		for (int i = cnt; i >= 0; i--) {
			if (data[d1] > data[d2]) {
				swap(&data[d1], &data[d2]);
				check = 1;
			}
			Print(data);
			d1++; d2++;
		}
	}

	printf("변환 후\n");
	Print(data);
}

void InsertionSort(int data[]) {
	InitArray(data);
	printf("\n-----------------------------\n");
	printf("| 삽입 정렬 - InsertionSort |\n");
	printf("-----------------------------\n\n");

	printf("-- 변환 전\n");
	Print(data);

	for (int i = 1; i < ARRAY_LENGTH; i++) {
		for (int j = i - 1; j >= 0; j--) {
			if (data[j] > data[j + 1])
				swap(&data[j], &data[j + 1]);
			else
				break;
			Print(data);
		}
	}

	printf("-- 변환 후\n");
	Print(data);
}

void RadixSort(int data[], int pow) {
	InitArray(data);
	printf("\n-------------------------\n");
	printf("| 기수 정렬 - RadixSort |\n");
	printf("-------------------------\n\n");

	printf("-- 변환 전\n");
	Print(data);

	List* list[10];
	RadixInit(list);

	printf("-- 변환 중\n");
	int rPow = 1;
	while (pow + 1 != rPow) {
		printf("-- %d의 자리수로 정렬\n", PowerC(rPow, 1));
		for (int i = 0; i < ARRAY_LENGTH; i++) {
			Enqueue(list[(data[i] % (PowerC(rPow, 1) * 10)) / PowerC(rPow, 1)], data[i]);
		}
		int cnt = 0;
		for (int i = 0; i < 10; i++) {
			Data t = Dequeue(list[i]);
			while (t != -1) {
				data[cnt++] = t;
				t = Dequeue(list[i]);
			}
		}
		Print(data);
		rPow++;
	}

	printf("-- 변환 후\n");
	Print(data);
}

void RadixInit(List * list[]) {
	for (int i = 0; i < 10; i++) {
		list[i] = (List*)malloc(sizeof(List));
		ListInit(list[i]);
	}
}

int PowerC(int radix, int res) {
	if (radix < 2) return res;
	return PowerC(radix - 1, res * 10);
}

void MergeSort(int data[], int len) {
	InitArray(data);
	printf("\n-------------------------\n");
	printf("| 병합 정렬 - MergeSort |\n");
	printf("-------------------------\n\n");
	int t = len;
	while (TRUE) {
		if (t % 2 != 0) {
			t %= 2;
			break;
		}
		t /= 2;
		if (t == 0)
			break;
	}
	if (t != 0) {
		printf("-- 변환 전\n");
		Print(data);

		printf("-- 변환 중\n");
		data = DivideMergeSort(data, len);

		printf("-- 변환 후\n");
		Print(data);
	}
	else
		printf("2^n승 길이의 자료만 제공합니다.");
}

int* DivideMergeSort(int d1[], int len) {
	len = len / 2;
	int* d2 = (int*)malloc(sizeof(int) * len);
	int* d3 = (int*)malloc(sizeof(int) * len);

	for (int i = 0; i < len; i++) {
		d2[i] = d1[i];
		d3[i] = d1[i + len];
	}
	MergePrint(d2, len);
	MergePrint(d3, len);
	if (len > 1) {
		d2 = DivideMergeSort(d2, len);
		d3 = DivideMergeSort(d3, len);
	}
	return MergeMergeSort(d2, d3, len * 2);
}

int* MergeMergeSort(int d1[], int d2[], int len) {
	printf("A : "); MergePrint(d1, len / 2);
	printf("B : "); MergePrint(d2, len / 2);
	int* newArray = (int*)malloc(sizeof(int) * len);
	int pd1 = 0, pd2 = 0;
	for (int i = 0; i < len; i++) {
		if (pd1 == len / 2) {
			for (int j = i; j < len - i + i; j++) {
				newArray[j] = d2[pd2];
				pd2++;
			}
			break;
		}
		else if (pd2 == len / 2) {
			for (int j = i; j < len - i + i; j++) {
				newArray[j] = d1[pd1];
				pd1++;
			}
			break;
		}
		else {
			if (d1[pd1] < d2[pd2]) {
				newArray[i] = d1[pd1];
				pd1++;
			}
			else {
				newArray[i] = d2[pd2];
				pd2++;
			}
		}
	}
	printf("A+B : "); MergePrint(newArray, len);
	return newArray;
}

void QuickSort(int data[]) {
	InitArray(data);
	printf("\n-----------------------\n");
	printf("| 퀵 정렬 - QuickSort |\n");
	printf("-----------------------\n\n");

	printf("-- 변환 전\n");
	Print(data);

	printf("-- 변환 중\n");
	int low = 1, high = ARRAY_LENGTH - 1, pivot = 0, len = ARRAY_LENGTH;
	int start = 0;
	QuickPrint(data, start, low, high, pivot, len);
	while (low < high) {
		if (data[low] > data[high]) {
			if (data[pivot] > data[low])
				low++;
			else if (data[pivot] < data[high])
				high--;
			else {
				swap(&data[low], &data[high]);
				low++;
				high--;
			}
		}
		else {
			if (data[pivot] < data[low] && data[pivot] < data[high])
				high--;
			else if (data[pivot] > data[low] && data[pivot] > data[high])
				low++;
			else {
				low++;
				high--;
			}
		}
		QuickPrint(data, start, low, high, pivot, len);
	}
	swap(&data[high], &data[pivot]);
	swap(&high, &pivot);
	QuickPrint(data, start, low, high, pivot, len);

	LeftQuickSort(data, start, pivot - 1, pivot, pivot);
	RightQuickSort(data, pivot + 1, len - 1, len - (pivot + 1), pivot);

	printf("-- 변환 후\n");
	Print(data);
}

int* LeftQuickSort(int data[], int start, int end, int length, int pivot) {
	int s = start, l = start + 1, h = length - (length - pivot) - 1, p = start, len = pivot;
	if (len < 2) {
		if (data[p] > data[h] && p < h) {
			swap(&data[h], &data[p]);
			swap(&h, &p);
		}
		QuickPrint(data, s, l, h, p, len);
		return data;
	}

	QuickPrint(data, s, l, h, p, len);
	while (l < h) {
		if (data[l] > data[h]) {
			if (data[p] > data[l])
				l++;
			else if (data[p] < data[h]) {
				swap(&data[h], &data[l]);
				h--;
			}
			else {
				swap(&data[l], &data[h]);
				l++;
				h--;
			}
		}
		else {
			if (data[p] < data[l] && data[p] < data[h])
				h--;
			else if (data[p] > data[l] && data[p] > data[h])
				l++;
			else {
				l++;
				h--;
			}
		}
		QuickPrint(data, s, l, h, p, len);
	}
	if (data[p] > data[h]) {
		swap(&data[h], &data[p]);
		swap(&h, &p);
		QuickPrint(data, s, l, h, p, len);
	}
	LeftQuickSort(data, s, p - 1, len, p);
	RightQuickSort(data, p + 1, end, len, p);

	return data;
}

int* RightQuickSort(int data[], int start, int end, int length, int pivot) {
	int s2 = start, l2 = s2 + 1, h2 = end, p2 = s2, len2 = length - (pivot + 1);
	if (len2 < 2) {
		if (data[p2] > data[h2] && p2 < h2) {
			swap(&data[h2], &data[p2]);
			swap(&h2, &p2);
		}
		QuickPrint(data, s2, l2, h2, p2, len2);
		return data;
	}

	QuickPrint(data, s2, l2, h2, p2, len2);
	while (l2 < h2) {
		if (data[l2] > data[h2]) {
			if (data[p2] > data[l2])
				l2++;
			else if (data[p2] < data[h2]) {
				swap(&data[h2], &data[l2]);
				h2--;
			}
			else {
				swap(&data[l2], &data[h2]);
				l2++;
				h2--;
			}
		}
		else {
			if (data[p2] < data[l2] && data[p2] < data[h2])
				h2--;
			else if (data[p2] > data[l2] && data[p2] > data[h2])
				l2++;
			else {
				l2++;
				h2--;
			}
		}
		QuickPrint(data, s2, l2, h2, p2, len2);
	}
	if (data[p2] > data[h2]) {
		swap(&data[h2], &data[p2]);
		swap(&h2, &p2);
		QuickPrint(data, s2, l2, h2, p2, len2);
	}
	LeftQuickSort(data, s2, p2 - 1, len2, p2);
	RightQuickSort(data, p2 + 1, end, len2, p2);

	return data;
}

void HeapSort(int data[]) {
	InitArray(data);
	printf("\n----------------------\n");
	printf("| 힙 정렬 - HeapSort |\n");
	printf("----------------------\n\n");
	int temp[ARRAY_LENGTH] = { 0, };

	printf("-- 변환 전\n");
	for (int i = 0; i < ARRAY_LENGTH; i++) {
		InsertHeapSort(temp, data[i]);
		Print(temp);
	}
	int t[ARRAY_LENGTH] = { 0, };
	for (int i = 0; i < ARRAY_LENGTH; i++)
		t[i] = RemoveHeapSort(temp);

	printf("-- 변환 후\n");
	Print(t);
	printf("오류...\n");
}

void InsertHeapSort(int arr[], int data) {	// (k-1)/2
	int index = 0;

	for (index = 0; arr[index]; index++);
	arr[index] = data;
	while (TRUE) {
		if (arr[index] < arr[(index - 1) / 2]) {
			swap(&arr[index], &arr[(index - 1) / 2]);
			index = (index - 1) / 2;
		}
		else break;
	}
}
int RemoveHeapSort(int arr[]) { // (k+1)*2-1 , (k+1)*2
	int index = 0, data = arr[0];

	for (index = 0; index != (ARRAY_LENGTH - 1) && arr[index]; index++);
	arr[0] = arr[index]; arr[index] = 0; index = 0;

	while (TRUE) {
		if ((arr[index] > arr[(index + 1) * 2 - 1] || arr[index] > arr[(index + 1) * 2]) && index < ARRAY_LENGTH - 1) {
			if ((index + 1) * 2 < ARRAY_LENGTH) {
				if (arr[(index + 1) * 2 - 1] < arr[(index + 1) * 2]) {
					swap(&arr[index], &arr[(index + 1) * 2 - 1]);
					index = (index + 1) * 2 - 1;
				}
				else {
					swap(&arr[index], &arr[(index + 1) * 2]);
					index = (index + 1) * 2;
				}
			}
			else break;
		}
		else break;
	}
	Print(arr);

	return data;
}
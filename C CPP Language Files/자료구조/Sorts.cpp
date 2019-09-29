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
void InsertionSort(int[]);
void RadixSort(int[], int);
void MergeSort(int[], int);
void QuickSort(int[]);
void HeapSort(int[]);

void swap(int*, int*);
void Print(int[]);
void MergePrint(int[], int);
void InitArray(int[]);

void RadixInit(List**);						// 기수정렬시 Queue가 들어갈 배열 초기화
int PowerC(int, int);
int* DivideMergeSort(int[], int);			// 병합정렬시 배열을 나눌 때 사용
int* MergeMergeSort(int[], int[], int);		// 병합정렬시 배열을 합칠 때 사용

int main() {
	int data[ARRAY_LENGTH];

	SelectionSort(data);
	BubbleSort(data);
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
		printf("%d ", data[i]);
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

void InsertionSort(int data[]) {
	InitArray(data);
	printf("\n-----------------------------\n");
	printf("| 삽입 정렬 - InsertionSort |\n");
	printf("-----------------------------\n\n");

	printf("-- 변환 전\n");
	Print(data);

	for (int i = 1; i < ARRAY_LENGTH; i++) {
		for (int j = i - 1; j >= 0; j--) {
			if (data[j] > data[j + 1]) {
				swap(&data[j], &data[j + 1]);
			}
			else {
				break;
			}
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
	while (pow != rPow) {
		for (int i = 0; i < ARRAY_LENGTH; i++)
			Enqueue(list[(data[i] % (rPow * 10)) / rPow], data[i]);
		for (int i = 0; i < ARRAY_LENGTH; i++) {
			int cnt = 0;
			while (Data t = Dequeue(list[i]) != -1)
				data[cnt++] = t;
		}
		Print(data);
		rPow++;
	}

	printf("-- 변환 후\n");
	Print(data);
}

void RadixInit(List * list[]) {
	for (int i = 0; i < 10; i++)
		list[i] = (List*)malloc(sizeof(List));
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
}

void HeapSort(int data[]) {
	InitArray(data);
	printf("\n----------------------\n");
	printf("| 힙 정렬 - HeapSort |\n");
	printf("----------------------\n\n");
}
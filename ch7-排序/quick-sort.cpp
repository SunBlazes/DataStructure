#include<iostream>
#include<cstdlib>
#include<time.h>
#include<windows.h>
using namespace std;

typedef int ElementType;

ElementType Middle3(ElementType* A, int L, int R) {
	int Pivot = (R + L) / 2;
	if (A[R] < A[Pivot]) {
		swap(A[R], A[Pivot]);
	}
	if (A[R] < A[L]) {
		swap(A[R], A[L]);
	}
	if (A[L] > A[Pivot]) {
		swap(A[L], A[Pivot]);
	}
	swap(A[Pivot], A[R-1]);
	return A[R - 1];
}

void Quicksort(ElementType* A, int L, int R) {
	if (L == R) return;
	int Pivot = Middle3(A, L, R);
	//1.两个数排序 这里的j或i可能会越界
	//2.三个数已经在Middle3已排序完毕 
	if (R - L + 1 <= 3) return;
	int i = L, j = R - 1;
	while (1) {
		while (A[++i] < Pivot);
		while (A[--j] > Pivot);
		if (i < j) swap(A[i], A[j]);
		else break;
	}
	swap(A[i], A[R - 1]);
//	for (j = L; j <= R; j++) cout<<A[j]<<" ";
//	cout<<endl;
	Quicksort(A, L, i - 1);
	Quicksort(A, i + 1, R);
}

void Quick_Sort(ElementType* A, int Size) {
	Quicksort(A, 0, Size - 1);
}

void Quicksort1(ElementType* A, int Low, int High) {
	if (Low >= High) return;
	int i = Low, j = High + 1;
	ElementType Pivot = A[Low];
	while (i != j) {
		while (i != j && A[--j] >= Pivot);
		A[i] = A[j];
		while (i != j && A[++i] < Pivot);
		A[j] = A[i];
	}
	A[i] = Pivot;
	Quicksort1(A, Low, i - 1);
	Quicksort1(A, i + 1, High);
}

void Quick_Sort1(ElementType* A, int Size) {
	Quicksort1(A, 0, Size - 1);
}

int main () {
//	DWORD startTime, endTime;
	srand(time(NULL));
	ElementType arr[7];
	int i;
	for (i = 0; i < 7; i++) {
		arr[i] = rand() % 10 + 1;
		cout<<arr[i]<<" ";
	}
	cout<<endl;
//	startTime = GetTickCount();
	Quick_Sort1(arr, 7);
//	endTime = GetTickCount();cout<<(double)(endTime - startTime);
	for (i = 0; i < 7; i++) {
		cout<<arr[i]<<" ";
	}
	return 0;
} 

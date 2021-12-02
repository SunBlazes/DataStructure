#include<iostream>
#include<cstdlib>
#include<time.h>
using namespace std;

typedef int ElementType;

void Merge_Sort(ElementType*, int);
void MSort(ElementType*, ElementType*, int, int);
void Merge(ElementType*, ElementType*, int, int, int);

void Merge_Sort1(ElementType*, int);
void MSort1(ElementType*, ElementType*, int, int);
void Merge1(ElementType*, ElementType*, int, int, int);

int main () {
	srand(time(NULL));
	ElementType arr[15];
	int i;
	for (i = 0; i < 15; i++) {
		arr[i] = rand() % 25 + 1;
		cout<<arr[i]<<" ";
	}
	cout<<endl;
	Merge_Sort(arr, 15);
//	Merge_Sort1(arr, 15);
	for (i = 0; i < 15; i++) {
		cout<<arr[i]<<" ";
	}
	return 0;
}

void Merge_Sort1(ElementType* A, int Size) {
	int Length = 1;
	ElementType *Tmp = new ElementType[Size];
	if (Tmp) {
		while (Length < Size) {
			MSort1(A, Tmp, Size, Length);
			Length *= 2;
			MSort1(Tmp, A, Size, Length);
			Length *= 2;
		}
		delete Tmp;
	}
}

void MSort1(ElementType* A, ElementType* Tmp, int Size, int Length) {
	int i;
	for (i = 0; i < Size - 2 * Length; i += 2 * Length) {
		Merge1(A, Tmp, i, i + Length, i + 2 * Length - 1);
	}
	if (i + Length < Size) {
		Merge1(A, Tmp, i, i + Length, Size - 1);
	} else {
		int j;
		for (j = i; j < Size; j++) {
			Tmp[j] = A[j];
		}
	}
}

void Merge1(ElementType* A, ElementType* Tmp, int L, int R, int RightEnd) {
	int LeftEnd = R - 1;
	int ElNumber = RightEnd - L + 1;
	int i = L;
	while (L <= LeftEnd && R <= RightEnd) {
		if (A[L] <= A[R]) {
			Tmp[i++] = A[L++];
		} else {
			Tmp[i++] = A[R++];
		}
	}
	while (L <= LeftEnd) Tmp[i++] = A[L++];
	while (R <= RightEnd) Tmp[i++] = A[R++];
}

void Merge_Sort(ElementType* A, int Size) {
	ElementType *Tmp = new ElementType[Size];
	if (Tmp) {
		MSort(A, Tmp, 0, Size - 1);
		delete Tmp;
	}
}

void MSort(ElementType* A, ElementType* Tmp, int L, int RightEnd) {
	int Center;
	if (RightEnd > L) {
		Center = (RightEnd + L) / 2;
		MSort(A, Tmp, L, Center);
		MSort(A, Tmp, Center + 1, RightEnd);
		Merge(A, Tmp, L, Center + 1, RightEnd);
	}
}

void Merge(ElementType* A, ElementType* Tmp, int L, int R, int RightEnd) {
	int LeftEnd = R - 1;
	int ElNumber = RightEnd - L + 1;
	int i = L;
	while (L <= LeftEnd && R <= RightEnd) {
		// A[L] == A[R]可以保证排序稳定 
		if (A[L] <= A[R]) {
			Tmp[i++] = A[L++];
		} else {
			Tmp[i++] = A[R++];
		}
	}
	while (L <= LeftEnd) Tmp[i++] = A[L++];
	while (R <= RightEnd) Tmp[i++] = A[R++];
	for (i = 0; i < ElNumber; i++, RightEnd--) {
		A[RightEnd] = Tmp[RightEnd];
	}
}

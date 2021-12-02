#include<iostream>
using namespace std;

typedef int ElementType;

int BinarySearch(ElementType *A, ElementType e, int L, int R) {
	int Loca = -1;
	if (L <= R) {
		int Center =  (L + R) / 2;
		if (e == A[Center]) Loca = Center;
		else if (A[Center] > e) Loca = BinarySearch(A, e, L, Center - 1);
		else Loca = BinarySearch(A, e, Center + 1, R);
	}
	return Loca;
}

int Binary_Search(ElementType *A, ElementType e, int Size) {
	int Loca = BinarySearch(A, e, 0, Size - 1);
	return Loca == -1 ? -1 : Loca + 1;
}

int main () {
	ElementType A[] = {2, 4, 5, 7, 15, 17, 25, 30};
	cout<<Binary_Search(A, 2, 8)<<endl;
	return 0;
}

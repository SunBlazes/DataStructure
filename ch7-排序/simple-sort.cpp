#include<iostream>
#include<cstdlib>
#include<time.h>
using namespace std;

typedef int ElementType;

void Bubble_Sort(ElementType*, int);
void Insertion_Sort(ElementType*, int);

int main() {
	srand(time(NULL));
	int arr[10];
	int i;
	for (i = 0; i < 10; i++) {
		arr[i] = rand() % 1000 + 1;
		cout<<arr[i]<<" ";
	}
	cout<<endl;
//	Bubble_Sort(arr, 10);
	Insertion_Sort(arr, 10);
	for (i = 0; i < 10; i++) {
		cout<<arr[i]<<" ";
	}
	return 0;
} 

void Bubble_Sort(ElementType* arr_sort, int count) {
	int i, j;
	for (i = count - 1; i >= 0; i--) {
		bool flag = false;
		for (j = 0; j < i; j++) {
			if (arr_sort[j] > arr_sort[j + 1]) {
				swap(arr_sort[j], arr_sort[j + 1]);
				flag = true;
			}
		}
		if (!flag) return;
	}
}

void Insertion_Sort(ElementType* arr_sort, int count) {
	int i, j;
	for (i = 1; i < count; i++) {
		int tmp = arr_sort[i];
		for (j = i; j > 0 && tmp < arr_sort[j - 1]; j--) {
			arr_sort[j] = arr_sort[j - 1];
		}
		arr_sort[j] = tmp;
	}
}

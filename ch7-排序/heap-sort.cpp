#include<iostream>
#include<cstdlib>
#include<time.h>
using namespace std;

typedef int ElementType;

void BuildMaxHeap(ElementType*, int);
void SiftDown(ElementType*, int, int);
void Heap_Sort(ElementType*, int);
bool Is_MaxHeap(ElementType*, int, int);

int main() {
	srand(time(NULL));
	ElementType arr[6];
	int i;
	for (i = 0; i < 6; i++) {
//		arr[i] = rand() % 100 + 1;
//		cout<<arr[i]<<" ";
		cin>>arr[i];
	}
	cout<<endl;
	cout<<Is_MaxHeap(arr, 6, 0)<<endl;
//	Heap_Sort(arr, 6);
//	for (i = 0; i < 6; i++) cout<<arr[i]<<" ";
//	cout<<endl;
}

bool Is_MaxHeap(ElementType* A, int Size, int Loca) {
	// 只有一个结点肯定是最大堆 
	if (Loca * 2 + 1 >= Size) return true;
	// 左右子树是否为最大堆 
	bool flag = Is_MaxHeap(A, Size, 2 * Loca + 1) && 
		Is_MaxHeap(A, Size, 2 * Loca + 2);
	int Son = 2 * Loca + 1;
	// 左孩子或者右孩子(若存在)比双亲结点还大，那么肯定不是最大堆 
	if (A[Loca] < A[Son] || Son + 1 < Size && A[Loca] < A[Son + 1]) 
		return false;
	// 若左右孩子包括双亲结点满足最大堆，则还需要左右子树是否也满足最大堆 
	else 
		return flag;
}

void Heap_Sort(ElementType* arr, int size) {
	// 总体思路: 先调整为最大堆，然后进行循环
	// 每次交换第一个元素和最大堆此时未排序好的最后一个元素
	// 交换后再调整为最大堆，然后重复此步骤 
	int i;
	BuildMaxHeap(arr, size);
	for (i = 0; i < size; i++) {
		swap(arr[0], arr[size - i - 1]);
		SiftDown(arr, 0, size - i - 1);
	} 
}

void BuildMaxHeap(ElementType* arr, int size) {
	int Parent = (size - 2) / 2;
	for (; Parent >= 0; Parent--) {
		SiftDown(arr, Parent, size);
	}
}

void SiftDown(ElementType* arr, int Parent, int size) {
	int Son = Parent * 2 + 1, tmp = arr[Parent];
	while (Son < size) {
		if (Son != size - 1 && arr[Son] < arr[Son + 1]) {
			Son++;
		}
		if (tmp >= arr[Son]) break;
		arr[Parent] = arr[Son];
		Parent = Son;
		Son = Son * 2 + 1;
	}
	arr[Parent] = tmp;
}

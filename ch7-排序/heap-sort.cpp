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
	// ֻ��һ�����϶������� 
	if (Loca * 2 + 1 >= Size) return true;
	// ���������Ƿ�Ϊ���� 
	bool flag = Is_MaxHeap(A, Size, 2 * Loca + 1) && 
		Is_MaxHeap(A, Size, 2 * Loca + 2);
	int Son = 2 * Loca + 1;
	// ���ӻ����Һ���(������)��˫�׽�㻹����ô�϶��������� 
	if (A[Loca] < A[Son] || Son + 1 < Size && A[Loca] < A[Son + 1]) 
		return false;
	// �����Һ��Ӱ���˫�׽���������ѣ�����Ҫ���������Ƿ�Ҳ�������� 
	else 
		return flag;
}

void Heap_Sort(ElementType* arr, int size) {
	// ����˼·: �ȵ���Ϊ���ѣ�Ȼ�����ѭ��
	// ÿ�ν�����һ��Ԫ�غ����Ѵ�ʱδ����õ����һ��Ԫ��
	// �������ٵ���Ϊ���ѣ�Ȼ���ظ��˲��� 
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

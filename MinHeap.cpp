#include<iostream>
#define MaxSize 100000
using namespace std;
typedef int ElementType;
typedef struct {
	ElementType *elements;
	int size;
} *MinHeap, HeapStruct;

MinHeap Heap_Init() {
	MinHeap H = new(HeapStruct);
	H->elements = new ElementType[MaxSize];
	H->size = 0;
	H->elements[0] = 1<<31; // ·ÅÖÃÉÚ±ø
	return H; 
}

void Heap_Insert(MinHeap H, ElementType e) {
	H->size++;
	int Child = H->size, Parent = H->size / 2;
	for (; e < H->elements[Parent]; Child = Parent, Parent /= 2) {
		H->elements[Child] = H->elements[Parent];
	}
	H->elements[Child] = e;
}

void Heap_DeleteMin(MinHeap H) {
	ElementType temp = H->elements[H->size--];
	int Parent = 1;
	while (Parent * 2 <= H->size) {
		int Child = Parent * 2;
		if (Child != H->size) {
			if (H->elements[Child] > H->elements[Child + 1]) {
				Child++;
			}
		}
		if (temp <= H->elements[Child]) break;
		H->elements[Parent] = H->elements[Child];
		Parent *= 2;
	}
	H->elements[Parent] = temp;
}

int main () {
	MinHeap H = Heap_Init();
	int i;
	for (i = 8; i >= 1; i--) Heap_Insert(H, i);
	for (i = 1; i <= H->size; i++) cout<<(H->elements[i])<<" ";
	cout<<endl;
	Heap_DeleteMin(H);
	for (i = 1; i <= H->size; i++) cout<<(H->elements[i])<<" ";
	cout<<endl;
	return 0;
}

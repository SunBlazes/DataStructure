#include<iostream>
#define MaxSize 100000
using namespace std;
typedef int ElementType;
typedef struct {
	ElementType *elements;
	int size;
} *MaxHeap, HeapStruct;

bool Heap_isEmpty(MaxHeap H) {
	return H->size == 0;
}

MaxHeap Heap_Init() {
	MaxHeap h = new(HeapStruct);
	h->elements = new ElementType[MaxSize];
	h->size = 0;
	// 哨兵 方便插入，这里规定最大堆的起始位置为1，如果不设置哨兵
	// 假如插入的值大于根结点的值，插入的比较一直会到0号位置，
	// 最后在0号位置放置插入的值，由于e=H[0]，那跳出循环，
	// 所以需要一个很大的值，能在比较0号位置的值时能跳出来 
	h->elements[0] = ((unsigned int)-1>>1) - 1;
	return h;
}
int count = 0;
void Heap_Insert(MaxHeap H, ElementType e) {
	// 依次把插入的值和插入位置的祖先结点的值进行比较
	// 如果插入的值大于任何一个祖先结点的值，那么祖先结点下移
	// 重复操作直到碰到一个祖先结点比它的时候跳出循环 
	int Parent = (H->size + 1) / 2, Child = H->size + 1;
	for (; e > H->elements[Parent]; Child = Parent, Parent = Parent / 2) {
		H->elements[Child] = H->elements[Parent];
		count++;
	}
	H->size++;
	H->elements[Child] = e;
}

void Heap_DeleteMax(MaxHeap H) {
	// 先保持完全二叉树的形状再步步变成最大堆 
	ElementType temp = H->elements[H->size--]; //取出最后的值 放到合适的位置  
	int Parent = 1;
	// 由于最大堆是完全二叉树，知道Parent，可以得知左孩子的位置，来判断是否已经循环到最后 
	while (Parent * 2 <= H->size) {
		int Child = Parent * 2;
		// 取出孩子结点中大的那个结点放置Parent位置 
		if (Child + 1 <= H->size) {
			if (H->elements[Child] < 
				H->elements[Child + 1]) 
			Child++;
		}
		// 这里有两种情况 
		// 1.这个孩子结点刚好是temp 
		// 2.temp比另一边的Child都大，
		//  又因为最后要把temp放置Parent位置上，这里不跳出
		//  那么Parent=Child，会把temp放置到此时的Child的下方
		//  不符合最大堆中（根结点大于左右子树的所有值） 
		if (temp >= H->elements[Child]) break;
		H->elements[Parent] = H->elements[Child];
		Parent = Child;
	} 
	H->elements[Parent] = temp;
}
 
void Transform2MaxHeap(MaxHeap H, int loca) {
	if (loca * 2 > H->size) return;
	Transform2MaxHeap(H, loca * 2);
	Transform2MaxHeap(H, loca * 2 + 1);
	int left = loca * 2, right = loca * 2 + 1;
	if (right <= H->size) {
		if (H->elements[left] > H->elements[right]) {
			if (H->elements[left] < H->elements[loca]) return;
			count++;
			ElementType temp = H->elements[left];
			H->elements[left] = H->elements[loca];
			H->elements[loca] = temp;
			Transform2MaxHeap(H, left);
		} else {
			if (H->elements[right] < H->elements[loca]) return;
			count++;
			ElementType temp = H->elements[right];
			H->elements[right] = H->elements[loca];
			H->elements[loca] = temp;
			Transform2MaxHeap(H, right);
		}
	} else {
		if (H->elements[left] < H->elements[loca]) return;
		count++;
		ElementType temp = H->elements[left];
		H->elements[left] = H->elements[loca];
		H->elements[loca] = temp;
		Transform2MaxHeap(H, left);
	}
} 

main() {
	MaxHeap H = Heap_Init();
	/* ElementType e;
	cin>>e;
	while (e != -1) {
		Heap_Insert(H, e);
		int i;
		for (i = 1; i <= H->size; i++) cout<<(H->elements[i])<<" ";
		cout<<endl;
		cin>>e;
	};
	Heap_DeleteMax(H);*/
	int i;
	for (i = 1; i <= 999; i++) H->elements[i] = i;
	H->size = 999;
	Transform2MaxHeap(H, 1);
	for (i = 1; i <= H->size; i++) cout<<(H->elements[i])<<" ";
	cout<<endl;
	cout<<"count: "<<count;
	return 0;
}

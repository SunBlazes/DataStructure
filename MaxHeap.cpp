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
	// �ڱ� ������룬����涨���ѵ���ʼλ��Ϊ1������������ڱ�
	// ��������ֵ���ڸ�����ֵ������ıȽ�һֱ�ᵽ0��λ�ã�
	// �����0��λ�÷��ò����ֵ������e=H[0]��������ѭ����
	// ������Ҫһ���ܴ��ֵ�����ڱȽ�0��λ�õ�ֵʱ�������� 
	h->elements[0] = ((unsigned int)-1>>1) - 1;
	return h;
}
int count = 0;
void Heap_Insert(MaxHeap H, ElementType e) {
	// ���ΰѲ����ֵ�Ͳ���λ�õ����Ƚ���ֵ���бȽ�
	// ��������ֵ�����κ�һ�����Ƚ���ֵ����ô���Ƚ������
	// �ظ�����ֱ������һ�����Ƚ�������ʱ������ѭ�� 
	int Parent = (H->size + 1) / 2, Child = H->size + 1;
	for (; e > H->elements[Parent]; Child = Parent, Parent = Parent / 2) {
		H->elements[Child] = H->elements[Parent];
		count++;
	}
	H->size++;
	H->elements[Child] = e;
}

void Heap_DeleteMax(MaxHeap H) {
	// �ȱ�����ȫ����������״�ٲ���������� 
	ElementType temp = H->elements[H->size--]; //ȡ������ֵ �ŵ����ʵ�λ��  
	int Parent = 1;
	// ������������ȫ��������֪��Parent�����Ե�֪���ӵ�λ�ã����ж��Ƿ��Ѿ�ѭ������� 
	while (Parent * 2 <= H->size) {
		int Child = Parent * 2;
		// ȡ�����ӽ���д���Ǹ�������Parentλ�� 
		if (Child + 1 <= H->size) {
			if (H->elements[Child] < 
				H->elements[Child + 1]) 
			Child++;
		}
		// ������������� 
		// 1.������ӽ��պ���temp 
		// 2.temp����һ�ߵ�Child����
		//  ����Ϊ���Ҫ��temp����Parentλ���ϣ����ﲻ����
		//  ��ôParent=Child�����temp���õ���ʱ��Child���·�
		//  �����������У�����������������������ֵ�� 
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
	count++;
	if (right <= H->size) {
		if (H->elements[left] > H->elements[right]) {
			if (H->elements[left] < H->elements[loca]) return;
			ElementType temp = H->elements[left];
			H->elements[left] = H->elements[loca];
			H->elements[loca] = temp;
			Transform2MaxHeap(H, left);
		} else {
			if (H->elements[right] < H->elements[loca]) return;
			ElementType temp = H->elements[right];
			H->elements[right] = H->elements[loca];
			H->elements[loca] = temp;
			Transform2MaxHeap(H, right);
		}
	} else {
		if (H->elements[left] < H->elements[loca]) return;
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
	for (i = 1; i <= 100; i++) H->elements[i] = i;
	H->size = 100;
	Transform2MaxHeap(H, 1);
	for (i = 1; i <= H->size; i++) cout<<(H->elements[i])<<" ";
	cout<<endl;
	cout<<"count: "<<count;
	return 0;
}

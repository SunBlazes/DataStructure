#include<iostream>
#include<cstdlib>
#include<time.h>
using namespace std;

typedef int KeyType;

typedef struct {
	KeyType key;
} Item;

typedef Item ElementType;

void Table_Sort(ElementType* A, KeyType* Table, int Size) {
	int i, j;
	for (i = 1; i < Size; i++) {
		int Key = A[Table[i]].key;
		int tmp = Table[i];
		for (j = i - 1; j >= 0; j--) {
			if (A[Table[j]].key > Key) {
				Table[j + 1] = Table[j];
			} else {
				break;
			}
		}
		Table[j + 1] = tmp;
	} 
}

void Physical_Sort(ElementType* A, KeyType* Table, int Size) {
	int i = 0;
	while (1) {
		int j;
		ElementType Tmp = A[i]; // 缓存环开始的第一个值 
		while (1) {
			j = Table[i];// 缓存Table[i]的值，为下次循环的i提供位置 
			// 通过表排序会生成几个环
			// j == Table[j]意味着有环 
			// 1.j这边的值不能用了，会重复
			// 2.j这个序号也不能用，会重复
			// 3.有环，那么得破环 
			if (j == Table[j]) {
				Table[i] = i;
				A[i] = Tmp;
				break;
			} else {
				A[i] = A[j];
				Table[i] = i;
			}
			i = j;
		}
		// 每次找到环开始的第一个点 
		for (i = 0; i < Size && Table[i] == i; i++);
		// 说明待排数组里没有环了，意味着排序结束 
		if (i == Size) break;
	}
}

int main() {
	srand(time(NULL));
	ElementType arr[15];
	KeyType Table[15];
	int i;
	for (i = 0; i < 15; i++) {
		arr[i].key = rand() % 1000 + 1;
		Table[i] = i;
		cout<<arr[i].key<<"\t";
	}
	cout<<endl;
	Table_Sort(arr, Table, 15);
	for (i = 0; i < 15; i++) {
		cout<<Table[i]<<"\t";
	}
	cout<<endl;
	for (i = 0; i < 15; i++) {
		cout<<arr[Table[i]].key<<"\t";
	}
	cout<<endl;
	Physical_Sort(arr, Table, 15);
	for (i = 0; i < 15; i++) {
		cout<<arr[i].key<<"\t";
	}
} 

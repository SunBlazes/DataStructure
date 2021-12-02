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
		ElementType Tmp = A[i]; // ���滷��ʼ�ĵ�һ��ֵ 
		while (1) {
			j = Table[i];// ����Table[i]��ֵ��Ϊ�´�ѭ����i�ṩλ�� 
			// ͨ������������ɼ�����
			// j == Table[j]��ζ���л� 
			// 1.j��ߵ�ֵ�������ˣ����ظ�
			// 2.j������Ҳ�����ã����ظ�
			// 3.�л�����ô���ƻ� 
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
		// ÿ���ҵ�����ʼ�ĵ�һ���� 
		for (i = 0; i < Size && Table[i] == i; i++);
		// ˵������������û�л��ˣ���ζ��������� 
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

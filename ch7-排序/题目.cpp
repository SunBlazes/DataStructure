#include<iostream>
#include<cstdlib>
#include<time.h>
#include<math.h>
using namespace std;

typedef int ElementType;

void Double_Bubble_Sort(ElementType* A, int Size) {
	int Low = 0, High = Size - 1;
	bool is_Positive = true;
	while (Low != High) {
		int i;
		if (is_Positive) {
			ElementType _max = A[Low];
			int Loca = Low;
			for (i = Low + 1; i <= High; i++) {
				if (A[i] < _max) {
					swap(A[i], A[Loca]);
				} else {
					_max = A[i];
				}
				Loca = i;
			}
			High--;
		} else {
			ElementType _min = A[High];
			int Loca = High;
			for (i = High - 1; i >= 0; i--) {
				if (A[i] > _min) {
					swap(A[i], A[Loca]);
				} else {
					_min = A[i];
				}
				Loca = i;
			}
			Low++;
		}
		is_Positive = !is_Positive;
	}
} 

// 把所有奇数移动到所有偶数前面 
void Move_Odd_Even_Worst(ElementType* A, int Size) {
	int count[2] = {0}, i;
	ElementType Tmp[Size];
	for (i = 0; i < Size; i++) {
		count[!(A[i] % 2)]++;
	}
	count[1] += count[0];
	for (i = Size - 1; i >= 0; i--) {
		Tmp[--count[!(A[i] % 2)]] = A[i];
	}
	for (i = 0; i < Size; i++) {
		A[i] = Tmp[i];
	}
}

void QuicksortRandom(ElementType* A, int L, int R) {
	if (L >= R) return;
	int Low = L, High = R + 1;
	int Size = R - L + 1;
	int Pivot_Loca = rand() % Size + L;
	ElementType Pivot = A[Pivot_Loca];
	swap(A[L], A[Pivot_Loca]);
	while (Low != High) {
		while (Low != High && A[--High] >= Pivot);
		A[Low] = A[High];
		while (Low != High && A[++Low] < Pivot);
		A[High] = A[Low];
	}
	A[High] = Pivot;
	QuicksortRandom(A, L, High - 1);
	QuicksortRandom(A, High + 1, R);
}

// 随机选择当前数组的一个元素作为Pivot的快速排序 
void Quick_Sort_Random(ElementType* A, int Size) {
	QuicksortRandom(A, 0, Size - 1);
}

// 假如数组按照从小到大排序，找到第k个小的元素
// 三种情况
// 1.j==-1或者此时Tmp未填满并且Tmp最后的元素是小于待加入元素A[i]，此时可以直接加入
// 2.因为这里是找第几小，所以当Tmp被填满时，若待加入元素A[i]大于Tmp最大元素时，可以忽略
// 3.A[i]小于Tmp最大的元素，此时Tmp比A[i]大的元素后移(溢出的可以舍弃) 
void Find_El_MinLoca(ElementType* A, int Size, int k) {
	ElementType Tmp[k + 1];
	int i, j = -1, p;
	for (i = 0; i < Size; i++) {
		if (j == -1 || j < k && A[i] > Tmp[j]) {
			Tmp[++j] = A[i];
		} else if (j == k && A[i] > Tmp[j]){
			continue;
		} else {
			for (p = j; p >= 0 && Tmp[p] > A[i]; p--) {
				if (p < k) {
					Tmp[p + 1] = Tmp[p];
				}
			}
			Tmp[p + 1] = A[i];
			if (j < k) j++;
		}
	}
	cout<<Tmp[k]<<endl;
}

// 荷兰国旗问题 以红(0)白(1)蓝(2)排序 
void DutchFlags(ElementType* A, int Size) {
	ElementType Tmp[Size], count[3] = {0};
	int i;
	for (i = 0; i < Size; i++) {
		count[A[i]]++; 
	}
	for (i = 1; i < 3; i++) {
		count[i] += count[i - 1];
	}
	for (i = Size - 1; i >= 0; i--) {
		Tmp[--count[A[i]]] = A[i]; 
	}
	for (i = 0; i < Size; i++) {
		A[i] = Tmp[i]; 
	}
}

void DutchFlags1(ElementType* A, int Size) {
	int m = -1, n = Size + 1;
	int i;
	for (i = 0; i < Size; i++) {
		if (A[i] == 0) {
			swap(A[++m], A[i]);
		} else if (A[i] == 2) {
			swap(A[--n], A[i]);
		}
	}
} 

ElementType C_2016_408(ElementType* A, int Size) {
	
}

int main () {
	srand(time(NULL));
//	ElementType A[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
//	ElementType A[] = {3, 2, 7, 6, 6, 9, 1, 4, 8};
//	ElementType A[] = {0, 1, 1, 2, 0, 2, 2, 0, 1};
	ElementType A[20];
	int i;
	for (i = 0; i < 20; i++) {
		A[i] = rand() % 100;
		cout<<A[i]<<" ";
	}
	cout<<endl;
//	Double_Bubble_Sort(A, 20);
//	Move_Odd_Even_Worst(A, 20);
//	Find_El_MinLoca(A, 20, 8);
//	Quick_Sort_Random(A, 20);
//	DutchFlags(A, 20);
	C_2016_408(A, 20);
//	for (i = 0; i < 9; i++) {
//		cout<<A[i]<<" ";
//	}
	return 0;
} 

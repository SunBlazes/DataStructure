#include<iostream>
#include<cstdlib>
#include<time.h>
#include<math.h>
using namespace std;

// 返回待排数组的最大位数 
int MaxBit(int* A, int n) {
	int bit = 1;
	int i = 0;
	int maxdata = 10;
	while (i <= n - 1) {
		if (A[i] >= maxdata) {
			bit++;
			maxdata *= 10;
		}
		i++;
	}
	return bit;
}

// 基数排序
void Radix_Sort(int* A, int n) {
	int max_bit = MaxBit(A, n);
	int count[n] = {0};
	int tmp[n];
	int i, j, k, radix = 1;
	for (i = 1; i <= max_bit; i++) {
		for (j = 0; j < n; j++) {
			count[j] = 0;
		}
		for (j = 0; j < n; j++) {
			k = A[j] / radix % 10;
			count[k]++;
		}
		for (j = 1; j < n; j++) {
			count[j] += count[j - 1]; 
		}
		for (j = n - 1; j >= 0; j--) {
			k = A[j] / radix % 10;
			tmp[count[k] - 1] = A[j];
			count[k]--;
		}
		for (j = 0; j < n; j++) {
			A[j] = tmp[j];
		}
		radix *= 10;
	}
	for (j = 0; j < n; j++) {
		cout<<A[j]<<" ";
	}
}

int main () {
//	srand(time(NULL));
	int array[10] = {73,22,93,43,55,14,28,65,39,81};
	Radix_Sort(array, 10);
//	printArray(array,10);
	return 0; 
}

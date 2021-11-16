#include<stdio.h>
#include<memory.h> 

// ¶þ·Ö·¨
int searchForLoca(int a[], int start, int end, int v) {
	int middleIndex = (end - start) / 2 + start;
	if (v == a[middleIndex]) return middleIndex;
	if (start >= end) {
		printf("start: %d, end: %d\n", start, end);
		return -1;
	}
	if (v > a[middleIndex]) {
		searchForLoca(a, middleIndex + 1, end, v);
	} else {
		searchForLoca(a, start, middleIndex - 1, v);
	};
}

int main() {
//	int arr[] = {2,4,6,8,10,12,14,16,18,20};
//	int searchV = 99, len = sizeof(arr) / sizeof(arr[0]);
//	printf("%d", searchForLoca(arr, 0, len - 1, 2));
	int a[] = {4, 2, 6, 8, 5, 1, 3, 7},
		b[10];
	memcpy(b, a + 5, 3 * sizeof(int));
	int i = 0;
	for (; i < 3; i++) {
		printf("%d ", b[i]);
	}
} 

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#define MaxSize 100

typedef struct {
	int* array;
	int length;
	int size;
} SqList;

int listInsert(SqList*, int, int);
void initList(SqList*);
void printList(SqList*);
int listDelete(SqList*, int, int*);
int minEleLoca(SqList*);
void listReverse(SqList*);
void listDeleteAll(SqList*, int);
void listDeleteRepeat_worst(SqList*);
void ch2_sqlist_9(SqList*, int);
int searchForLoca(int[], int, int, int, int*);
void exchangeLatter(SqList*, int);
void ch2_sqlist_10_worst(SqList*);

// ch2_sqlist_10_better
void Reverse(int R[], int from, int to) {
	int i, temp;
	for (i = 0; i< (to - from + 1) / 2; i++) {
		temp = R[from + i];
		R[from + i] = R[to - i];
		R[to - i] = temp;
	}
}
void Converse(int R[], int n, int p) {
	Reverse(R, 0, p-1);
	Reverse(R, p, n-1);
	Reverse(R, 0, n-1);
}

int main() {
	srand((unsigned)time(NULL));
	SqList sqlist;
	initList(&sqlist);
	int i = 1, e, j;
	while(i != 11) {
		listInsert(&sqlist, i++, j++);
	}
	printList(&sqlist);
//	listReverse(&sqlist);
//	listDeleteAll(&sqlist, 5);
//	listDeleteRepeat_worst(&sqlist);
//	ch2_sqlist_9(&sqlist, 21);
//	ch2_sqlist_10_worst(&sqlist);
//	Converse(sqlist.array, sqlist.length, 5);
	printList(&sqlist);
//	printf("%d", minEleLoca(&sqlist));
	return 0;
} 

void ch2_sqlist_10_worst(SqList* list) {
	int p, i, j, temp;
	scanf("%d", &p);
	for (i = 0, j = p; j < list->length; j++, i++) {
		temp = list->array[i];
		list->array[i] = list->array[j];
		list->array[j] = temp;
	}
}

int searchForLoca(int a[], int start, int end, int v, int* stopLoca) {
	int middleIndex = (end - start) / 2 + start;
	if (v == a[middleIndex]) return middleIndex;
	if (end <= start) {
		*stopLoca = start;
		return -1;
	}
	if (v > a[middleIndex]) {
		searchForLoca(a, middleIndex + 1, end, v, stopLoca);
	} else {
		searchForLoca(a, start, middleIndex - 1, v, stopLoca);
	};
}

void ch2_sqlist_9(SqList *list, int v) {
	int stopLoca = -1;
	int loca = searchForLoca(list->array, 0, list->length - 1, v, &stopLoca);
	if (loca != -1) {
		exchangeLatter(list, loca);
	} else {
		printf("loca: %d\n", stopLoca);
		listInsert(list, stopLoca + 1, v);
	}
}

void exchangeLatter(SqList *list, int loca) {
	if (list->length - 1 <= loca) return;
	int temp = list->array[loca];
	list->array[loca] = list->array[loca + 1];
	list->array[loca + 1] = temp;
}

void listDeleteRepeat_worst(SqList *list) {
	int i, j, e;
	for (i = 0; i < list->length; i++) {
		for (j = i + 1; j < list->length; j++) {
			if (list->array[i] == list->array[j]) {
				listDelete(list, j + 1, &e);
				j--;
			}
		}
	}
}

void listDeleteAll(SqList* list, int v) {
	int i = 0, e;
	while (1) {
		if (list->array[i] == v) {
			listDelete(list, i + 1, &e);
		} else {
			i++;
		}
		if (i > list->length) break;
	}
}

void listReverse(SqList* list) {
	int i = 0, temp;
	while (i < list->length / 2) {
		temp = list->array[i];
		list->array[i] = list->array[list->length - 1 - i];
		list->array[list->length - 1 - i] = temp;
		i++;
	}
}

int minEleLoca(SqList* list) {
	int min = list->array[0], i = 1, minLoca = 1;
	for (; i < list->length; i++) {
		if (min > list->array[i]) {
			min = list->array[i];
			minLoca = i;
		}
	} 
	return minLoca + 1;
}

int listDelete(SqList* list, int i, int* e) {
	if (i < 1 || i > list->length) return 0;
	int j;
	*e = list->array[i - 1];
	for (j = i - 1; j <list->length - 1; j++) {
		list->array[j] = list->array[j + 1]; 
	}
	list->array[j] = 0;
	list->length--;
	return 1;
}

void printList(SqList* list) {
	int i;
	for (i = 0; i < list->length; i++) {
		printf("%d ", list->array[i]);
	}
	printf("\n");
}

int listInsert(SqList *list, int i, int value) {
	if (i < 1 || i > list->length + 1 || i > list->size - 1) {
		return 0;
	}
	int j;
	for (j = list->length; j >= i; j--) {
		list->array[j] = list->array[j - 1];
	}
	list->array[i - 1] = value;
	list->length++;
	return 1;
}

void initList(SqList* list) {
	list->array = (int*)malloc(sizeof(int) * MaxSize);
	list->length = 0;
	list->size = MaxSize;
}

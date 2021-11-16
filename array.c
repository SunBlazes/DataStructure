#include<stdio.h>
#include<stdlib.h>
#include<string.h>

const BLOCK_SIZE = 20;

typedef struct {
	int* array;
	int size;
} Array;

Array array_create(int init_size) {
	Array a;
	a.size = init_size;
	a.array = (int*)malloc(sizeof(int) * a.size);
	return a;
}

void array_free(Array* a) {
	free(a->array);
	a->array = NULL;
	a->size = 0;
}

int array_size(const Array* a) {
	return a->size;
}

void array_inflate(Array *a, int more_size) {
	int init_size = a->size;
	int *new_arr = (int*)malloc(sizeof(int) * (init_size + more_size));
	memcpy(new_arr, a->array, init_size);
	free(a->array);
	a->array = new_arr;
	a->size += more_size;
}

int* array_at(Array *a, int index) {
	if (index >= a->size) {
		array_inflate(a, (index / BLOCK_SIZE + 1) * BLOCK_SIZE- a->size);
	}
	return &(a->array[index]);
}

int main() {
	Array a = array_create(100);
	a.array[0] = 5;
	printf("%d\n", a.array[0]);
//	array_free(&a);
//	printf("%d", a.array);
	printf("%d\n", array_size(&a));
	printf("%d\n", *array_at(&a, 0));
	array_inflate(&a, 10);
	printf("%d\n", array_size(&a));
	printf("%d\n", *array_at(&a, 0));
	return 0;
} 

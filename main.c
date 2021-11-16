#include<stdio.h>
#include<stdlib.h>
#include "max.h"
#include "min.h"

int main() {
	printf("%f", useMax(5, gAll));
	int a = 5;
	int *p = (int*)malloc(sizeof(int));
	p = &a;
	printf("%d", *p);
}

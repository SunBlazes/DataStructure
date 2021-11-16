#include "circle-single-linked-list.h"

void test() {
	CLinkedList L;
	InitList(&L);
	List_TailInsert(L);
	List_EmptyByClearMin(&L);
	Output(L);
}

int main() {
	test();
	return 0;
}


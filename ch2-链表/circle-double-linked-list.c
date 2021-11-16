#include "circle-double-linked-list.h"

void test() {
	CDLinkedList L;
	InitList(&L);
//	List_TailInsert(L);
	List_headInsert(L);
//	Output(L);
	ReOutput(L);
//	printf("%d", List_IsSymmetric(L));
}

void test1() {
	CDLinkedList L1, L2;
	InitList(&L1);
	InitList(&L2);
	List_TailInsert(L1);
	List_TailInsert(L2);
	CDLinkedList L = List_Concat(L1, L2);
	Output(L);
	ReOutput(L);
}

int main() {
	test();
//	test1();
	return 0;
}

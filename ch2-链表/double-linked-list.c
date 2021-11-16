#include "double-linked-list.h"

void test() {
	DLinkedList L;
	InitList(&L);
	List_TailInsert(L);
	Output(L);
//	Locate(L, 7);
//	Locate(L, 7);
	Locate(L, 5);
	Output(L);
	Locate(L, 5);
//	Locate(L, 5);
	Output(L);
}

int main() {
	test();
	return 0;
}

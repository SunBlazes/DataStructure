#include "single-linked-list.h"

void test() {
	LinkedList list;
	InitList(&list);
	List_TailInsert(list);
//	List_ReOutput(list, 1);
//	Output(list);
//	List_SplitByOddEven(list);
//	List_DeleteRe(list);
	
//	List_DeleteAll(list, 5);
//	List_DeleteMin(list);
//	List_Reverse(list);
	List_Increment(list);
//	List_FindFromEndByLoca(list, 1);
	Output(list);
//	ch2_2015_408(list);
	Output(list);
}

void test2() {
	LinkedList L1, L2;
	InitList(&L1);
	InitList(&L2);
	List_TailInsert(L1);
	List_TailInsert(L2);
	Output(L1);
	Output(L2);
//	Output(List_FindMutualNode(L1, L2));
//	Output(List_Mutual(L1, L2));
//	printf("%d", List_IsSubsquence(L1, L2));
}

int main() {
	test();
//	test2();
	return 0;
}

// 不带头指针的判空 
/* int Empty(LinkedList list) {
	return list == NULL;
} */ 

// 不带头指针的头插法
/* LinkedList  List_HeadInsert(LinkedList L, ElemType e) {
	LNode *head_node = NULL;
	ElemType data;
	scanf("%d", &data);
	while (data != -1) {
		LNode* node = (LNode*)malloc(sizeof(LNode));
		node->data = e;
		node->next = head_node;
		head_node = node;
		scanf("%d", &data);
	}
	return L;
} */

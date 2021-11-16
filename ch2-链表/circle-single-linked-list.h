#include<stdio.h>
#include<stdlib.h>
#define ElemType int

typedef struct _node {
	ElemType data;
	struct _node *next;
} CLNode, *CLinkedList; 

CLinkedList InitList(CLinkedList*);
CLinkedList List_TailInsert(CLinkedList);
void Output(CLinkedList);
void List_EmptyByClearMin(CLinkedList*); 

void List_EmptyByClearMin(CLinkedList *L) {
	CLNode *min, *p, *prev;
	if (!min) return;
	while ((*L)->next) {
		min = (*L)->next;
		prev = *L;
		for (p = (*L)->next; p->next && p->next != *L; p = p->next) {
			if (p->next->data < min->data) {
				min = p->next;
				prev = p;
			}
		}
		if (p->next == *L) {
			p->next = NULL;
		}
		prev->next = min->next;
		free(min);
		min = NULL;
	}
	free(*L);
	*L = NULL;
}

void Output(CLinkedList L) {
	if (!L) return;
	CLNode *p = L;
	for (p = p->next; p && p != L; p = p->next) {
		printf("%d ", p->data);
	}
	printf("\n");
}

CLinkedList InitList(CLinkedList* L) {
	*L = (CLNode*)malloc(sizeof(CLNode));
	(*L)->next = *L;
	return *L;
}

CLinkedList List_TailInsert(CLinkedList L) {
	ElemType e;
	CLNode *pre = L;
	scanf("%d", &e);
	while (e != -1) {
		CLNode *node = (CLNode*)malloc(sizeof(CLNode));
		node->data = e;
		node->next = L;
		pre->next = node;
		pre = node;
		scanf("%d", &e);
	}
	return L;
}



#include<stdio.h>
#include<stdlib.h>
#define ElemType int

typedef struct _node {
	ElemType data;
	struct _node *next;
	struct _node *prev;
} CDLNode, *CDLinkedList; 

CDLinkedList InitList(CDLinkedList*);
CDLinkedList List_TailInsert(CDLinkedList);
CDLinkedList List_headInsert(CDLinkedList);
void Output(CDLinkedList);
void ReOutput(CDLinkedList);
int List_IsSymmetric(CDLinkedList);
CDLinkedList List_Concat(CDLinkedList, CDLinkedList);

CDLinkedList List_headInsert(CDLinkedList L) {
	CDLNode *s;
	ElemType x;
	scanf("%d", &x);
	while (x != 9999) {
		s = (CDLNode*)malloc(sizeof(CDLNode));
		s->data = x;
		s->next = L->next;
		if (L->next != L) {
			L->next->prev = s;
		} else {
			L->prev = s;
		}
		s->prev = L;
		L->next = s;
		scanf("%d", &x);
	}
	return L;
}

CDLinkedList List_Concat(CDLinkedList h1, CDLinkedList h2) {
	if (h2->next == NULL) return h1;
	CDLNode *tail_2 = h2->prev, *tail_1 = h1->prev;
	h2->next->prev = tail_1;
	tail_1->next = h2->next;
	tail_2->next = h1;
	h1->prev = tail_2;
	return h1;
}

CDLinkedList InitList(CDLinkedList* L) {
	*L = (CDLNode*)malloc(sizeof(CDLNode));
	(*L)->next = *L;
	(*L)->prev = *L;
	return *L;
}

CDLinkedList List_TailInsert(CDLinkedList L) {
	ElemType e;
	scanf("%d", &e);
	while (e != -1) {
		CDLNode *node = (CDLNode*)malloc(sizeof(CDLNode));
		node->data = e;
		L->prev->next = node;
		node->next = L;
		node->prev = L->prev;
		L->prev = node;
		scanf("%d", &e);
	}
	return L;
}

void Output(CDLinkedList L) {
	CDLNode *p;
	for (p = L->next; p != L; p = p->next) {
		printf("%d ", p->data);
	}
	printf("\n");
}

void ReOutput(CDLinkedList L) {
	CDLNode *p;
	for (p = L->prev; p != L; p = p->prev) {
		printf("%d ", p->data);
	}
	printf("\n");
}

int List_IsSymmetric(CDLinkedList L) {
	CDLNode *head = L->next, *tail = L->prev;
	while(head != tail 
		&& head->prev != tail) {
		if (head->data == tail->data) {
			head = head->next;
			tail = tail->prev;
		} else {
			return 0;
		}
	}
	return 1;
}

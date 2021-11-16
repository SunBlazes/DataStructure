#include<stdio.h>
#include<stdlib.h>
#define ElemType int

typedef struct _node {
	ElemType data;
	struct _node *pred, *next;
	int freq;
} DNode, *DLinkedList;

int InitList(DLinkedList*);
DLinkedList List_TailInsert(DLinkedList);
void Output(DLinkedList);
void Locate(DLinkedList, ElemType); 

void Output(DLinkedList L) {
	if (!L) return;
	DNode *p = L;
	for (p = p->next; p; p = p->next) {
		printf("data: %d  freq: %d  addr: %p\n", p->data, p->freq, p);
	}
	
//	printf("\n");
}

int InitList(DLinkedList *L) {
	*L = (DNode*)malloc(sizeof(DNode));
	if (!(*L)) return 0;
	(*L)->next = NULL;
	(*L)->pred = NULL;
	(*L)->freq = 0;
	
	return 1;
}

DLinkedList List_TailInsert(DLinkedList L) {
	ElemType e;
	DNode *pre = L;
	scanf("%d", &e);
	while (e != -1) {
		DNode *node = (DNode*)malloc(sizeof(DNode));
		node->data = e;
		node->freq = 0;
		node->next = NULL;
		node->pred = pre;
		pre->next = node;
		pre = node;
		scanf("%d", &e);
	}
	return L;
}

void Locate(DLinkedList L, ElemType e) {
	DNode *p = L, *prev;
	while (p) {
		if (p->data == e) {
			DNode *q, *node = p;
			prev = p->pred;
			node->freq++;
			p = p->next;
			if (node->next) {
				prev->next = node->next;
				node->next->pred = prev;
			} else {
				prev->next = NULL;
				node->pred = NULL;
			}
			for (q = L->next; q &&
				q->freq > node->freq; q = q->next);
			node->pred = q->pred;
			q->pred->next = node;
			q->pred = node;
			node->next = q;
		} else {
			p = p->next;
		}
	} 
	printf("\n");
}


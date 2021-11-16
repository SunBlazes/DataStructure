#include<stdio.h>
#include<stdlib.h>
#define ElemType int

typedef struct _node {
	ElemType data;
	struct _node *next;
} LNode, *LinkedStack;

void Stack_Init(LinkedStack*);
void Stack_Push(LinkedStack, ElemType);
int Stack_IsEmpty(LinkedStack);
ElemType Stack_Pop(LinkedStack);
void Stack_Output(LinkedStack);
void Stack_Clear(LinkedStack);
ElemType Stack_Top(LinkedStack);

void Stack_Init(LinkedStack* s) {
	*s = (LNode*)malloc(sizeof(LNode));
	if (*s == NULL) {
		printf("没有可分配的内存\n");
	} else {
		(*s)->next = NULL;
	}
}

void Stack_Push(LinkedStack s, ElemType e) {
	LNode *node = (LNode*)malloc(sizeof(LNode));
	if (node == NULL) {
		printf("没有可分配的内存\n");
	} else {
		node->data = e;
		node->next = s->next;
		s->next = node;
	}
}

int Stack_IsEmpty(LinkedStack s) {
	return s->next == NULL;
}

ElemType Stack_Pop(LinkedStack s) {
	if (Stack_IsEmpty(s)) {
		printf("pop empty\n");
		return -1;
	}
	LNode *node = s->next;
	ElemType e = node->data;
	s->next = node->next;
	free(node);
	return e;
}

void Stack_Output(LinkedStack s) {
	LNode *p = s->next;
	for (; p; p = p->next) {
		printf("data: %d, %c ", p->data, p->data);
	} 
	printf("\n");
}

void Stack_Clear(LinkedStack s) {
	LNode *q = s->next;
	while (!Stack_IsEmpty(s)) {
		Stack_Pop(s);
	}
}

ElemType Stack_Top(LinkedStack s) {
	return s->next->data;
}

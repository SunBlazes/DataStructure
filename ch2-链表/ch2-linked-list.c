#include<stdio.h>
#include<stdlib.h>

typedef struct _node {
	int data;
	struct _node *next;
} LNode, *LinkedList;

int InitList(LinkedList*);
int Empty(LinkedList);
LinkedList List_TailInsert(LinkedList*);
void Output(LinkedList);
void List_Delete(LNode**, LNode*, LNode*, int);
LNode* List_GetElem(LinkedList, int);

void test() {
	LinkedList L;
	InitList(&L);
	List_TailInsert(&L);
	Output(L);
	List_Delete(&L, L, NULL, 5);
	Output(L);
}

int main() {
	test();
	return 0;
}

int InitList(LinkedList* L) {
	*L = NULL;
	return 1;
}

int Empty(LinkedList L) {
	return L == NULL;
}

void List_Delete(LNode** head, LNode *curr, LNode* prev, int data) {
	if (!curr || !(*head)) return;
	if (curr->data == data) {
//		首部需要被删除 
		if (!prev) {
			*head = (*head)->next;
		} else {
			prev->next = curr->next;
		}
		List_Delete(head, curr->next, prev, data);
		free(curr);
	} else {
		List_Delete(head, curr->next, curr, data);
	}
}

LNode* List_GetElem(LinkedList L, int number) {
	LNode *p = L;
	int i = 1;
	while (i++ < number && p) {
		p = p->next;
	}
	return p;
}

LinkedList List_TailInsert(LinkedList* L) {
	LNode *p;
	int data;
	scanf("%d", &data);
	while (data != -1) {
		LNode *node = (LNode*)malloc(sizeof(LNode));
		node->data = data;
		node->next = NULL;
		if (p) {
			p->next = node;
		} else {
			*L = node;
		}
		p = node;
		scanf("%d", &data);
	}
	return *L;
}

void Output(LinkedList L) {
	LNode *p;
	for (p = L; p; p = p->next) {
		printf("%d ", p->data);
	}
	printf("\n");
}

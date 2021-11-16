#include<stdio.h>
#include<stdlib.h>

typedef struct _node {
	int value;
	struct _node *next;
} Node;

typedef struct _list {
	Node *head;
	Node *tail;
	int size;
} List; 

void add(List *pList, int value) {
	Node *p = (Node*)malloc(sizeof(Node));
	p->value = value;
	p->next = NULL;
	if (pList->size != 0) {
		pList->tail->next = p;	
	} else {
		pList->head = p;
	}
	pList->size++;
	pList->tail = p;
}

int search(List *list, int value) {
	Node *next = list->head;
	int isFound = 0;
	while (next) {
		if (next->value == value) {
			isFound = 1;
			break;
		}
		next = next->next;
	}
	return isFound;
}

void list_delete(List *list, int value) {
	Node *prev = NULL, *curr = list->head, *temp = NULL;
	while (curr) {
		if (value == curr->value) {
			if (prev == NULL) {
				list->head = curr->next;
			} else {
				prev->next = curr->next;
			}
			temp = curr;
		} else {
			prev = curr;
		}
		curr = curr->next;
		free(temp);
		temp = NULL;
	}
}

void list_clear(List *list) {
	Node *q, *p;
	for (p = list->head; p; p = q) {
		q = p->next;
		free(p);
		p = NULL;
	}
}

void print(List *list) {
	Node *p;
	for (p = list->head; p; p = p->next) {
		printf("%d\t", p->value);
	}
	printf("\n");
} 

int main() {
	int number;
	List list;
	list.head = list.tail = NULL;
	list.size = 0;
	scanf("%d", &number);
	
	while(number != -1) {
		add(&list, number);
		scanf("%d", &number);
	}
	
//	print(&list);
//	printf("%d", search(&list, 5));
//	print(&list);
//	list_delete(&list, 5);
//	print(&list);
//	list_clear(&list);
	printf("clear\n");
	print(&list);
//	printf("hello");
}

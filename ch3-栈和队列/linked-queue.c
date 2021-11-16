#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define ElemType int

typedef struct _node {
	ElemType data; 
	struct _node *next;
} LinkedNode;

typedef struct {
	LinkedNode *front, *rear;
} LinkedQueue;

void Queue_Init(LinkedQueue*);
void Enqueue(LinkedQueue*, ElemType);
int Dequeue(LinkedQueue*, ElemType*);
int Queue_IsEmpty(LinkedQueue);
void Queue_Output(LinkedQueue); 

void Queue_Init(LinkedQueue* q) {
	q->front = q->rear = (LinkedNode*)malloc(sizeof(LinkedNode));
	q->front->next = NULL;
}

void Enqueue(LinkedQueue* q, ElemType e) {
	LinkedNode *node = (LinkedNode*)malloc(sizeof(LinkedNode));
	node->data = e;
	node->next = NULL;
	q->rear->next = node;
	q->rear = node;
}

int Queue_IsEmpty(LinkedQueue q) {
	return q.front->next == NULL;
}

int Dequeue(LinkedQueue* q, ElemType* e) {
	if (Queue_IsEmpty(*q)) return 0;
	*e = q->rear->data;
	LinkedNode *p = q->front->next;
	q->front->next = p->next;
	if (!p->next) {
		q->rear = q->front;
	}
	free(p);
	return 1;
}

void Queue_Output(LinkedQueue q) {
	if (Queue_IsEmpty(q)) return;
	LinkedNode *node = q.front;
	while ((node = node->next)) {
		printf("%d ", node->data);
	}
	printf("\n");
}

void test() {
	LinkedQueue q;
	Queue_Init(&q);
	int i = 0;
	while(i++ < 10) {
		Enqueue(&q, rand() % 20);
	}
	Queue_Output(q);
	int e;
	Dequeue(&q, &e);
	Dequeue(&q, &e);
	Dequeue(&q, &e);
	Queue_Output(q);
}

int main() {
	srand((unsigned int)time(0));
	test();
	return 0;
}


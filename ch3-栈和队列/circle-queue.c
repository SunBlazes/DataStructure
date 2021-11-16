#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define ElemType int
#define MaxSize 10

typedef struct _queue {
	ElemType data[MaxSize];
	int front, rear, size;
} Queue; 

void Queue_Init(Queue*);
int Queue_IsEmpty(Queue);
int Queue_IsFull(Queue);
int Enqueue(Queue*, ElemType);
int Dequeue(Queue*, ElemType*);
void Queue_Output(Queue);

void Queue_Init(Queue *q) {
	q->front = q->rear = q->size = 0;
}

int Queue_IsEmpty(Queue q) {
	return q.size == 0;
}

int Queue_IsFull(Queue q) {
	return q.size == MaxSize;
}

int Enqueue(Queue *q, ElemType e) {
	if (Queue_IsFull(*q)) return 0;
	q->size++;
	q->data[q->rear] = e;
	q->rear = (q->rear + 1) % MaxSize;
	return 1;
}

int Dequeue(Queue *q, ElemType *e) {
	if (Queue_IsEmpty(*q)) return 0;
	q->size--;
	*e = q->data[q->front];
	q->front = (q->front + 1) % MaxSize;
	return 1;
}

void Queue_Output(Queue q) {
	int start = q.front, flag = 1;
	while (start != q.rear || flag) {
		printf("start: %d, rear: %d, data: %d\n", start, q.rear, q.data[start]);
		start = (start + 1) % MaxSize;
		flag = 0;
	}
	printf("\n");
}

void test() {
	Queue q;
	Queue_Init(&q);
	while(Enqueue(&q, rand() % 10));
	Queue_Output(q);
	int e;
	Dequeue(&q, &e);
	Dequeue(&q, &e);
	Dequeue(&q, &e);
	Dequeue(&q, &e);
	Queue_Output(q);
	while(Enqueue(&q, rand() % 10));
	Queue_Output(q);
}

int main() {
	srand((unsigned int)time(0));
	test();
	return 0;
}

#include "linked-stack.h"

int handler (int n, int x) {
	LinkedStack stack;
	Stack_Init(&stack);
	Stack_Push(stack, 1);
	Stack_Push(stack, 2 * x);
	int i = 2;
	for (; i <= n; i++) {
		int latter = Stack_Pop(stack),
			former = Stack_Pop(stack);
		Stack_Push(stack, latter);
		Stack_Push(stack, 2 * x * latter - 2 * (i - 1) * former);
	}
	printf("%d", Stack_Pop(stack));
}

int main() {
	int n, x;
	scanf("%d %d", &n, &x);
	handler(n, x);
}



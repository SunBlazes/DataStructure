#include "linked-stack.h" 
#include <string.h>

int main () {
	char c;
	LinkedStack stack;
	Stack_Init(&stack);
	
	while ((c = getchar()) != '\n') {
		if (c >= 0 && c <= 9) continue; 
		if (c == '(' || c == '[' || c == '{') {
			Stack_Push(stack, c);
		} else {
			switch (c) {
				case ')':
					if (Stack_Pop(stack) != '(') {
						printf("ƥ�����\n");
					}
					break;
				case '}':
					if (Stack_Pop(stack) != '{') {
						printf("ƥ�����\n");
					}
					break;
				case ']':
					if (Stack_Pop(stack) != '[') {
						printf("ƥ�����\n");
					}
					break;
			}
		}
	}
	if (Stack_IsEmpty(stack)) {
		printf("ƥ��ɹ�\n");
	} else {
		printf("ƥ�����\n");
	}
	return 0;
} 

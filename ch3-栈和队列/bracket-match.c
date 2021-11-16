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
						printf("Æ¥Åä´íÎó\n");
					}
					break;
				case '}':
					if (Stack_Pop(stack) != '{') {
						printf("Æ¥Åä´íÎó\n");
					}
					break;
				case ']':
					if (Stack_Pop(stack) != '[') {
						printf("Æ¥Åä´íÎó\n");
					}
					break;
			}
		}
	}
	if (Stack_IsEmpty(stack)) {
		printf("Æ¥Åä³É¹¦\n");
	} else {
		printf("Æ¥Åä´íÎó\n");
	}
	return 0;
} 

#include "linked-stack.h"
#include <string.h>
#include <math.h>

// 读取两位及以上整数
void ReadNumber(LinkedStack s, int count) {
	int i = 0, sum = 0;
	for (; i < count; i++) {
		int number = Stack_Pop(s);
		sum += number * pow(10, i);
	}
	Stack_Push(s, sum);
}

int OpPriority(char c) {
	switch (c) {
		case '+':
		case '-':
			return 1;
		case '*':
		case '/':
			return 2;
		case '(':
			return 3; 
	}
}

void Calculate(LinkedStack s, char c) {
	int right = Stack_Pop(s), left = Stack_Pop(s);
	printf("left: %d, right: %d\n", left, right);
	switch (c) {
		case '-': 
			Stack_Push(s, left - right);break;
		case '+': 
			Stack_Push(s, left + right);break;
		case '/': 
			Stack_Push(s, left / right);break;
		case '*': 
			Stack_Push(s, left * right);break;
	}
}

int main () {
	char c;
	int count = 0;
	LinkedStack num_stack, operator_stack;
	Stack_Init(&num_stack);
	Stack_Init(&operator_stack);
	do {
		c = getchar(); // 11 count:2 
		if (c >= 48 && c <= 57) {
			count++;
			Stack_Push(num_stack, (int)c - 48);
		} else {
			if (count >= 2) {
				ReadNumber(num_stack, count);
				count = 0;
			}
			if (c != '\n') {
				count = 0;
				// 遇到')'表示这个括号的运算已结束 
				if (c == ')') {
					char op;
					// 依次弹出运算符直到遇到对应的'(' 
					while ((op = Stack_Pop(operator_stack)) != '(') {
						Calculate(num_stack, op);
					}
					// 如果输入的运算符优先级大于运算符栈顶部的优先级的话
					// 那么就压入运算符
					// 由于运算符栈自下而上优先级递增，那么根据这种情况
					// 运算符栈的运算符都要后于输入的运算符 
					// 还有就是运算符栈为空，那么就直接压入输入的运算符 
				} else if (Stack_IsEmpty(operator_stack) || 
						OpPriority(Stack_Top(operator_stack))
							< OpPriority(c)) {
					Stack_Push(operator_stack, c);
				} else {
					// 如果输入的运算符优先级小于运算符栈的优先级
					// 那么必须优先执行运算符栈
					// 直到运算符栈顶端的优先级小于输入的运算符 
					// 这里注意，由于'('优先级大于其他运算符 
					while (!Stack_IsEmpty(operator_stack) && 
						Stack_Top(operator_stack) != '(' && 
							OpPriority(Stack_Top(operator_stack))
								>= OpPriority(c)) {
						Calculate(num_stack, Stack_Pop(operator_stack));
					}
					Stack_Push(operator_stack, c);
				}
			}
		}
	} while(c != '\n');
	// 依次弹出剩余的运算符并执行运算 
	while (!Stack_IsEmpty(operator_stack)) {
		Calculate(num_stack, Stack_Pop(operator_stack));
	}
	Stack_Output(num_stack);
	Stack_Output(operator_stack);
	printf("final result: %d", Stack_Pop(num_stack));
	return 0;
}

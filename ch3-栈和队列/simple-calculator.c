#include "linked-stack.h"
#include <string.h>
#include <math.h>

// ��ȡ��λ����������
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
				// ����')'��ʾ������ŵ������ѽ��� 
				if (c == ')') {
					char op;
					// ���ε��������ֱ��������Ӧ��'(' 
					while ((op = Stack_Pop(operator_stack)) != '(') {
						Calculate(num_stack, op);
					}
					// ����������������ȼ����������ջ���������ȼ��Ļ�
					// ��ô��ѹ�������
					// ���������ջ���¶������ȼ���������ô�����������
					// �����ջ���������Ҫ�������������� 
					// ���о��������ջΪ�գ���ô��ֱ��ѹ������������ 
				} else if (Stack_IsEmpty(operator_stack) || 
						OpPriority(Stack_Top(operator_stack))
							< OpPriority(c)) {
					Stack_Push(operator_stack, c);
				} else {
					// ����������������ȼ�С�������ջ�����ȼ�
					// ��ô��������ִ�������ջ
					// ֱ�������ջ���˵����ȼ�С������������ 
					// ����ע�⣬����'('���ȼ�������������� 
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
	// ���ε���ʣ����������ִ������ 
	while (!Stack_IsEmpty(operator_stack)) {
		Calculate(num_stack, Stack_Pop(operator_stack));
	}
	Stack_Output(num_stack);
	Stack_Output(operator_stack);
	printf("final result: %d", Stack_Pop(num_stack));
	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define cube(x) ((x)*(x)*(x))

int mylen(const char *s) {
	int cnt = 0, i = 0;
	while (*s++ != '\0') {
		cnt++;
	}
	return cnt;
}

int mycmp(const char *s1, const char *s2) {
	while (*s1 != '\0' && *s1++ == *s2++);
	return *(s1 - 1) - *(s2 - 1);
}

char* mycpy(char* dst, const char* src) {
	char* res = dst;
	while (*dst++ = *src++);
	*dst = '\0';
	return res;
}

typedef struct {
	int month;
	int day;
	int year;
} date;

void genStruct(date *d) {
	scanf("%d %d %d", &d->month, &d->day, &d->year);
}

date* getStruct(date d) {
	date *p = &d;
	scanf("%d %d %d", &p->month, &p->day, &p->year);
	
	return p;
}

typedef union {
	int i;
	char ch[sizeof(int)];
} CHI;

//int* f() {
//	int i = 5;
//	return &i;
//}

void g() {
	int k = 24;
}

int Is_Legal() {
	char c;
	int i_num = 0;
	while ((c = getchar()) != '\n') {
		if (c == 'o') {
			if (i_num <= 0) {
				printf("出错了\n");
				return 0;
			}
			i_num--;
		}
		if (c == 'i') i_num++;
		printf("i_num: %d\n", i_num);
	}
	printf("成功了\n");
	return 1;
}

/* int Is_CenterSymmetry(LinkedList L, int n) {
	Stack s;
	int end_num = n / 2, i = 1;
	Node *p = L;
	for (; i < end_num; i++, p = p->next) {
		Push(s, p->data);
	}
	if (n % 2 == 1) 
		p = p->next->next;
	else 
		p = p->next;
	while (!StackEmpty(s)) {
		int a;
		Pop(s, &a);
		if (a != p->data) {
			return 0;
		}
		p = p->next;
	}
	return 1;
} */

/* bool Push(SharedStack s, ElemType e, bool isUp) {
	if (s.top1 + 1 == s.top2) {
		return false;
	}
	if (isUp) {
		s.data[++s.top1] = e;
	} else {
		s.data[--s.top2] = e;
	}
	return true;
}

bool Pop(SharedStack s, ElemType *e, bool isUp) {
	if (isUp) {
		if (s.top1 == -1) return false;
		*e = s.data[s.top1--];
	} else {
		if (s.top2 == maxsize) return false;
		*e = s.data[s.top2++];
	}
	return true;
} */


int main()
{
	// 输出he 
	/* char ch[] = "hello";
	char *p = strchr(ch, 'l'), 
		c = *p;
	*p = '\0';
	char *q = (char*)malloc(strlen(ch) + 1);
	q = strcpy(q, ch);
	*p = c;
	printf("%s\n", ch);
	printf("%s", q);*/
	
	/* int len = 5, num;
	printf("%*d\n", len, cube(5));
	scanf("%*d %d", &num);
	int outputNum = printf("%d\n", num);
	printf("%d", outputNum); */
	
	/*  输出二进制 
		int number;
		scanf("%d", &number);
		unsigned mask = 1u<<31;
		for (; mask > 0; mask >>= 1) {
			printf("%d", mask & number ? 1 : 0);
		}
	*/
	Is_Legal();
}



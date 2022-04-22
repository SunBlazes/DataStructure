#include<stdio.h>
#define MaxSize 100

// 从下标1开始 且末尾不用'\0'结束 
typedef struct {
	char ch[MaxSize];
	int length;
} SString;

void StrAssign(SString*, char*);
void get_next(SString, int[]);
void print_str(SString);
int KMP(SString, SString, int[]);
void get_nextval(SString, int[], int []);

void print_str(SString s) {
	int i = 1;
	for (; i <= s.length; i++) {
		printf("%c", s.ch[i]);
	}
	printf("\n");
}

void StrAssign(SString* s, char* chars) {
	int i = 0;
	for (; chars[i] != '\0'; i++) {
		(*s).ch[i + 1] = chars[i];
		(*s).length++;
	}
}

void get_next(SString s, int next[]) {
	int j = 1, t = 0;
	next[1] = 0;
	while (j < s.length) {
		if (t == 0 || s.ch[j] == s.ch[t]) {
			t++;
			j++;
			next[j] = t;
		} else {
			t = next[t];
		}
	}
}

void get_nextval(SString s, int nextval[], int next[]) {
	int j = 1, t = 0;
	nextval[1] = 0;
	for (j = 2; j <= s.length; j++) {
		if (s.ch[j] == s.ch[next[j]]) {
			nextval[j] = nextval[next[j]];
		} else {
			nextval[j] = next[j];
		}
	}
	/*while (j < s.length) {
		if (t == 0 || s.ch[j] == s.ch[t]) {
			if (s.ch[j + 1] != s.ch[t + 1]) {
				nextval[j + 1] = t + 1;
			} else {
				nextval[j + 1] = nextval[t + 1];
			}
			t++;
			j++;
		} else {
			t = nextval[t];
		}
	}*/
}

int KMP(SString s, SString ms, int next[]) {
	int i = 1, j = 1;
	while (i <= s.length && j <= ms.length) {
		if (j == 0 || s.ch[i] == ms.ch[j]) {
			i++;j++;
		} else {
			j = next[j];
		}
	}
	if (j > ms.length) return i - j + 1;
	return 0;
}

void test() {
	SString str, model_str;
	StrAssign(&str, "asababaaababaass");
	StrAssign(&model_str, "ababaaababaa");
//	print_str(model_str);
	int next[model_str.length + 1];
	int nextval[model_str.length + 1];
	get_next(model_str, next);
	get_nextval(model_str, nextval, next);
	int i = 1;
	for (; i <= model_str.length; i++) {
		printf("%d ", next[i]);
	}
	printf("\n0 1 1 2 3 4 2 2 3 4 5 6\n");
	i = 1;
	for (; i <= model_str.length; i++) {
		printf("%d ", nextval[i]);
	}
	printf("\n0 1 0 1 0 4 2 1 0 1 0 4\n");
	printf("loca: %d", KMP(str, model_str, next));
}

int main() {
	test();
	return 0;
} 

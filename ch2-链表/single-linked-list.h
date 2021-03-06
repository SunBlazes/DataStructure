#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define ElemType int

typedef struct _node {
	ElemType data;
	struct _node *next;
} LNode, *LinkedList; 

int InitList(LinkedList*);
int Empty(LinkedList);
LinkedList List_HeadInsert(LinkedList);
LinkedList List_TailInsert(LinkedList);
void Output(LinkedList);
LNode* GetElem(LinkedList, int);
LNode* LocateElem(LinkedList, ElemType);
LinkedList List_PrevInsert(LinkedList, int, ElemType);
LinkedList List_Delete(LinkedList, int);
LinkedList List_NextInsert(LinkedList, int, ElemType e);
LNode* List_InsertPriorNode(LNode*, ElemType);
LinkedList List_DeleteAll(LinkedList, int);
void List_ReOutput(LinkedList, int);
LinkedList List_DeleteMin(LinkedList);
LinkedList List_Reverse(LinkedList); 
LinkedList List_Increment(LinkedList); 
LinkedList List_FindMutualNode(LinkedList, LinkedList);
void List_SplitByOddEven(LinkedList);
LinkedList List_DeleteRe(LinkedList);
LinkedList List_MergeIntoDecrease(LinkedList, LinkedList);
LinkedList List_Mutual(LinkedList, LinkedList);
int List_IsSubsquence(LinkedList, LinkedList);
int List_FindFromEndByLoca(LinkedList, int);
//LinkNode ch2_2012_408(LinkedList, LinkedList);
LinkedList ch2_2015_408(LinkedList);
LNode List_IsLoop(LinkedList);
LinkedList ch2_2019_408(LinkedList);
// ιζ©ζεΊ 
void Selective_Sort(LinkedList);

void Selective_Sort(LinkedList L) {
	if (!L->next) return;
	while (L->next) {
		ElemType m = ~(1<<31);
		LNode *prev, *prev1 = L, *p = L->next;
		while (p) {
			if (p->data < m) {
				m = p->data;
				prev = prev1;
			}
			p = p->next;
			prev1 = prev1->next;
		}
		LNode *q = prev->next;
		prev->next = q->next;
		q->next = L->next;
		L->next = q;
		L = q;
	}
}

LinkedList ch2_2019_408(LinkedList L) {
	
}

LNode List_IsLoop(LinkedList L) {
	
}

LinkedList ch2_2015_408(LinkedList L) {
	
}

/* LinkNode ch2_2012_408(LinkedList L1, LinkedList L2) {
	int len1 = length(L1), len2 = length(L2);
	LinkNode *p, *q;
	for (p = L1; len1 > len2; len1--) {
		p = p->next;
	}
	for (q = L2; len1 < len2; len2--) {
		q = q->next;
	}
	while (q->next && q->next != p->next) {
		p = p->next;
		q = q->next;
	}
	return p->next;
}*/

// ζ₯ζΎιΎθ‘¨δΈ­ηεζ°η¬¬kδΈͺδ½η½?ηη»ηΉοΌθΎεΊε?ηdataεΉΆθΏε1οΌε¦εθΏε0 
int List_FindFromEndByLoca(LinkedList L, int k) {
	LNode *p = L->next, *q = L;
	int gap = 1;
	for (; p; p = p->next) {
		gap++;
		if (gap > k) {
			q = q->next;
		}
	}
	if (q == L) 
		return 0;
	else {
		printf("data: %d\n", q->data);
		return 1;
	}
}

// ε€ζ­Bζ―ε¦δΈΊAηθΏη»­ε­εΊε 
int List_IsSubsquence(LinkedList A, LinkedList B) {
	LNode *p = A->next, *q1, *q2;
	if (!(B->next)) return 1;
	int flag = 1;
	for(; p; p = p->next) {
		q2 = B->next;
		if (p->data == q2->data) {
			for (q1 = p->next, q2 = q2->next; 
				q1 && q2; q1 = q1->next, q2 = q2->next) {
				if (q1->data != q2->data) {
					flag = 0;
					break;
				}
			}
			if (q2 == NULL) {
				flag = 1;
				break;
			}
		}
	}
	return flag;
}

// ζ½εΊδΈ€δΈͺιε’ιΎθ‘¨ηε¬ε³η»ηΉζζζ°ιΎθ‘¨δΈδΈη ΄εεζ₯δΈ€δΈͺιΎθ‘¨ 
LinkedList List_Mutual(LinkedList L1, LinkedList L2) {
	LinkedList L;
	InitList(&L);
	LNode *p = L1->next, *q = L2->next, *pre = L;
	while (p && q) {
		if (p->data == q->data) {
			LNode *node = (LNode*)malloc(sizeof(LNode));
			node->data = q->data;
			node->next = NULL;
			pre->next = node;
			pre = node;
			p = p->next;
			q = q->next;
		} else {
			if (p->data > q->data) {
				for (q = q->next; q && q->data < p->data; q = q->next);
			} else {
				for (p = p->next; p && p->data < q->data; p = p->next);
			}
		}
	}
	return L;
}

// δΈ€δΈͺιε’ιΎθ‘¨ε½εΉΆδΈΊδΈδΈͺιειΎθ‘¨οΌδΈδ½Ώη¨εζ₯η»ηΉε­ζΎε½εΉΆεηη»ηΉ
LinkedList List_MergeIntoDecrease(LinkedList L1, LinkedList L2) {
	LNode *p1 = L1->next, *p2 = L2->next, *r;
	L1->next = NULL;
	while (p1 && p2) {
		if (p1->data >= p2->data) {
			r = p2->next;
			p2->next = L1->next;
			L1->next = p2;
			p2 = r;
		} else {
			r = p1->next;
			p1->next = L1->next;
			L1->next = p1;
			p1 = r;
		}
	}
	return L1;
}

// ε ι€ιΎθ‘¨ιε€ηη»ηΉ 
LinkedList List_DeleteRe(LinkedList L) {
	LNode *p, *q = L, *pre;
	if (!(L->next)) return L;
	while ((q = q->next)) {
		pre = q;
		p = q->next;
		while (p) {
			if (q->data == p->data) {
				pre->next = p->next;
				free(p);
				Output(L);
			} else {
				pre = p;
			}
			p = pre->next;
		}
	}
	return L;
}

// εθ§£ιΎθ‘¨δΈΊδΈ€δΈͺιΎθ‘¨οΌεε«εε«εΆζ°εε₯ζ° 
void List_SplitByOddEven(LinkedList L) {
	LinkedList E, O;
	InitList(&E);
	InitList(&O);
	LNode *e_p = E, *o_p = O, *p = L;
	for (p = p->next; p; p = p->next) {
		if (p->data % 2) {
			LNode *node = (LNode*)malloc(sizeof(LNode));
			node->data = p->data;
			node->next = NULL;
			o_p->next = node;
			o_p = node;
		} else {
			LNode *node = (LNode*)malloc(sizeof(LNode));
			node->data = p->data;
			node->next = NULL;
			e_p->next = node;
			e_p = node;
		}
	}
	Output(E);
	Output(O);
}

// ζΎεΊδΈ€δΈͺιΎθ‘¨ηε¬ε±η»ηΉ 
LinkedList List_FindMutualNode(LinkedList L1, LinkedList L2) {
	LinkedList L;
	InitList(&L);
	LNode *p, *q;
	for (p = L1->next; p; p = p->next) {
		for (q = L2->next; q; q = q->next) {
			if (q->data == p->data) {
				List_NextInsert(L, 0, q->data);
			}
		}
	}
	return L;
}

// δ½ΏιΎθ‘¨ιε’ζεΊ(εζ³‘ζεΊ)
LinkedList List_Increment(LinkedList L) {
	if (L->next == NULL) return L; 
	LNode *p, *q, *pre, *tail;
	while (tail != L->next) {
		p = L->next;
		pre = L;
		for (q = p->next; q && q != tail; q = q->next) {
			if (p->data > q->data) {
				pre->next = q;
				p->next = q->next;
				q->next = p;
			}
			pre = p;
			p = q;
			printf("pre->data: %d, p->data: %d, q->data: %d\n", pre->data, p->data, q->data);
			Output(L);
		}
		tail = p;
	}
	return L;
}
 

// ε°±ε°εη½? 
LinkedList List_Reverse(LinkedList L) {
	if (L->next == NULL) return L;
	LNode *curr = L->next, *pre = L->next;
	while ((pre = pre->next)) {
		curr->next = pre->next;
		pre->next = L->next;
		L->next = pre;
		pre = curr;
	}
	return L;
}

// ιεΊθΎεΊ 
void List_ReOutput(LinkedList L, int flag) {
	if (L == NULL) return;
	List_ReOutput(L->next, 0);
	if (!flag) {
		printf("%d ", L->data);
	}
	printf("\n");
}

// ε ι€ζε°η»ηΉοΌεθ?Ύζε°η»ηΉε―δΈοΌ 
LinkedList List_DeleteMin(LinkedList L) {
	LNode *prev = NULL, *curr = L->next, *min = L;
	while (curr) {
		if (!prev) {
			min = L->next;
			prev = L;
		} else {
			if (min->data > curr->data) {
				prev = min;
				min = curr;
			}
		}
		curr = curr->next;
	}
	prev->next = min->next;
	free(min);
	return L;
}

LinkedList List_DeleteAll(LinkedList L, int data) {
	LNode *p = L, *prev = L;
	while ((p = prev->next)) {
		if (p->data == data) {
			prev->next = p->next;
			free(p);
		} else {
			prev = p;
		}
	}
	return L;
}

// εΈ¦ε€΄ζιηεε§ε 
int InitList(LinkedList *L) {
	*L = (LNode*)malloc(sizeof(LNode));
	if (*L == NULL) {
		return 0;
	} 
	(*L)->next = NULL;
	return 1;
}

// εΈ¦ε€΄ζιηε€η©Ί 
int Empty(LinkedList L) {
	return L->next == NULL;
}

// εΈ¦ε€΄ζιηε€΄ζζ³ (ιεΊ)
LinkedList List_HeadInsert(LinkedList L) {
	ElemType data;
	LNode* curr = NULL;
	scanf("%d", &data);
	while (data != -1) {
		LNode *node = (LNode*)malloc(sizeof(LNode));
		node->data = data;
		node->next = curr;
		L->next = node; 
		curr = node;
		scanf("%d", &data);
	}
	return L;
}

// εΈ¦ε€΄ζιηε°Ύζζ³ (ζ­£εΊ)
LinkedList List_TailInsert(LinkedList L) {
	LNode *p = L;
	ElemType data;
	scanf("%d", &data);
	while (data != -1) {
		LNode *node = (LNode*)malloc(sizeof(LNode));
		node->data = data;
		node->next = NULL;
		p->next = node;
		p = node;
		scanf("%d", &data);
	}
	return L;
}

// εΈ¦ε€΄ζιηζεΊζ₯ζΎ 
LNode* GetElem(LinkedList L, int i) {
	int j = 1;
	LNode *p = L;
	while (j++ <= i && (p = p->next));
	return p;
}

// εΈ¦ε€΄ζιηθΎεΊ 
void Output(LinkedList L) {
	LNode *p;
	for (p = L->next; p; p = p->next) {
		printf("%d ", p->data);
	}
	printf("\n");
}

// εΈ¦ε€΄ζιηζεΌζ₯ζΎ 
LNode* LocateElem(LinkedList L, ElemType e) {
	LNode *curr = L;
	while ((curr = curr->next) && e != curr->data);
	return curr;
}

// εΈ¦ε€΄ζιηεΎεζε₯ 
LinkedList List_PrevInsert(LinkedList L, int i, ElemType e) {
	LNode *prev_node = GetElem(L, i - 1);
	if (prev_node == NULL) return L;
	LNode *node = (LNode*)malloc(sizeof(LNode));
	node->data = e;
	node->next = prev_node->next;
	prev_node->next = node;
	return L;
}

// εΈ¦ε€΄ζιηεΎεζε₯ 
LinkedList List_NextInsert(LinkedList L, int i, ElemType e) {
	LNode *curr_node = GetElem(L, i);
	if (curr_node == NULL) return L;
	LNode *node = (LNode*)malloc(sizeof(LNode));
	node->data = e;
	node->next = curr_node->next;
	curr_node->next = node;
	return L;
}

// εΈ¦ε€΄ζιηε ι€ 
LinkedList List_Delete(LinkedList L, int i) {
	LNode *prev_node = GetElem(L, i - 1), *delete_node = GetElem(L, i);
	if (!delete_node) return L;
	prev_node->next = delete_node->next;
	free(delete_node);
	delete_node = NULL;
	return L; 
}

// εΈ¦ε€΄ζιηζε?η»ηΉεεζ 
LNode* List_InsertPriorNode(LNode* node, ElemType e) {
	if (!node) return NULL;
	LNode *new_node = (LNode*)malloc(sizeof(LNode));
	new_node->next = node->next;
	node->next = new_node; // ζζ°η»ηΉζε₯ε°ζε?η»ηΉει’
	// δΊ€ζ’ζ°θηΉεζε?θηΉηdata 
	new_node->data = node->data;   
	node->data = e;
	return node;
}


#include<iostream>
#include<queue>
#include<stack>
#include<memory.h>
#include<cmath>
#define ElemType int
using namespace std;

typedef struct _btree {
	ElemType data;
	struct _btree *lchild, *rchild;
	int tag;
} BiNode, *BiTree;

BiNode* createBiTree();
// ��ͷ��� 
BiNode* initBiTree();
void traverseByLevelOrder(BiTree);
// �������� 
void traverseByReLevelOrder(BiTree);
void traverseByPreOrder(BiTree);
// �ǵݹ����� 
void traverseByPreOrder1(BiTree);
// �ǵݹ����� 
void traverseByPreOrder2(BiTree);
void traverseByMidOrder(BiTree);
// �ǵݹ����� 
void traverseByMidOrder1(BiTree);
// �ǵݹ����� 
void traverseByMidOrder2(BiTree);
void traverseByPostOrder(BiTree);
// �ǵݹ���� 
void traverseByPostOrder1(BiTree);
// �ݹ������߶� 
int getHeight(BiTree);
// �ǵݹ������߶� 
int getHeight1(BiTree);
int getHeight2(BiTree);
bool isCompleteTree(BiTree);
// ����������γɶ�����
BiTree PreAndIn(int[], int[], int);
BiTree PreAndIn1(int[], int[], int, int);
BiTree PreAndIn2(int[], int[], int, int, int, int);
// ͳ��˫��֧������ 
int countDoubleOffspringsOfNodes(BiTree);
// �������н����������� 
BiTree swapLeftAndRightTree(BiTree);
BiTree swapLeftAndRightTree1(BiTree);
// �õ�����������еĵ�k�Ľ���data 
ElemType getDataByPreOrder(BiTree, int);
void delTree(BiTree&); 
bool findAndDeleteNodeWithX(BiTree, ElemType);
// ��ӡֵΪx���������Ƚ���ֵ 
bool printAncestors(BiTree, ElemType, bool&);
// �ҵ�p,r����Ĺ������Ƚ�� 
void Ancestor(BiNode*, BiNode*, BiNode*, BiNode*);
// ���ؿս�� 
BiNode* resEmptyNode();
// ���ض��������н����������һ��Ľ����� 
// �ֻ�ʹ���������� 
int getBiTreeWidth(BiTree); 
// ����ս��������ÿһ��Ľ�� 
int getBiTreeWidth1(BiTree);
// ��Ҷ��������������һ�������� 
BiNode* linkAllLeafNodes(BiTree);
BiNode* linkAllLeafNodes1(BiTree, BiNode*&);
// �ж������������Ƿ����� 
bool is_SimilarTree(BiTree, BiTree);
bool is_SimilarTree1(BiTree, BiTree);
// �����������У���֪����������������� 
void PreToPost(int[], int, int, int[], int, int);
// ����ͺ����γɶ����� 
BiTree PostAndIn(int[], int[], int, int, int, int);
// �ж��Ƿ�Ϊ���������� 
bool is_BSTree(BiTree);
// �ж��Ƿ�Ϊƽ������� 
bool is_AVL(BiTree);
void is_AVL1(BiTree, bool&, int&);

void test() {
//	BiTree T = createBiTree();
//	traverseByPreOrder(T);
//	traverseByPreOrder1(T);
//	cout<<endl;
//	traverseByPreOrder2(T);
//	traverseByLevelOrder(T);
//	traverseByReLevelOrder(T);
//	traverseByMidOrder1(T); 
//	traverseByMidOrder2(T);
//	traverseByPostOrder(T);
//	traverseByPostOrder1(T);
//	cout<<"height: "<<getHeight(T)<<endl;
//	cout<<"height: "<<getHeight1(T)<<endl;
//	cout<<"height: "<<getHeight2(T);
//	cout<<"isCompleteTree: "<<isCompleteTree(T)<<endl;
	int a[] = {1, 2, 4, 5, 6, 8, 3, 7},
		b[] = {4, 2, 6, 8, 5, 1, 3, 7}; 
//	int a[] = {1, 2, 4, 6, 11, 12, 13, 14, 7, 3, 5, 8, 9, 10, 15},
//		b[] = {11, 6, 13, 12, 14, 4, 7, 2, 1, 3, 8, 10, 9, 5, 15};
	BiTree T = PreAndIn(a, b, sizeof(b) / sizeof(b[0]));
//	BiTree T = PreAndIn1(a, b, 0, sizeof(b) / sizeof(b[0]) - 1);
//	BiTree T = PreAndIn2(a, b, 0, sizeof(b) / sizeof(b[0]) - 1, 0, sizeof(b) / sizeof(b[0]) - 1);
	traverseByPreOrder(T);
//	cout<<endl;
//	traverseByMidOrder2(T);
//	cout<<endl;
}

void test1() {
	BiTree T = createBiTree();
//	BiTree T = initBiTree();
//	cout<<countDoubleOffspringsOfNodes(T)<<endl;
//	cout<<T<<endl;
//	swapLeftAndRightTree(T);
//	swapLeftAndRightTree1(T);
//	findAndDeleteNodeWithX(T, 1);
	traverseByPreOrder(T);
	cout<<"\nis_BSTree: "<<is_BSTree(T)<<endl;
	cout<<"is_AVL   : "<<is_AVL(T)<<endl;
	bool balance = false;
	int h;
	is_AVL1(T, balance, h);
	cout<<"is_AVL1  : "<<balance<<endl;
//	bool flag = false;
//	printAncestors(T, 10, flag);
//	cout<<getDataByPreOrder(T, 15)<<endl;
//	BiNode *r;
//	Ancestor(T, T->lchild->rchild->rchild->lchild->rchild, T->lchild->rchild->rchild->rchild, r);
//	cout<<r<<endl;
//	cout<<(r->data)<<endl;
}

void test2 () {
	BiTree T = initBiTree();
//	cout<<getBiTreeWidth(T->lchild)<<endl;
//	cout<<getBiTreeWidth1(T->lchild)<<endl;
	BiNode *head = new(BiNode), *pre = head;
	head->lchild = head->rchild = NULL; 
	linkAllLeafNodes1(T->lchild, pre);
	pre = head;
	while(pre = pre->rchild) {
		cout<<(pre->data)<<" ";
	}
//	BiTree T1 = initBiTree();
//	BiTree T2 = initBiTree();
//	cout<<is_SimilarTree(T1->lchild, T2->lchild)<<endl; 
//	int pre[] = {1, 2, 4, 8, 9, 5, 10, 11, 3, 6, 12, 13, 7, 14, 15};
//	int len = sizeof(pre) / sizeof(pre[0]);
//	int post[len];
//	PreToPost(pre, 0, len - 1, post, 0, len - 1);
//	int i = 0;
//	for (; i < len; i++) cout<<post[i]<<" ";
}

void test3 () {
	BiTree T1 = initBiTree();
	BiTree T2 = initBiTree();
	cout<<is_SimilarTree(T1, T2);
}

void test4 () {
	int post[] = {11, 13, 14, 12, 6, 7, 4, 2, 10, 9, 8, 15, 5, 3, 1},
		in[]   = {11, 6, 13, 12, 14, 4, 7, 2, 1, 3, 8, 10, 9, 5, 15};
	int len = sizeof(post) / sizeof(post[0]);
	BiTree T = PostAndIn(post, in, 0, len - 1, 0, len - 1);
	traverseByPreOrder(T);
}

int main() {
	test();
//	test1();
//	test2();
//	test3();
//	test4();
	return 0;
}

void is_AVL1(BiTree T, bool& balance, int& h) {
	int hl = 0, hr = 0;
	bool bl = false, br = false;
	if (!T) {
		balance = true;
		h = 0;
	} else if (!T->lchild && !T->rchild) {
		balance = true;
		h = 1;
	} else { 
		// �Ȳ����������������������¶���ִ�� 
		is_AVL1(T->lchild, bl, hl);
		is_AVL1(T->rchild, br, hr);
		if (abs(hl - hr) > 1) {
			balance = false;
		} else {
			// ������ƽ������������������������ĸ߶Ȳ�ܴ���1
			// ��������������������ƽ������� 
			balance = bl && br;
		}
		h = (hl > hr ? hl : hr) + 1;
	}
}

bool is_AVL(BiTree T) {
	bool lf = true, rf = true;
	if (T) {
		lf = is_AVL(T->lchild);
		if (abs(getHeight(T->lchild) - getHeight(T->rchild)) > 1) return false;
		if (T->lchild && T->data <= T->lchild->data) return false;
		if (T->rchild && T->data >= T->rchild->data) return false;
		rf = is_AVL(T->rchild);
	}
	return lf && rf;
}

bool is_BSTree(BiTree T) {
	bool lf = true, rf = true;
	if (T) {
		lf = is_BSTree(T->lchild);
		if (T->lchild && T->data <= T->lchild->data) return false;
		if (T->rchild && T->data >= T->rchild->data) return false;
		rf = is_BSTree(T->rchild);
	}
	return lf && rf;
}

/*
	pre[]: ��������
	in[]: ��������
	prel: �����������ʼλ��
	prer: ��������Ľ���λ�� 
	inl: �����������ʼλ��
	inr: ��������Ľ���λ��
*/
BiTree PreAndIn2(int pre[], int in[], int prel, int prer, int inl, int inr) {
	// ���:  0       1 2 3  4  5  6  7 8 9 10 11 12 13 14
	// pre:   1(prel) 2  4  6 11 12 13 14 7        3  5  8  9 10 15(prer)
	// in:   11(inl)  6 13 12 14  4  7  2 1(pivot) 3  8 10  9  5 15(inr)
	// ����˼·���������������ʼλ�õ�ֵȥ�ҵ������������λ��pivot���������������л��� 
	// ��ôpivot������ֳ�prel(��)prel+1~pivot-inl+prel(���������)pivot-inl+prel+1~prer(���������)
	// ����ֳ�inl~pivot-1(���������)pivot(��)pivot+1~inr(���������)
	BiNode *node = new(BiNode);
	node->data = pre[prel]; 
	int pivot;
	for (pivot = inl; pivot <= inr && 
		pre[prel] != in[pivot]; pivot++);
	if (pivot == inr + 1) return NULL;
	node->lchild = PreAndIn2(pre, in, prel + 1, pivot - inl + prel, inl, pivot - 1);
	node->rchild = PreAndIn2(pre, in, pivot - inl + prel + 1, prer, pivot + 1, inr);
	return node;
}

/*
	post[]: ��������
	in[]: ��������
	postl: �����������ʼλ��
	postr: ��������Ľ���λ�� 
	inl: �����������ʼλ��
	inr: ��������Ľ���λ��
*/
BiTree PostAndIn(int post[], int in[], int postl, int postr, int inl, int inr) {
	// ����˼·���ɺ�������Ľ���λ�õ�ֵȥ�ҵ������������λ��pivot���Ժ����������л��� 
	// ��ôpivot������ֳ�postl~postl+pivot-inl-1(���������)postl+pivot-inl~postr-1(���������)postr(��)
	// ����ֳ�inl~pivot-1(���������)pivot(��)pivot+1~inr(���������)
	BiNode *node = new(BiNode);
	node->data = post[postr];
	int pivot;
	for (pivot = inl; pivot <= inr && 
		post[postr] != in[pivot]; pivot++);
	if (pivot == inr + 1) return NULL;
	node->lchild = PostAndIn(post, in, postl, postr - inr + pivot - 1, inl, pivot - 1);
	node->rchild = PostAndIn(post, in, postr - inr + pivot, postr - 1, pivot + 1, inr);
	return node;
}

/*
	pre[]: ��������
	s1: ������ʼλ��
	e1: �����βλ��
	post[]: ��������
	s2: ������ʼλ��
	e2: �����βλ�� 
	func: ����������������������ó��������� 
*/
void PreToPost(int pre[], int s1, int e1, int post[], int s2, int e2) {
	// ����˼·����������ֳɸ����ң��������������Ҹ�
	// �����������ʼֵ�϶��Ǹ��ڵ��ֵ����ô������������
	// ���丳�������ĩβλ�á�����������������ÿ��������Ҷ�ӽ�㶼����������
	// ����ÿ���������������������ĸ�������floor(�ܸ���/2)�� 
	if (e1 >= s1) {
		int half = (e1 - s1) / 2;// ���Ե������������������ĸ��� 
		post[e2] = pre[s1];
		PreToPost(pre, s1 + 1, s1 + half, post, s2, s2 + half - 1);
		PreToPost(pre, s1 + half + 1, e1, post, s2 + half, e2 - 1);
	}
}

bool is_SimilarTree(BiTree T1, BiTree T2) {
	if (T1 && T2) {
		return is_SimilarTree(T1->lchild, T2->lchild) &&
			is_SimilarTree(T1->rchild, T2->rchild);
	} else if (T1 && !T2 || !T1 && T2) {
		return false;
	}
	return true;
}

bool is_SimilarTree1(BiTree T1, BiTree T2) {
	queue<BiNode*> q1;
	queue<BiNode*> q2;
	q1.push(T1);
	q2.push(T2);
	while (!q1.empty() && !q2.empty()) {
		BiNode *t1 = q1.front(), *t2 = q2.front();
		q1.pop(); q2.pop();
		if (t1->lchild) {
			if (!t2->lchild) return false;
			q1.push(t1->lchild);
		}
		if (t1->rchild) {
			if (!t2->rchild) return false;
			q1.push(t1->rchild);
		}
		if (t2->lchild) {
			if (!t1->lchild) return false;
			q2.push(t2->lchild);
		}
		if (t2->rchild) {
			if (!t1->rchild) return false;
			q2.push(t2->rchild);
		}
	}
	return true;
}

BiNode* linkAllLeafNodes1(BiTree B, BiNode*& pre) {
	if (B) {
		linkAllLeafNodes1(B->lchild, pre);
		if (!B->lchild && !B->rchild) {
			pre->rchild = B;
			pre = B;
		}
		linkAllLeafNodes1(B->rchild, pre);
	}
}

BiNode* linkAllLeafNodes(BiTree B) {
	BiNode *head = resEmptyNode();
	stack<BiNode*> s;
	BiNode *r = head;
	BiNode *p = B;
	while (p || !s.empty()) {
		while (p) {
			s.push(p);
			p = p->lchild;
		}
		BiNode *q = s.top();
		s.pop();
		if (q->rchild) {
			p = q->rchild;
		} else if (!q->lchild) {
			r->rchild = q;
			r = q;
		}
	}
	return head;
}

BiNode* resEmptyNode() {
	// ����getBiTreeWidth1����������������Ľ�� 
	BiNode* p = new(BiNode);
	p->data = -999;
	p->lchild = NULL;
	p->rchild = NULL;
	return p;
}

int getBiTreeWidth1(BiTree B) {
	// ����˼·�Ǹ�ÿһ�����һ�����������ս�㣬�ָ���һ��Ľ�㡣 
	// ��ʼ��w=0��ÿ�α���һ��Ԫ�أ���w++�������ĺ��ӽ����ӣ����������� 
	// ֱ�������ս�㣬��ôw������һ��Ŀ�ȣ���maxWidth�Ƚϡ���������w=0��
	// ͬʱ��һ��Ľ���Ѿ�ȫ����ӣ���ĩβ����ս�㣬�ظ����� 
	if (!B) return 0;
	queue<BiNode*> q;
	q.push(B);
	q.push(resEmptyNode());
	int maxWidth = -1;
	int w = 0;
	// ����ý����ǿս�㣬���Ҳ��0����ζ���ڿս��ǰ������н��û�к��ӽ�� 
	// ��һ��Ϊ�գ���ô�����ѭ�� 
	while (!(q.front()->data == -999 && w == 0)) {
		BiNode* p = q.front();
		q.pop();
		if (p->data == -999) {
			if (w > maxWidth) maxWidth = w;
			w = 0;
			q.push(resEmptyNode());
		} else {
			w++;
		}
		if (p->lchild) {
			q.push(p->lchild);
		}
		if (p->rchild) {
			q.push(p->rchild);
		}
	}
	return maxWidth;
}

int getBiTreeWidth(BiTree B) {
	// ����˼·��q1��q2�ֻ�ʹ�ã�������q1�ȴ�������
	// ��q1����Ľ��һ�ߵ�����һ�߼�¼������һ�������ĺ������q2�� 
	// q1Ϊ������һ��Ŀ��Ҳ�͵õ��ˣ�ͬ��q2Ҳִ����һ������q1�ʹ���
	// ��q2���н��ĺ��ӽ�㣬ͬʱҲ�͵õ�����һ��Ŀ�� 
	// ��Ⱦ�ȡ��Щ�����п�ȵ����ֵ 
	if (!B) return 0; 
	queue<BiNode*> q1;
	queue<BiNode*> q2;
	q1.push(B);
	int maxWidth = -1;
	// ����ѭ����������q1��q2ͬʱΪ�� 
	while (!(q1.empty() && q2.empty())) {
		if (q2.empty()) {
			int w = 0;
			while (!q1.empty()){
				BiNode *p = q1.front();
				q1.pop();
				w++;
				if (p->lchild) {
					q2.push(p->lchild);
				}
				if (p->rchild) {
					q2.push(p->rchild);
				}
			}
			if (w > maxWidth) maxWidth = w;
		}
		if (q1.empty()) {
			int w = 0;
			while (!q2.empty()){
				BiNode *p = q2.front();
				q2.pop();
				w++;
				if (p->lchild) {
					q1.push(p->lchild);
				}
				if (p->rchild) {
					q1.push(p->rchild);
				}
			}
			if (w > maxWidth) maxWidth = w;
		}
	}
	return maxWidth;
}

/*
	BiNode* head: ����ͷ���Ķ�����
	BiNode* p: ���������
	BiNode* q: ���������
	BiNode *&r: �������ͣ�����p��q������������Ƚ�� 
*/
void Ancestor(BiNode* head, BiNode* p, BiNode* q, BiNode *&r) {
	// ����˼·�����ú���������ص㣬������ջ�ֱ𴢴�p��q�����Ƚ��
	// ����ջ����Ԫ����ԽԶ��p��q�����Ƚ�� 
	// �������������αȽ�p��q�����Ƚ�㣬ֱ��ջ��Ԫ�ز���ͬΪֹ 
	if (!(head->lchild)) return;
	BiNode *t = head;
	stack<BiNode*> s, s1, s2;
	BiNode *last_pop = NULL;
	while (t || !s.empty()) {
		if (t) {
			s.push(t);
			t = t->lchild;
		} else {
			BiNode *e = s.top();
			if (e->rchild && e->rchild != last_pop) {
				s.push(e->rchild);
				t = s.top()->lchild;
			} else {
				s.pop();
				if (e == p || e == q) {
					// ��ʱ����s��Ԫ�أ����㻹ԭջs 
					stack<BiNode*> temp;
					while (!s.empty()) {
						temp.push(s.top());
						s.pop();
						if (e == p) {
							s1.push(temp.top());
						} 
						if (e == q) {
							s2.push(temp.top());
						}
					}
					while (!temp.empty()) {
						s.push(temp.top());
						temp.pop();
					}
				}
				last_pop = e;
			}
		}
	}
	while (!s1.empty() && !s2.empty() && 
		s1.top() == s2.top()) {
		r = s1.top();
		s1.pop();
		s2.pop();
	}
}

BiNode* initBiTree() {
	// �����������ӿյ�ͷ��� 
	BiTree T = createBiTree();
	BiNode *head = new(BiNode);
	head->lchild = T;
	head->rchild = NULL;
	return head;
}

bool printAncestors(BiTree B, ElemType x, bool& flag) {
//	if (B) {
//		if (B->data == x) return true;
//		if (!flag && printAncestors(B->lchild, x, flag)) {
//			flag = true;
//		}
//		if (!flag && printAncestors(B->rchild, x, flag)) {
//			flag = true;
//		}
//		if (flag) {
//			cout<<(B->data)<<" ";
//		}
//	}
//	return false;
	// ���������ջ�д����ջ��Ԫ�ذ��������������Ƚ�� 
	if (!B) return false;
	BiNode *p = B;
	stack<BiNode*> s;
	BiNode *last_pop = NULL;
	while (p || !s.empty()) {
		if (p) {
			if (p->data == x) {
				while (!s.empty()) {
					cout<<(s.top()->data)<<" ";
					s.pop();
				}
				return true;
			}
			s.push(p);
			p = p->lchild;
		} else {
			BiNode *q = s.top();
			if (q->rchild && q->rchild != last_pop) {
				s.push(q->rchild);
				p = s.top()->lchild;
			} else {
				s.pop();
				last_pop = q;
			}
		}
	}
}

void delTree(BiTree &B) { 
	if (B) {
		delTree(B->lchild);
		delTree(B->rchild);
		delete B;
	}
}

bool findAndDeleteNodeWithX(BiTree B, ElemType x) {
	if (B) {
		if (B->data == x) return true;
		if (findAndDeleteNodeWithX(B->lchild, x)) {
			delTree(B->lchild);
			B->lchild = NULL;
		}
		if (findAndDeleteNodeWithX(B->rchild, x)) {
			delTree(B->rchild);
			B->rchild = NULL;
		}
	}
	return false;
}

ElemType getDataByPreOrder(BiTree B, int num) {
	if (!B) return -1;
	stack<BiNode*> s;
	BiNode *p = B;
	int i = 0;
	while (p || !s.empty()) {
		while (p) {
			i++;
			if (num == i) return p->data;
			s.push(p);
			p = p->lchild;
		}
		BiNode *q = s.top();
		s.pop();
		if (q->rchild) {
			p = q->rchild;
		}
	}
	return -1; 
}

BiTree swapLeftAndRightTree1(BiTree B) {
	if (B) {
		BiNode *temp = B->lchild;
		B->lchild = B->rchild;
		B->rchild = temp;
		swapLeftAndRightTree1(B->lchild);
		swapLeftAndRightTree1(B->rchild);
	}
	return B;
}

BiTree swapLeftAndRightTree(BiTree B) {
	if (!B) return NULL;
	queue<BiNode*> q;
	q.push(B);
	while (!q.empty()) {
		BiNode *p = q.front(), *temp;
		q.pop();
		if (p->lchild) q.push(p->lchild);
		if (p->rchild) q.push(p->rchild);
		temp = p->lchild;
		p->lchild = p->rchild;
		p->rchild = temp;
	}
	return B;
}

int countDoubleOffspringsOfNodes(BiTree B) {
	if (!B) return 0;
	queue<BiNode*> q;
	q.push(B);
	int number = 0;
	while (!q.empty()) {
		BiNode *p = q.front();
		q.pop();
		if (p->lchild && p->rchild) {
			number++;
			q.push(p->lchild);
			q.push(p->rchild);
		} else {
			if (p->lchild) q.push(p->lchild);
			if (p->rchild) q.push(p->rchild);
		}
	}
	return number;
}

/*	
	�����ڵ�ֵ������ͬ
	pre[]: ������������
	in[]: ������������
	int s: �����������ʼλ��
	int e: ��������Ľ���λ�� 
	return BiTree: �������ɵĶ����� 
*/
BiTree PreAndIn1(int pre[], int in[], int s, int e) {
    if (s > e) return NULL;                      	
	BiNode *node = new(BiNode);
	int first = pre[0];
	node->data = first;
	int loca;
	for (loca = s; loca <= e && in[loca] != first; loca++);
	if (loca == e + 1) return NULL; 
	// ��ʼλ�õ�����ֹλ��˵����ʱ�����������һ��ֵ
	// û�����Һ��� 
	if (s == e) {
		node->lchild = node->rchild = NULL;
	} else {
		node->lchild = PreAndIn1(pre + 1, in, s, loca - 1);
//	    pre+loca+1-s������ע��loca-s���������������������  
		node->rchild = PreAndIn1(pre + loca + 1 - s, in, loca + 1, e);
	}
	return node;
}

/*	
	�����ڵ�ֵ������ͬ
	A[]: ������������
	B[]: ������������
	int len: ��Ҫ�������еĸ���
	return BiTree: �������ɵĶ����� 
*/ 
BiTree PreAndIn(int A[], int B[], int len) {
	// ����˼·: ��������������׸�ֵ��λ��loca 
	// ����loca������ֳ������ ��������������0~loca-1������������loca+1~len-1
	// ͬʱlocaҲ������ֳɸ����� ��������������1~loca������������loca+1~len-1 
	// ��left����������0��loca-1��ֵ��right����������loca+1��len-1��ֵ
	
	// ����Ϊ0˵��û�п��õ����� 
	if (len == 0) return NULL;
	int num = A[0];
	BiNode *node = new(BiNode);
	node->data = num;
	node->tag = 1;
	int loca = 0;
	for (; B[loca] != num && loca < len; loca++);
	// ����������û���ҵ���Ӧnum��ֵ��˵����������ߵĺ��� 
	if (loca == len) return NULL;
	// ���ȵ���1˵����û�����Һ��� 
	if (len == 1) {
		node->lchild = node->rchild = NULL;
	} else {
		int left[loca], right[len - loca - 1];
		memcpy(left, B, sizeof(int) * loca);
		memcpy(right, B + loca + 1, sizeof(int) * (len - loca - 1));
		node->lchild = PreAndIn(A + 1, left, loca);
		node->rchild = PreAndIn(A + loca + 1, right, len - loca - 1);
	}
	return node;
}

bool isCompleteTree(BiTree B) {
	if (!B) return true;
	int flag = 0; //0����û�г��ֹ�����Ϊ�յĽ�㣬��֮���෴
	// ����˼·�����������������Ϊ�յ������plus�������ĺ��Ӵ���������ȫ������ 
	// ��֮���� 
	queue<BiNode*> q;
	q.push(B);
	while (!q.empty()) {
		BiNode *p = q.front();
		q.pop();
		if (p->lchild) {
			if (flag) return false;
			q.push(p->lchild);
		} else {
			flag = 1;
		}
		if (p->rchild) {
			if (flag) return false;
			q.push(p->rchild);
		}
	}
	return true;
}

int getHeight2(BiTree B) { 
	queue<BiNode*> q;
	// lastָ��һ�����ұ߽��
	// rearָ����һ�����ұ߽�� 
	// ����˼·������frontָ��ǰ�����ʽ��Ĵ���
	// ͬʱ�������ָ����ĺ��ӣ�����о���ӣ�����rear++
	// ��front==last ��������last��ֵ������һ���ظ����� 
	int front = -1, rear = -1, level = 0, last = 0;
	q.push(B);
	rear++;
	while (!q.empty()) {
		BiNode *p = q.front();
		q.pop();
		front++;
		if (p->lchild) {
			q.push(p->lchild);
			rear++;
		}
		if (p->rchild) {
			q.push(p->rchild);
			rear++;
		}
		// front==last��ζ��һ��ķ����ѽ���
		// Ҳ˵�������ĺ��ӽ��ȫ����ӣ�rearҲ�ɹ�������һ������ұ߽��Ĵ��� 
		// ������һ��Ϊ��һ��ѭ������last����lastָ����һ�����ұ߽��Ĵ��� 
		if (front == last) {
			last = rear;
			level++;
		}
	}
	return level;
}

int getHeight1(BiTree B) {
	if (!B) return 0; 
	BiNode *p = B;
	stack<int> s; //����ÿһ����ĸ߶� 
	stack<BiNode*> s1; //����ÿһ���� 
	s.push(1); 
	s1.push(B);
	int height = 1;
	while (!s1.empty()) {
		int h = s.top();
//		cout<<"h: "<<h<<endl; 
		if (h > height) {
			height = h;
		}
		BiNode *q = s1.top();
		s1.pop();
		s.pop();
		if (q->rchild) {
			s1.push(q->rchild);
			s.push(h + 1);
		}
		if (q->lchild) {
			s1.push(q->lchild);
			s.push(h + 1);
		}
	}
	return height;
}

/*
	BiTree B: ������
*/ 
int getHeight(BiTree B) {
 	// ���ڶ������ĸ߶�Ϊmax(�������߶ȣ��������߶�)+1 
 	// +1����Ϊ���ڵ���߶�Ϊ1 
	if (!B) return 0;
	return 
		getHeight(B->lchild) > getHeight(B->rchild) ? 
			getHeight(B->lchild) + 1 : 
				getHeight(B->rchild) + 1;
}

/*
	BiTree B: ������
*/
void traverseByReLevelOrder(BiTree B) {
	// ����Ϊ��ʵ�ִ�������Ĳ�α��� 
	// ֻ�����������Һ��Ӽ��� 
	queue<BiNode*> q;
	q.push(B);
	while (!q.empty()) {
		BiNode *p = q.front();
		cout<<(p->data)<<" ";
		q.pop();
		if (p->rchild) {
			q.push(p->rchild);
		}
		if (p->lchild) {
			q.push(p->lchild);
		}
	}
}

/*
	BiTree B: ������
*/
void traverseByPostOrder1(BiTree B) {
	if (!B) return;
	BiNode *p = B; //����û�����ʹ��������Ľ������ǿս�� 
	stack<BiNode*> s; //������ջ������ջ��Ԫ�ص�һ�������Ƚ�� 
	// ���ں���÷��ʺ������������������ܷ��ʸ����
	// Ϊ�˱����ظ��������������������п��Ե���������������������
	// ��������������Ҳ���ȱ����ʣ����Բ��ܵ������
	// ����Ϊ������������ϻ���ݵ����ڵ㣬Ϊ�˱����ظ����������� 
	// ������last_pop�����ѱ����ʵĽ�� 
	BiNode *last_pop = NULL;
	while (p || !s.empty()) {
		if (p) {
			s.push(p);
			p = p->lchild;
		} else {
			BiNode *q = s.top();
			// ����������δ�����ʹ��Ľ�㣬
			// ��p����ý������� 
			if (q->rchild && q->rchild != last_pop) {
				s.push(q->rchild);
				p = s.top()->lchild;
			} else {
				cout<<(q->data)<<" ";
				s.pop();
				last_pop = q;
			}
		}
	}
}

void traverseByPostOrder(BiTree B) {
	if (B) {
		traverseByPostOrder(B->lchild);
		traverseByPostOrder(B->rchild);
		cout<<(B->data)<<" ";
	}
}

/*
	return BiNode*: �����������ɵĶ����� 
*/
BiNode* createBiTree() {
	BiNode* node;
	ElemType data;
	cin>>data;
	// data = -1�������λ�ò������½�� 
	if (data != -1) {
		node = new(BiNode);
		node->data = data;
		node->tag = 1;
		node->lchild = createBiTree();
		node->rchild = createBiTree();
	} else {
		node = NULL;
	}
	return node;
}

void traverseByPreOrder(BiTree B) {
	if (B != NULL) {
		cout<<(B->data)<<" ";
		traverseByPreOrder(B->lchild);
		traverseByPreOrder(B->rchild);
	}
}

/*
	BiTree B: ������ 
*/
void traverseByPreOrder1(BiTree B) {
	stack<BiNode*> s; // �������϶��µ��ҽ�� 
	BiNode *p = B; // p��һ�α������㣬���󱣴���Ҫ�������������������ĵ�һ����� 
	// !s.empty()����ջ�б�����ǰһ��ѭ�����������Ľ�����Һ��� 
	while (p || !s.empty()) {
		// ��ѭ���������������ֵ 
		while (p) {
			cout<<(p->data)<<" ";
			// ���������Ƿ��ʺ��������ͷ����������ĵ�һ��
			// ��������Ҫ�ѽ����Һ�������ջ�� 
			if (p->rchild) {
				s.push(p->rchild);
			}
			p = p->lchild;
		}
		// ȡ�����������һ�������������ĵ�һ����㣬������ 
		// ��p��������������һ��ѭ���������������� 
		if (!s.empty()) {
			p = s.top();
			s.pop();
		}
	}
}

/*
	BiTree B: ������ 
*/
void traverseByPreOrder2(BiTree B) {
	stack<BiNode*> s; // ������û�б����ʹ��Һ��ӵĽ�� 
	BiNode *p = B; // ����û�б����ʹ����ӵĽ�� 
	while (p || !s.empty()) {
		if (p) {
			cout<<(p->data)<<" ";
			s.push(p);
			p = p->lchild;
		} else {
			p = s.top();
			s.pop();
			p = p->rchild;
		}
	}
}

/*
	BiTree B: ������
*/
void traverseByLevelOrder(BiTree B) {
	// ʹ�ö��д��û�з��ʵ����Һ��ӵĽ�� 
	// ���ʶ��׾����ֵ���������������ĺ��ӽ�� 
	if (B == NULL) return;
	queue<BiNode*> q;
	q.push(B);
	while (!q.empty()) {
		BiNode *p = q.front();
		cout<<(p->data)<<" ";
		q.pop();
		if (p->lchild) {
			q.push(p->lchild);
		}
		if (p->rchild) {
			q.push(p->rchild);
		}
	}
}

void traverseByMidOrder(BiTree B) {
	if (B != NULL) {
		traverseByMidOrder(B->lchild);
		cout<<(B->data)<<" ";
		traverseByMidOrder(B->rchild);
	}
}

/*
	BiTree B: ������
*/
void traverseByMidOrder1(BiTree B) { 
	if (B == NULL) return;
	stack<BiNode*> s;
	s.push(B);
	while (!s.empty()) {
		BiNode *p = s.top();
		// �����������ʺ����������ٻ��ݵ���������˫�׽��  
		// �����ظ������������������������tag����������Ƿ��Ѿ������ʹ� 
		if (p->lchild && p->lchild->tag) {
			s.push(p->lchild);
		} else {
			// û�����ӻ����Ѿ����ʺ���������ֱ��������ֵ 
			cout<<p->data<<" ";
			// ��Ǹý���������������� 
			p->tag = 0;
			s.pop();
			// ��ʼ���������� 
			if (p->rchild) {
				s.push(p->rchild);
			}
		}
	}
}

/*
	BiTree B: ������
*/
void traverseByMidOrder2(BiTree B) {
	stack<BiNode*> s;
	BiNode *p = B;
	while (p || !s.empty()) {
		// ������ȫ����ջ 
		while (p) {
			s.push(p);
			p = p->lchild;
		}
		// qҪô��û�����ӵĽ�㣬Ҫô���������Ѿ�������ϵĽ�� 
		BiNode *q = s.top();
		cout<<(q->data)<<" "; 
		s.pop();
		// ���������� 
		if (q->rchild) {
			p = q->rchild;
		}
	}
}

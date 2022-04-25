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
// 加头结点 
BiNode* initBiTree();
void traverseByLevelOrder(BiTree);
// 从右向左 
void traverseByReLevelOrder(BiTree);
void traverseByPreOrder(BiTree);
// 非递归先序 
void traverseByPreOrder1(BiTree);
// 非递归先序 
void traverseByPreOrder2(BiTree);
void traverseByMidOrder(BiTree);
// 非递归中序 
void traverseByMidOrder1(BiTree);
// 非递归中序 
void traverseByMidOrder2(BiTree);
void traverseByPostOrder(BiTree);
// 非递归后序 
void traverseByPostOrder1(BiTree);
// 递归求树高度 
int getHeight(BiTree);
// 非递归求树高度 
int getHeight1(BiTree);
int getHeight2(BiTree);
bool isCompleteTree(BiTree);
// 先序和中序形成二叉树
BiTree PreAndIn(int[], int[], int);
BiTree PreAndIn1(int[], int[], int, int);
BiTree PreAndIn2(int[], int[], int, int, int, int);
// 统计双分支结点个数 
int countDoubleOffspringsOfNodes(BiTree);
// 交换所有结点的左右子树 
BiTree swapLeftAndRightTree(BiTree);
BiTree swapLeftAndRightTree1(BiTree);
// 得到先序遍历序列的第k的结点的data 
ElemType getDataByPreOrder(BiTree, int);
void delTree(BiTree&); 
bool findAndDeleteNodeWithX(BiTree, ElemType);
// 打印值为x的所有祖先结点的值 
bool printAncestors(BiTree, ElemType, bool&);
// 找到p,r最近的公共祖先结点 
void Ancestor(BiNode*, BiNode*, BiNode*, BiNode*);
// 返回空结点 
BiNode* resEmptyNode();
// 返回二叉树具有结点数最多的那一层的结点个数 
// 轮换使用两个队列 
int getBiTreeWidth(BiTree); 
// 插入空结点来隔开每一层的结点 
int getBiTreeWidth1(BiTree);
// 将叶结点从左向右连成一个单链表 
BiNode* linkAllLeafNodes(BiTree);
BiNode* linkAllLeafNodes1(BiTree, BiNode*&);
// 判断两个二叉树是否相似 
bool is_SimilarTree(BiTree, BiTree);
bool is_SimilarTree1(BiTree, BiTree);
// 在满二叉树中，已知先序序列求后序序列 
void PreToPost(int[], int, int, int[], int, int);
// 中序和后序形成二叉树 
BiTree PostAndIn(int[], int[], int, int, int, int);
// 判断是否为二叉排序树 
bool is_BSTree(BiTree);
// 判断是否为平衡二叉树 
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
		// 先操作左子树和右子树，自下而上执行 
		is_AVL1(T->lchild, bl, hl);
		is_AVL1(T->rchild, br, hr);
		if (abs(hl - hr) > 1) {
			balance = false;
		} else {
			// 满足了平衡二叉树的左子树和右子树的高度差不能大于1
			// 还需满足左右子树都是平衡二叉树 
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
	pre[]: 先序数组
	in[]: 中序数组
	prel: 先序数组的起始位置
	prer: 先序数组的结束位置 
	inl: 中序数组的起始位置
	inr: 中序数组的结束位置
*/
BiTree PreAndIn2(int pre[], int in[], int prel, int prer, int inl, int inr) {
	// 序号:  0       1 2 3  4  5  6  7 8 9 10 11 12 13 14
	// pre:   1(prel) 2  4  6 11 12 13 14 7        3  5  8  9 10 15(prer)
	// in:   11(inl)  6 13 12 14  4  7  2 1(pivot) 3  8 10  9  5 15(inr)
	// 总体思路是由先序数组的起始位置的值去找到在中序数组的位置pivot，对先序和中序进行划分 
	// 那么pivot将先序分成prel(根)prel+1~pivot-inl+prel(左子树结点)pivot-inl+prel+1~prer(右子树结点)
	// 中序分成inl~pivot-1(左子树结点)pivot(根)pivot+1~inr(右子树结点)
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
	post[]: 后序数组
	in[]: 中序数组
	postl: 后序数组的起始位置
	postr: 后序数组的结束位置 
	inl: 中序数组的起始位置
	inr: 中序数组的结束位置
*/
BiTree PostAndIn(int post[], int in[], int postl, int postr, int inl, int inr) {
	// 总体思路是由后序数组的结束位置的值去找到在中序数组的位置pivot，对后序和中序进行划分 
	// 那么pivot将后序分成postl~postl+pivot-inl-1(左子树结点)postl+pivot-inl~postr-1(右子树结点)postr(根)
	// 中序分成inl~pivot-1(左子树结点)pivot(根)pivot+1~inr(右子树结点)
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
	pre[]: 先序数组
	s1: 先序起始位置
	e1: 先序结尾位置
	post[]: 后序数组
	s2: 后序起始位置
	e2: 后序结尾位置 
	func: （满二叉树）由先序数组得出后序数组 
*/
void PreToPost(int pre[], int s1, int e1, int post[], int s2, int e2) {
	// 总体思路是先序数组分成根左右，后序数组是左右根
	// 先序数组的起始值肯定是根节点的值，那么后序根又是最后
	// 则将其赋给后序的末尾位置。由于是满二叉树，每个结点除了叶子结点都是满二叉树
	// 所以每个结点的左子树和右子树的个数必是floor(总个数/2)， 
	if (e1 >= s1) {
		int half = (e1 - s1) / 2;// 可以当成左子树或右子树的个数 
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
	// 方便getBiTreeWidth1函数插入用作隔板的结点 
	BiNode* p = new(BiNode);
	p->data = -999;
	p->lchild = NULL;
	p->rchild = NULL;
	return p;
}

int getBiTreeWidth1(BiTree B) {
	// 总体思路是给每一层最后一个结点后面插入空结点，分隔下一层的结点。 
	// 初始化w=0，每次遍历一个元素，就w++，将它的孩子结点入队，并让它出队 
	// 直到遇到空结点，那么w就是这一层的宽度，与maxWidth比较。重新设置w=0，
	// 同时下一层的结点已经全部入队，再末尾插入空结点，重复操作 
	if (!B) return 0;
	queue<BiNode*> q;
	q.push(B);
	q.push(resEmptyNode());
	int maxWidth = -1;
	int w = 0;
	// 如果该结点既是空结点，宽度也是0，意味着在空结点前面的所有结点没有孩子结点 
	// 这一层为空，那么则结束循环 
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
	// 总体思路是q1，q2轮换使用，具体是q1先储存根结点
	// 把q1储存的结点一边弹出，一边记录个数，一边让它的孩子入队q2， 
	// q1为空则这一层的宽度也就得到了，同理，q2也执行这一操作，q1就储存
	// 了q2所有结点的孩子结点，同时也就得到了这一层的宽度 
	// 宽度就取这些操作中宽度的最大值 
	if (!B) return 0; 
	queue<BiNode*> q1;
	queue<BiNode*> q2;
	q1.push(B);
	int maxWidth = -1;
	// 结束循环的条件是q1和q2同时为空 
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
	BiNode* head: 带有头结点的二叉树
	BiNode* p: 二叉树结点
	BiNode* q: 二叉树结点
	BiNode *&r: 引用类型，返回p和q的最近公共祖先结点 
*/
void Ancestor(BiNode* head, BiNode* p, BiNode* q, BiNode *&r) {
	// 总体思路是利用后序遍历的特点，用两个栈分别储存p、q的祖先结点
	// 靠近栈顶的元素是越远离p、q的祖先结点 
	// 遍历结束后，依次比较p、q的祖先结点，直到栈顶元素不相同为止 
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
					// 临时储存s的元素，方便还原栈s 
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
	// 给二叉树增加空的头结点 
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
	// 后序遍历中栈中存放着栈顶元素包括它的所有祖先结点 
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
	各个节点值各不相同
	pre[]: 保存先序序列
	in[]: 保存中序序列
	int s: 中序数组的起始位置
	int e: 中序数组的结束位置 
	return BiTree: 返回生成的二叉树 
*/
BiTree PreAndIn1(int pre[], int in[], int s, int e) {
    if (s > e) return NULL;                      	
	BiNode *node = new(BiNode);
	int first = pre[0];
	node->data = first;
	int loca;
	for (loca = s; loca <= e && in[loca] != first; loca++);
	if (loca == e + 1) return NULL; 
	// 起始位置等于终止位置说明此时的中序数组就一个值
	// 没有左右孩子 
	if (s == e) {
		node->lchild = node->rchild = NULL;
	} else {
		node->lchild = PreAndIn1(pre + 1, in, s, loca - 1);
//	    pre+loca+1-s，这里注意loca-s等于中序的左子树结点个数  
		node->rchild = PreAndIn1(pre + loca + 1 - s, in, loca + 1, e);
	}
	return node;
}

/*	
	各个节点值各不相同
	A[]: 保存先序序列
	B[]: 保存中序序列
	int len: 需要操作序列的个数
	return BiTree: 返回生成的二叉树 
*/ 
BiTree PreAndIn(int A[], int B[], int len) {
	// 总体思路: 中序里查找先序首个值的位置loca 
	// 并用loca将中序分成左根右 具体左子树结点从0~loca-1，右子树结点从loca+1~len-1
	// 同时loca也将先序分成根左右 具体左子树结点从1~loca，右子树结点从loca+1~len-1 
	// 用left保存中序中0到loca-1的值，right保存中序中loca+1到len-1的值
	
	// 长度为0说明没有可用的序列 
	if (len == 0) return NULL;
	int num = A[0];
	BiNode *node = new(BiNode);
	node->data = num;
	node->tag = 1;
	int loca = 0;
	for (; B[loca] != num && loca < len; loca++);
	// 在中序序列没有找到对应num的值，说明不存在这边的孩子 
	if (loca == len) return NULL;
	// 长度等于1说明它没有左右孩子 
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
	int flag = 0; //0代表没有出现过左孩子为空的结点，反之则相反
	// 总体思路就是如果出现了左孩子为空的情况，plus后续结点的孩子存在则不是完全二叉树 
	// 反之则是 
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
	// last指向一层最右边结点
	// rear指向下一层最右边结点 
	// 总体思路就是用front指向当前被访问结点的次序
	// 同时检查它所指向结点的孩子，如果有就入队，并对rear++
	// 当front==last 重新设置last的值，对下一层重复操作 
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
		// front==last意味着一层的访问已结束
		// 也说明这层结点的孩子结点全部入队，rear也成功保存下一层的最右边结点的次序 
		// 层数加一，为下一层循环设置last，让last指向下一层最右边结点的次序 
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
	stack<int> s; //保存每一层结点的高度 
	stack<BiNode*> s1; //保存每一层结点 
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
	BiTree B: 二叉树
*/ 
int getHeight(BiTree B) {
 	// 由于二叉树的高度为max(右子树高度，左子树高度)+1 
 	// +1是因为根节点算高度为1 
	if (!B) return 0;
	return 
		getHeight(B->lchild) > getHeight(B->rchild) ? 
			getHeight(B->lchild) + 1 : 
				getHeight(B->rchild) + 1;
}

/*
	BiTree B: 二叉树
*/
void traverseByReLevelOrder(BiTree B) {
	// 这里为了实现从右向左的层次遍历 
	// 只需优先推入右孩子即可 
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
	BiTree B: 二叉树
*/
void traverseByPostOrder1(BiTree B) {
	if (!B) return;
	BiNode *p = B; //保存没被访问过左子树的结点或者是空结点 
	stack<BiNode*> s; //保存着栈顶包括栈顶元素的一连串祖先结点 
	// 由于后序得访问好左子树和右子树才能访问根结点
	// 为了避免重复访问左子树，在中序中可以弹出根结点来避免这种情况
	// 但根结点的右子树也得先被访问，所以不能弹出结点
	// 又因为右子树访问完毕会回溯到根节点，为了避免重复访问右子树 
	// 可以用last_pop保存已被访问的结点 
	BiNode *last_pop = NULL;
	while (p || !s.empty()) {
		if (p) {
			s.push(p);
			p = p->lchild;
		} else {
			BiNode *q = s.top();
			// 推入右子树未被访问过的结点，
			// 用p保存该结点的左孩子 
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
	return BiNode*: 返回先序生成的二叉树 
*/
BiNode* createBiTree() {
	BiNode* node;
	ElemType data;
	cin>>data;
	// data = -1代表这个位置不插入新结点 
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
	BiTree B: 二叉树 
*/
void traverseByPreOrder1(BiTree B) {
	stack<BiNode*> s; // 保存自上而下的右结点 
	BiNode *p = B; // p第一次保存根结点，往后保存需要操作左子树的右子树的第一个结点 
	// !s.empty()代表栈中保存着前一次循环的左子树的结点有右孩子 
	while (p || !s.empty()) {
		// 边循环左子树，边输出值 
		while (p) {
			cout<<(p->data)<<" ";
			// 由于先序是访问好左子树就访问右子树的第一个
			// 所以这里要把结点的右孩子推入栈中 
			if (p->rchild) {
				s.push(p->rchild);
			}
			p = p->lchild;
		}
		// 取出左子树最后一个结点的右子树的第一个结点，并弹出 
		// 用p保存它，方便下一次循环操作它的左子树 
		if (!s.empty()) {
			p = s.top();
			s.pop();
		}
	}
}

/*
	BiTree B: 二叉树 
*/
void traverseByPreOrder2(BiTree B) {
	stack<BiNode*> s; // 保存着没有被访问过右孩子的结点 
	BiNode *p = B; // 保存没有被访问过左孩子的结点 
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
	BiTree B: 二叉树
*/
void traverseByLevelOrder(BiTree B) {
	// 使用队列存放没有访问到左右孩子的结点 
	// 访问队首就输出值、弹出、推入它的孩子结点 
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
	BiTree B: 二叉树
*/
void traverseByMidOrder1(BiTree B) { 
	if (B == NULL) return;
	stack<BiNode*> s;
	s.push(B);
	while (!s.empty()) {
		BiNode *p = s.top();
		// 由于中序会访问好左子树，再回溯到左子树的双亲结点  
		// 避免重复访问左子树，这里给结点添加tag标记左子树是否已经被访问过 
		if (p->lchild && p->lchild->tag) {
			s.push(p->lchild);
		} else {
			// 没有左孩子或者已经访问好左子树，直接输出结点值 
			cout<<p->data<<" ";
			// 标记该结点的左子树访问完毕 
			p->tag = 0;
			s.pop();
			// 开始操作右子树 
			if (p->rchild) {
				s.push(p->rchild);
			}
		}
	}
}

/*
	BiTree B: 二叉树
*/
void traverseByMidOrder2(BiTree B) {
	stack<BiNode*> s;
	BiNode *p = B;
	while (p || !s.empty()) {
		// 将左孩子全部进栈 
		while (p) {
			s.push(p);
			p = p->lchild;
		}
		// q要么是没有左孩子的结点，要么是左子树已经访问完毕的结点 
		BiNode *q = s.top();
		cout<<(q->data)<<" "; 
		s.pop();
		// 操作右子树 
		if (q->rchild) {
			p = q->rchild;
		}
	}
}

#include<iostream>
#define ElemType int
using namespace std;

int t = 0;

typedef struct ThreadNode {
	ElemType data;
	struct ThreadNode* lchild, *rchild;
	int ltag, rtag;
} ThreadNode, *ThreadTree;

// 先序建立二叉树 
ThreadTree createTree();
void traverseByMidOrder(ThreadTree);
ThreadTree createThreadNode();
void createThreadTree(ThreadTree);
void ThreadifyNode(ThreadNode*, ThreadNode**);
ThreadNode* FirstNode(ThreadNode*);
ThreadNode* NextNode(ThreadNode*);
void traverseByThread(ThreadTree);
// 找到指定的结点在后序遍历的前继结点 
ThreadNode* ch5_533_18(ThreadNode*);

void test() {
	ThreadTree T = createTree();
	createThreadTree(T);
	traverseByThread(T);
//	traverseByMidOrder(T);
	cout<<ch5_533_18(T->lchild->lchild->lchild->lchild);
}

int main () {
	test();
	return 0;
}

ThreadNode* ch5_533_18(ThreadNode* p) {
	if (!p) return NULL;
	// 如果一个结点有右孩子，那么后序遍历前继结点必定是它的右孩子 
	if (p->rtag == 0) {
		return p->rchild;
	}
	// 如果左孩子存在右孩子不存在，那么后序遍历前继结点必定是它的左孩子 
	if (p->ltag == 0 && p->rtag == 1) {
		return p->lchild;
	}
	// 左右孩子都不存在，那么前继结点应该是双亲结点的左孩子 
	ThreadNode *q = p;
	for (; q && q->ltag; q = q->lchild);
	if (q) {
		return q->lchild;
	} else {
		return NULL;
	}
}

void traverseByThread(ThreadTree T) {
	ThreadNode *p;
	for (p = FirstNode(T); p; p = NextNode(p)) {
		cout<<(p->data)<<" ";
	}
	cout<<endl;
}

ThreadNode* NextNode(ThreadNode* node) {
	// 左子树为空的结点下一个结点要么是它的右子树最左下的结点 
	// 要么是它的后继线索结点 
	if (node->rtag == 0) {
		return FirstNode(node->rchild);
	} else {
		return node->rchild;
	}
}

ThreadNode* FirstNode(ThreadNode* node) {
	// 第一个结点肯定是左孩子为空的结点 
	if (node) {
		if (node->ltag == 1) {
			return node;
		}
		if (node->ltag == 0) {
			FirstNode(node->lchild);
		}
	}
}

/*
	ThreadNode* node: 未线索化的二叉树结点 
	ThreadNode** pre: 二重指针，指向前一个线索化的结点，也保证递归栈里的函数用的是同一个pre 
*/
void ThreadifyNode(ThreadNode* node, ThreadNode **pre) {
	if (node == NULL) return;
	ThreadifyNode(node->lchild, pre);
	if (node->lchild == NULL) {
		node->ltag = 1;
		node->lchild = *pre;
	} 
// 应对没有初始化ltag或rtag的操作 
//	else {
//		node->ltag = 0;
//	}
	if (*pre) {
		if ((*pre)->rchild == NULL) {
			(*pre)->rtag = 1;
			(*pre)->rchild = node;
		} 
// 应对没有初始化ltag或rtag的操作
//		else {
//			(*pre)->rtag = 0;
//		}
	}
	*pre = node;
	ThreadifyNode(node->rchild, pre);
}

void createThreadTree(ThreadTree T) {
	ThreadNode *pre = NULL;
	ThreadifyNode(T, &pre);
	pre->rchild = NULL;
	pre->rtag = 1;
}

ThreadNode* createTree() {
	ThreadNode* node;
	ElemType data;
	cin>>data;
	if (data != -1) {
		node = new(ThreadNode);
		node->data = data;
		node->ltag = node->rtag = 0; 
		node->lchild = createTree();
		node->rchild = createTree();
	} else {
		node = NULL;
	}
	return node;
}

void traverseByMidOrder(ThreadTree B) {
	if (B != NULL) {
		if (B->ltag == 0) {
			traverseByMidOrder(B->lchild);
		}
		cout<<"data: "<<(B->data)<<endl;
		cout<<"addr: "<<B<<endl;
		cout<<"ltag: "<<(B->ltag)<<endl;
		cout<<"rtag: "<<(B->rtag)<<endl;
		cout<<"lchild: "<<(B->lchild)<<endl;
		cout<<"rchild: "<<(B->rchild)<<endl;
		if (B->lchild) {
			cout<<"B->lchild->data: "<<(B->lchild->data)<<endl;
		}
		if (B->rchild) {
			cout<<"B->rchild->data: "<<(B->rchild->data)<<endl;
		}
		cout<<endl;
		if (B->rtag == 0) {
			traverseByMidOrder(B->rchild);
		}
	}
}

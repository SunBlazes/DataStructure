#include<iostream>
#define ElemType int
using namespace std;

int t = 0;

typedef struct ThreadNode {
	ElemType data;
	struct ThreadNode* lchild, *rchild;
	int ltag, rtag;
} ThreadNode, *ThreadTree;

// ������������ 
ThreadTree createTree();
void traverseByMidOrder(ThreadTree);
ThreadTree createThreadNode();
void createThreadTree(ThreadTree);
void ThreadifyNode(ThreadNode*, ThreadNode**);
ThreadNode* FirstNode(ThreadNode*);
ThreadNode* NextNode(ThreadNode*);
void traverseByThread(ThreadTree);
// �ҵ�ָ���Ľ���ں��������ǰ�̽�� 
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
	// ���һ��������Һ��ӣ���ô�������ǰ�̽��ض��������Һ��� 
	if (p->rtag == 0) {
		return p->rchild;
	}
	// ������Ӵ����Һ��Ӳ����ڣ���ô�������ǰ�̽��ض����������� 
	if (p->ltag == 0 && p->rtag == 1) {
		return p->lchild;
	}
	// ���Һ��Ӷ������ڣ���ôǰ�̽��Ӧ����˫�׽������� 
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
	// ������Ϊ�յĽ����һ�����Ҫô�����������������µĽ�� 
	// Ҫô�����ĺ��������� 
	if (node->rtag == 0) {
		return FirstNode(node->rchild);
	} else {
		return node->rchild;
	}
}

ThreadNode* FirstNode(ThreadNode* node) {
	// ��һ�����϶�������Ϊ�յĽ�� 
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
	ThreadNode* node: δ�������Ķ�������� 
	ThreadNode** pre: ����ָ�룬ָ��ǰһ���������Ľ�㣬Ҳ��֤�ݹ�ջ��ĺ����õ���ͬһ��pre 
*/
void ThreadifyNode(ThreadNode* node, ThreadNode **pre) {
	if (node == NULL) return;
	ThreadifyNode(node->lchild, pre);
	if (node->lchild == NULL) {
		node->ltag = 1;
		node->lchild = *pre;
	} 
// Ӧ��û�г�ʼ��ltag��rtag�Ĳ��� 
//	else {
//		node->ltag = 0;
//	}
	if (*pre) {
		if ((*pre)->rchild == NULL) {
			(*pre)->rtag = 1;
			(*pre)->rchild = node;
		} 
// Ӧ��û�г�ʼ��ltag��rtag�Ĳ���
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

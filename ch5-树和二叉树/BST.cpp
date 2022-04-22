#include<iostream>
#define ElemType int
using namespace std; 

typedef struct _node {
	ElemType data;
	struct _node *lchild, *rchild;
} BSTNode, *BSTree;

BSTree createBSTree();
bool insertIntoBSTree(BSTree&, ElemType);
// 非递归实现插入 
bool insertIntoBSTree1(BSTree, ElemType);
void traverseByInOrder(BSTree);
int getLevel(BSTree, int);
void getMaxAndMin(BSTree, int&, int&);
// 从大到小输出不小于k的关键字 
void ch5_5_5_10(BSTree, int);

void test() {
	BSTree T = createBSTree();
	traverseByInOrder(T->lchild);
	cout<<"data: 90在第"<<getLevel(T->lchild, 90)<<"层\n";
	int max, min;
	getMaxAndMin(T, max, min);
	cout<<"max: "<<max<<", min: "<<min<<endl;
	ch5_5_5_10(T->lchild, 8);
}

int main () {
	test();
	return 0;
}

void ch5_5_5_10(BSTree B, int k) {
	if (!B) return;
	ch5_5_5_10(B->rchild, k);
	if (B->data >= k) cout<<(B->data)<<" ";
	ch5_5_5_10(B->lchild, k);
}

void getMaxAndMin(BSTree T, int& max, int& min) {
	BSTNode *p = T->lchild;
	for (; p && p->lchild; p = p->lchild);
	min = p->data;
	for (p = T->lchild; p->rchild; p = p->rchild);
	max = p->data;
}

int getLevel(BSTree T, int data) {
	BSTNode *p = T;
	int level = 0;
	while (p) {
		level++;
		if (p->data == data) {
			return level;
		}
		if (p->data > data) {
			p = p->lchild;
		} else {
			p = p->rchild;
		}
	}
	return -1;
}

/*
	BSTree Head: 头结点，减少了对第一个结点的额外处理 
	ElemType data: 插入元素的值	 
	return bool: 是否插入成功 
*/
bool insertIntoBSTree1(BSTree Head, ElemType data) {
	BSTNode *pre = Head, *p = Head->lchild;
	int dire = 0; //0代表左孩子 1代表右孩子 
	while (p) {
		if (p->data == data) return false;
		pre = p;
		if (p->data > data) {
			p = p->lchild;
			dire = 0;
		} else {
			p = p->rchild;
			dire = 1;
		}
		
	}
	if (!dire) {
		pre->lchild = new(BSTNode);
		pre->lchild->data = data;
		pre->lchild->lchild = pre->lchild->rchild = NULL;
	} else {
		pre->rchild = new(BSTNode);
		pre->rchild->data = data;
		pre->rchild->lchild = pre->rchild->rchild = NULL;
	}
	return true;
}

/*
	BSTree &T: 引用，方便添加结点
	ElemType data: 插入元素的值	 
	return bool: 是否插入成功 
*/
bool insertIntoBSTree(BSTree &T, ElemType data) {
	// 插入的位置都是叶节点的左右孩子 
	if (T == NULL) {
		T = new(BSTNode); //这里传入的T是引用类型 
		T->lchild = T->rchild = NULL;
		T->data = data;
		return true; //插入成功 
	} else if (data == T->data) {
		return false; // 排序二叉树要求不能有重复值 
	} else if (T->data > data) {
		return insertIntoBSTree(T->lchild, data);
	} else {
		return insertIntoBSTree(T->rchild, data);
	}
}

BSTree createBSTree() {
	BSTNode *head;
	ElemType data;
	head = new(BSTNode);
	head->lchild = head->rchild = NULL;
	cin>>data;
	while (data != -1) {
//		insertIntoBSTree(head->lchild, data);
		insertIntoBSTree1(head, data);
		cin>>data;
	}
	return head;
}
void traverseByInOrder(BSTree B) {
	if (B != NULL) {
		traverseByInOrder(B->lchild);
		cout<<(B->data)<<" ";
		traverseByInOrder(B->rchild);
	}
}

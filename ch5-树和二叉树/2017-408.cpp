#include<iostream>
#include<stack>
using namespace std;

typedef struct node {
	char data[10];
	struct node *left, *right;
} BTree;

BTree* createTree() {
	BTree *node = new(BTree);
	cin>>(node->data);
	if (node->data[0] != '#') {
		node->left = createTree();
		node->right = createTree();
	} else {
		return NULL;
	}
	return node;
}

void Output(BTree *t) {
	if (t){
		cout<<(t->data)<<" ";
		Output(t->left);
		Output(t->right);
	}
}

void handler1(BTree *T, int deep) {
	if (!T) return; 
	if (!T->left && !T->right) {
		cout<<(T->data);
	} else {
		if (deep > 1) cout<<"(";
		handler1(T->left, deep + 1);
		cout<<(T->data);
		handler1(T->right, deep + 1);
		if (deep > 1) cout<<")";
	}
}

void handler(BTree *T) {
	handler1(T, 1);
}

int main () {
	BTree *p = createTree();
	handler(p);
}

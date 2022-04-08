#include<iostream>
#include<map>
#include<string>
using namespace std;

map<char, string> map_codes;

typedef struct _node {
	int data;
	char ch;
	struct _node *lchild, *rchild;
} Node, *BTree; 

char chs[6] = {'a', 'b', 'c', 'd', 'e', 'f'};
int data[11] = {10, 7, 3, 9, 8, 1};
BTree T;

Node* createNode(int, char ch = ' ', Node* lchild = NULL, Node* rchild = NULL);
BTree createHFTree(int*, int);
void select2Min(int*, int len, int&, int&, bool*);
void traverse(BTree);
void Encode(char*, int*, int);
void EncodeHandler(BTree, char, int, Node* &child);
string Decode(BTree, string, int pos = 0);

int main () {
	T = createHFTree(data, 6);
//	traverse(T);
	Encode(chs, data, 6);
//	traverse(T);
//	cout<<map_codes['f'];
	string codes;
	cin>>codes;
	cout<<Decode(T, codes);
	return 0;
}

string Decode(BTree BT, string codes, int pos) {
	if (pos > codes.length()) return "";
	string str = "";    
	if (BT->ch != ' ') {
		str += string(1, BT->ch);
		if (codes.length() >= pos) {
			BT = T;
		}
	}
	if (BT) {
		if (codes[pos] == '1') {
			str += Decode(BT->lchild, codes, pos + 1);
		}
		if (codes[pos] == '0') {
			str += Decode(BT->rchild, codes, pos + 1);
		}
	}
	return str;
}

void EncodeHandler(BTree T, char c, int v, Node* &child) {
	if (!T) return;
	EncodeHandler(T->lchild, c, v, child);
	EncodeHandler(T->rchild, c, v, child);
	if (T->data == v && (!T->lchild && !T->rchild)) {
		child = T;
	}
	if (T->lchild && T->lchild == child) {
		child = T;
		map_codes[c] = "1" + map_codes[c];
	}
	if (T->rchild && T->rchild == child) {
		child = T;
		map_codes[c] = "0" + map_codes[c];
	}
}

void Encode(char *chs, int *data, int len) {
	for (int i = 0; i < len; i++) {
		map_codes.insert(pair<char, string>(chs[i], ""));
		Node *child = NULL;
		EncodeHandler(T, chs[i], data[i], child);
	} 
}

void traverse(BTree T) {
	if (T) {
		cout<<T->data<<" "<<T->ch<<endl;
		traverse(T->lchild);
		traverse(T->rchild);
	}
}

void select2Min(int *data, int len, int& loca1, int& loca2, bool *visited) {
	int min1 = ~(1<<31), min2 = ~(1<<31);
	for(int i = 0; i < len; i++) {
		if (visited[i]) continue;
		if (data[i] < min1) {
			min2 = min1;
			loca2 = loca1;
			min1 = data[i];
			loca1 = i;
		} else if (data[i] < min2) {
			min2 = data[i];
			loca2 = i;
		}
	}
	visited[loca1] = visited[loca2] = true;
}

BTree createHFTree(int arr[], int len) {
	BTree forests[2 * len - 1];
	bool visited[2 * len - 1];
	for (int i = 0; i < 2 * len - 1; i++) {
		visited[i] = false;
		forests[i] = createNode(arr[i], i < len ? chs[i] : ' ');
	}
	for (int i = 0; i < len - 1; i++) {
		int loca1 = 0, loca2 = 0;
		select2Min(arr, len + i, loca1, loca2, visited);
		arr[len + i] = arr[loca1] + arr[loca2];
		forests[len + i]->data = arr[len + i];
		forests[len + i]->lchild = forests[loca1];
		forests[len + i]->rchild = forests[loca2];
	}
	return forests[2 * len - 2];
}

Node* createNode(int data, char ch, Node* lchild, Node* rchild) {
	Node *node = new Node;
	node->data = data;
	node->lchild = lchild;
	node->rchild = rchild;
	node->ch = ch;
	return node;
}

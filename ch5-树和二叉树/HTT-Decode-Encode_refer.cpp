#include<iostream>
#include<map>
#include<string>
using namespace std;

// 保存字符对应的哈夫曼编码，以键值对保存
map<char, string> map_codes;

typedef struct _node {
	int data;
    struct _node *parent;
	struct _node *lchild, *rchild;
} Node, *BTree; 

// 需要编码的字符
char chs[6] = {'a', 'b', 'c', 'd', 'e', 'f'};
// 字符对应的权重，这里11就是6*2-1，11为最后生成11个结点的权重
int data[11] = {10, 7, 3, 9, 8, 1};
BTree T;
BTree *forests;

void initNode(Node*, int, Node* lchild = NULL, Node* rchild = NULL);
BTree createHFTree(int*, int);
void select2Min(int*, int len, int&, int&, bool*);
void traverse(BTree);
void Encode(int len);
void EncodeHandler(Node*, Node*, char);
string Decode(BTree, string, int pos = 0);
char mapStr2Ch(string);

int main () {
	T = createHFTree(data, 6);
	Encode(6);
//	traverse(T);
	// cout<<map_codes['f'];
	string codes;
	cin>>codes;
	cout<<Decode(T, codes);
	return 0;
}

char mapStr2Ch(string str) {
	char ret = ' ';
	map<char, string>::iterator it;
	it = map_codes.begin();

	while(it != map_codes.end()){
		if (it->second == str) {
			ret = it->first;
			break;
		}
		it++;
	}
	return ret;
}

string Decode(BTree BT, string codes, int pos) {
	static int start = 0;
	if (pos > codes.length()) return "";
	string str = "";
	if (!BT->lchild && !BT->rchild) {
		string sub_str = codes.substr(start, pos - start);
		str += string(1, mapStr2Ch(sub_str));
		start = pos;
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

void EncodeHandler(Node* node, Node* parent, char c) {
    if (parent) {
        if (parent->lchild == node) {
            map_codes[c] = "1" + map_codes[c];
        }
        if (parent->rchild == node) {
            map_codes[c] = "0" + map_codes[c];
        }
		EncodeHandler(parent, parent->parent, c);
    }
}

void Encode(int len) {
	for (int i = 0; i < len; i++) {
		// 初始化每个字符对应的哈夫曼编码为空字符串
		map_codes.insert(pair<char, string>(chs[i], ""));
        EncodeHandler(forests[i], forests[i]->parent, chs[i]);
	} 
}

// 先序遍历
void traverse(BTree T) {
	if (T) {
		cout<<T->parent<<" "<<endl;
		traverse(T->lchild);
		traverse(T->rchild);
	}
}

/**
 * @brief 找到最小权重的两个结点在forests的位置
 * 
 * @param data 传入的权重数组
 * @param len 传入的权重数组
 * @param loca1 引用 第一个最小权重所在位置
 * @param loca2 引用 第二个最小权重所在位置
 * @param visited 结点的访问情况，防止有些很小的权重结点重复访问
 */
void select2Min(int *data, int len, int& loca1, int& loca2, bool *visited) {
	// ~(1<<31)有符号数（第一位为符号位）十六进制为10000000H，取反为最大的值
	int min1 = ~(1<<31), min2 = ~(1<<31);
	for(int i = 0; i < len; i++) {
		// 如果该结点有被使用过，那么就跳过
		if (visited[i]) continue;
		// 如果找到更小的权重值，则把之前最小的权重值及位置赋给loca2，min2
		if (data[i] < min1) {
			min2 = min1;
			loca2 = loca1;
			min1 = data[i];
			loca1 = i;
		// 若找到比次小的权重值还小的结点，则重新赋值
		} else if (data[i] < min2) {
			min2 = data[i];
			loca2 = i;
		}
	}
	// 把找到的两个位置标记使用过
	visited[loca1] = visited[loca2] = true;
}

BTree createHFTree(int arr[], int len) {
	// 假设刚开始所有结点各自都为一个森林，比如n个结点，最后会多生成n-1个结点，所以初始化长度为2*n-1
	forests = new Node*[2 * len - 1];
	// 保证在select2Min每次找到的两个最小权重的结点不是被用过的
	bool visited[2 * len - 1];
	for (int i = 0; i < 2 * len - 1; i++) {
		visited[i] = false;// 默认该结点没被使用
		forests[i] = new Node;
		initNode(forests[i], arr[i]);
	}
	// 因为要多生成n-1个结点，所以循环n-1次
	for (int i = 0; i < len - 1; i++) {
		// 最小的两个权重所在结点在forests的位置
		int loca1 = 0, loca2 = 0;
		// len+i因为每次循环会多生成一个结点
		select2Min(arr, len + i, loca1, loca2, visited);
		arr[len + i] = arr[loca1] + arr[loca2];
		forests[len + i]->data = arr[len + i];
        forests[loca1]->parent = forests[loca2]->parent = forests[len + i];
		forests[len + i]->lchild = forests[loca1];
		forests[len + i]->rchild = forests[loca2];
	}
	return forests[2 * len - 2];
}

void initNode(Node* node, int data, Node* lchild, Node* rchild) {
	node->data = data;
	node->lchild = lchild;
	node->rchild = rchild;
	node->parent = NULL;
}

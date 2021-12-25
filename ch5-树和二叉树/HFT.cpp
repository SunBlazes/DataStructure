#include<iostream>
using namespace std; 

typedef struct _node {
	int weight; //权重 
	struct _node *lchild, *rchild;
} HFTNode, *HFTree;

HFTree createHFTree(int[], int);
void traverseByPreOrder(HFTree);
void select(HFTree[], int&, int&, int);
// 带权路径长度之和 
void getWPL(HFTree, int&, int);

int main () {
//	int weight[] = {5, 2, 6, 3, 4, 7, 8, 9, 1};
	int weight[] = {5, 7, 2, 3, 6, 8, 9};
	int len = sizeof(weight) / sizeof(weight[0]);
	HFTree T = createHFTree(weight, len);
	traverseByPreOrder(T);
	int WPL = 0;
	getWPL(T, WPL, 0);
	cout<<"WPL: "<<WPL<<endl;
	return 0;
}

/*
	HFTree T: 哈夫曼树
	int &WPL: 引用，得到最终的带权路径长度之和
	int len: 累加最终后得到到叶节点的路径长度 
*/
void getWPL(HFTree T, int &WPL, int len) {
	if (T) {
		getWPL(T->lchild, WPL, len + 1);
		getWPL(T->rchild, WPL, len + 1);
		if (!T->lchild && !T->rchild) {
			WPL += T->weight * len;
		}
	}
}

/*
	HT[]: 森林
	int &s1: 引用s1，这里s1代表没有使用过的树里权重最小的索引 
	int &s2: 引用s2，这里s2代表没有使用过的树里权重次小的索引
			 这里s2还有个作用：保证不会使用到之前已经被使用过的树
	int n: 当前森林含有的棵数 
*/
void select(HFTree HT[], int &s1, int &s2, int n) {
	// _s2保存s2的值，因为后面的操作会修改s2的值
	// min1：最小的值，min2：次小的值 
	int min1 = -1, min2 = -1, i, _s2 = s2;
	for (i = 0; i < n; i++) {
		if (min1 > HT[i]->weight || min1 == -1) {
			if (_s2 == -1 || HT[i]->weight > HT[_s2]->weight) {
				// 如果找到更小的值，那么就把先前最小值的索引和值赋给 s1、min2 
				s2 = s1;
				min2 = min1;
				
				s1 = i;
				min1 = HT[i]->weight;
			}
		} else {
			// 这里的作用防止刚开始就找到最小值，而导致找不到次小 
			if (min2 > HT[i]->weight || min2 == -1) {
				s2 = i;
				min2 = HT[i]->weight;
			}
		}
 	}
}

/*
	int weight[]: 权重值
	int len: 初始森林的树的棵数 
	return HFTree: 返回生成的哈夫曼树 
*/
HFTree createHFTree(int weight[], int len) {
	// 2*len - 1: 由于森林有len棵节点树为1的树，两两结合又会生成len - 1棵树 
	HFTree *HT = new HFTNode*[2 * len - 1];
	int i;
	// 初始化森林 
	for (i = 0; i < len; i++) {
		HT[i] = new (HFTNode);
		HT[i]->lchild = HT[i]->rchild = NULL;
	}
	int s1, s2 = -1;
	while (i < 2 * len - 1) {
		select(HT, s1, s2, i);
		HT[i] = new(HFTNode);
		HT[i]->lchild = HT[s1];
		HT[i]->rchild = HT[s2];
		HT[i]->weight = HT[s1]->weight + HT[s2]->weight;
		i++;
	}
	// HT最后会含有 2*len - 1棵树，
	// 而每次添加新树都是放到当前森林最后一颗树的后面 
	// 所以最后一颗树自然就是所求的哈夫曼树 
	return HT[2 * len - 2];
}

void traverseByPreOrder(HFTree B) {
	if (B != NULL) {
		cout<<(B->weight)<<" ";
		traverseByPreOrder(B->lchild);
		traverseByPreOrder(B->rchild);
	}
}

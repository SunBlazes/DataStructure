#include<iostream>
using namespace std; 

typedef struct _node {
	int weight; //Ȩ�� 
	struct _node *lchild, *rchild;
} HFTNode, *HFTree;

HFTree createHFTree(int[], int);
void traverseByPreOrder(HFTree);
void select(HFTree[], int&, int&, int);
// ��Ȩ·������֮�� 
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
	HFTree T: ��������
	int &WPL: ���ã��õ����յĴ�Ȩ·������֮��
	int len: �ۼ����պ�õ���Ҷ�ڵ��·������ 
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
	HT[]: ɭ��
	int &s1: ����s1������s1����û��ʹ�ù�������Ȩ����С������ 
	int &s2: ����s2������s2����û��ʹ�ù�������Ȩ�ش�С������
			 ����s2���и����ã���֤����ʹ�õ�֮ǰ�Ѿ���ʹ�ù�����
	int n: ��ǰɭ�ֺ��еĿ��� 
*/
void select(HFTree HT[], int &s1, int &s2, int n) {
	// _s2����s2��ֵ����Ϊ����Ĳ������޸�s2��ֵ
	// min1����С��ֵ��min2����С��ֵ 
	int min1 = -1, min2 = -1, i, _s2 = s2;
	for (i = 0; i < n; i++) {
		if (min1 > HT[i]->weight || min1 == -1) {
			if (_s2 == -1 || HT[i]->weight > HT[_s2]->weight) {
				// ����ҵ���С��ֵ����ô�Ͱ���ǰ��Сֵ��������ֵ���� s1��min2 
				s2 = s1;
				min2 = min1;
				
				s1 = i;
				min1 = HT[i]->weight;
			}
		} else {
			// ��������÷�ֹ�տ�ʼ���ҵ���Сֵ���������Ҳ�����С 
			if (min2 > HT[i]->weight || min2 == -1) {
				s2 = i;
				min2 = HT[i]->weight;
			}
		}
 	}
}

/*
	int weight[]: Ȩ��ֵ
	int len: ��ʼɭ�ֵ����Ŀ��� 
	return HFTree: �������ɵĹ������� 
*/
HFTree createHFTree(int weight[], int len) {
	// 2*len - 1: ����ɭ����len�ýڵ���Ϊ1��������������ֻ�����len - 1���� 
	HFTree *HT = new HFTNode*[2 * len - 1];
	int i;
	// ��ʼ��ɭ�� 
	for (i = 0; i < len; i++) {
		HT[i] = new (HFTNode);
		HT[i]->lchild = HT[i]->rchild = NULL;
		HT[i]->weight = weight[i];
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
	// HT���Ậ�� 2*len - 1������
	// ��ÿ������������Ƿŵ���ǰɭ�����һ�����ĺ��� 
	// �������һ������Ȼ��������Ĺ������� 
	return HT[2 * len - 2];
}

void traverseByPreOrder(HFTree B) {
	if (B != NULL) {
		cout<<(B->weight)<<" ";
		traverseByPreOrder(B->lchild);
		traverseByPreOrder(B->rchild);
	}
}

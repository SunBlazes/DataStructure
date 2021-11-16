#include<iostream>
#include<queue>
#define MaxVertexNum 100
using namespace std;

typedef int Vertex;
typedef int WeightType;

typedef struct _ArcNode {
	Vertex TailVex; // ��β��ͼ�е�λ�� 
	Vertex HeadVex; // ��ͷ��ͼ�е�λ�� 
	struct _ArcNode* HLink; // ָ��ͷ��ͬ����һ���� 
	struct _ArcNode* TLink; // ָ��β��ͬ����һ���� 
	WeightType Weight;
} ANode, *ArcNode;

typedef struct {
	Vertex Vex;
	ArcNode FirstIn; // �Ըö���Ϊ��ͷ�ĵ�һ������� 
	ArcNode FirstOut; // �Ըö���Ϊ��β�ĵ�һ�������
} VNode, *VertexNode;

typedef struct {
	VNode G[MaxVertexNum];
	int Nv;
	int Ne;
} GNode, *CLGraph;

typedef struct ENode *PtrToENode;
struct ENode {
	Vertex V, W;
	WeightType Weight;
};
typedef PtrToENode Edge;

CLGraph CreateGraph(int);
void InsertEdge(CLGraph, Edge); 
CLGraph BuildGraph();
// ���ؽ�������� 
int GetVerInDge(CLGraph, Vertex);
// ���ؽ��ĳ����� 
int GetVerOutDge(CLGraph, Vertex);
// �жϸ�����ͼ�Ƿ��л� 
bool Exist_Loop(CLGraph);

main () {
	CLGraph Graph = BuildGraph();
//	GetVerInDge(Graph, 3);
//	GetVerOutDge(Graph, 3);
	cout<<Exist_Loop(Graph);
	return 0;
}

bool Exist_Loop(CLGraph Graph) {
	// ����˼·: ������������ÿ������Ķ������Ϊ0�Ľ��
	// ������ Indgree���鱣��ÿ��������ȣ��ö���q��������Ѿ�Ϊ0�Ľ�� 
	// ����BFS��ÿ���һ�����Ϊ0�Ľ�㣬�Ͱ�����ָ��Ľ�����ȼ�һ��ͬʱ
	// ������ǵ������û�б�Ϊ0������о���� 
	Vertex V;
	queue<Vertex> q;
	Vertex Indgree[Graph->Nv];
	int cnt = 0;
	for (V = 0; V < Graph->Nv; V++) {
		Indgree[V] = GetVerInDge(Graph, V);
		if (!Indgree[V]) {
			q.push(V);
		}
	}
	while (!q.empty()) {
		V = q.front();
		q.pop();
		cnt++;
		ArcNode Node = Graph->G[V].FirstOut->TLink;
		for (; Node; Node = Node->TLink) {
			if (--Indgree[Node->HeadVex] == 0) {
				q.push(Node->HeadVex);
			}
		}
	}
	return cnt != Graph->Nv;
}

int GetVerInDge(CLGraph Graph, Vertex V) {
	int num = 0;
	ArcNode Node = Graph->G[V].FirstIn->HLink;
	for (; Node; Node = Node->HLink, num++);
	return num;
}

int GetVerOutDge(CLGraph Graph, Vertex V) {
	int num = 0;
	ArcNode Node = Graph->G[V].FirstOut->TLink;
	for (; Node; Node = Node->TLink, num++);
	return num;
}

CLGraph BuildGraph() {
	int VertexNum;
	cin>>VertexNum;
	CLGraph Graph = CreateGraph(VertexNum);
	cin>>Graph->Ne;
	Vertex V;
	for (V = 0; V < Graph->Ne; V++) {
		Edge E = new (ENode);
		cin>>E->V>>E->W>>E->Weight;
		InsertEdge(Graph, E);
	}
	return Graph;
}

void InsertEdge(CLGraph Graph, Edge E) {
	// <V, W> ͷ�巨 
	// ÿ�μ���һ���ߣ���Ҫ����������
	// 1.����Graph->G[V]��FirstOut��ָ������� 
	// 2.����Graph->G[W]��FirstIn��ָ������� 
	ArcNode Node = new (ANode);
	Node->TailVex = E->V;
	Node->HeadVex = E->W;
	Node->Weight = E->Weight;
	Node->TLink = Graph->G[E->V].FirstOut->TLink;
	Graph->G[E->V].FirstOut->TLink = Node;
	Node->HLink = Graph->G[E->W].FirstIn->HLink;
	Graph->G[E->W].FirstIn->HLink = Node;
}

CLGraph CreateGraph(int VertexNum) {
	CLGraph Graph = new (GNode);
	Graph->Ne = 0;
	Graph->Nv = VertexNum;
	Vertex V;
	for (V = 0; V < Graph->Nv; V++) {
		Graph->G[V].Vex = V;
		// ��FirstIn �� FirstOut����һ���յ�ͷ��� 
		Graph->G[V].FirstIn = new (ANode);
		Graph->G[V].FirstIn->HeadVex = V;
		Graph->G[V].FirstIn->TailVex = -1;
		Graph->G[V].FirstIn->HLink = NULL;
		Graph->G[V].FirstIn->TLink = NULL;
		Graph->G[V].FirstIn->Weight = -1;
		
		Graph->G[V].FirstOut = new (ANode);
		Graph->G[V].FirstOut->HeadVex = -1;
		Graph->G[V].FirstOut->TailVex = V;
		Graph->G[V].FirstOut->HLink = NULL;
		Graph->G[V].FirstOut->TLink = NULL;
		Graph->G[V].FirstOut->Weight = -1;
	}
	return Graph;
}

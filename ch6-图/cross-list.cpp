#include<iostream>
#include<queue>
#define MaxVertexNum 100
using namespace std;

typedef int Vertex;
typedef int WeightType;

typedef struct _ArcNode {
	Vertex TailVex; // 弧尾在图中的位置 
	Vertex HeadVex; // 弧头在图中的位置 
	struct _ArcNode* HLink; // 指向弧头相同的下一条弧 
	struct _ArcNode* TLink; // 指向弧尾相同的下一条弧 
	WeightType Weight;
} ANode, *ArcNode;

typedef struct {
	Vertex Vex;
	ArcNode FirstIn; // 以该顶点为弧头的第一个弧结点 
	ArcNode FirstOut; // 以该顶点为弧尾的第一个弧结点
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
// 返回结点的入度数 
int GetVerInDge(CLGraph, Vertex);
// 返回结点的出度数 
int GetVerOutDge(CLGraph, Vertex);
// 判断该有向图是否有环 
bool Exist_Loop(CLGraph);

main () {
	CLGraph Graph = BuildGraph();
//	GetVerInDge(Graph, 3);
//	GetVerOutDge(Graph, 3);
	cout<<Exist_Loop(Graph);
	return 0;
}

bool Exist_Loop(CLGraph Graph) {
	// 总体思路: 由于拓扑排序每次输出的都是入度为0的结点
	// 可以用 Indgree数组保存每个结点的入度，用队列q保存入度已经为0的结点 
	// 利用BFS，每输出一个入度为0的结点，就把它所指向的结点的入度减一，同时
	// 检查它们的入度有没有变为0，如果有就入队 
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
	// <V, W> 头插法 
	// 每次加入一条边，需要做以下事情
	// 1.更新Graph->G[V]的FirstOut所指向的链表 
	// 2.更新Graph->G[W]的FirstIn所指向的链表 
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
		// 给FirstIn 和 FirstOut增加一个空的头结点 
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

#include<iostream>
#include<queue>
#include<stack>
#define MaxVertexNum 100
using namespace std;

typedef int WeightType; 
typedef int Vertex;

typedef Vertex SetType[MaxVertexNum];

typedef struct AdjVNode *PtrToAdjVNode;
struct AdjVNode {
	Vertex AdjV; // �ڽӵ��±� 
	WeightType Weight;
	PtrToAdjVNode Next;
};
typedef struct VNode {
	PtrToAdjVNode FirstEdge;
} AdjList[MaxVertexNum];

typedef struct GNode *PtrToGNode;
struct GNode {
	int Nv;
	int Ne;
	AdjList G;
};
typedef PtrToGNode LGraph;

typedef struct ENode *PtrToENode;
struct ENode {
	Vertex V, W;
	WeightType Weight;
};
typedef PtrToENode Edge;

LGraph CreateGraph(int);
void InsertEdge(LGraph, Edge);
LGraph BuildGraph();
Vertex FirstNeighbor(LGraph, Vertex);
Vertex NextNeighbor(LGraph, Vertex, Vertex);
void BFS(LGraph);
void BFS_Handler(LGraph, Vertex, bool*);
void DFS(LGraph);
// �ǵݹ�������ȱ��� 
void DFS1(LGraph, Vertex V = 0);
void DFS_Handler(LGraph, Vertex, bool*);
// ������V�����W�����м�·�� 
void OutputPath(LGraph, Vertex, Vertex);
void OutputPath_Handler(LGraph, Vertex, Vertex, Vertex*, int count = 0);
// ������ȱ����ж��Ƿ�����������·�� 
bool Is_PathExist_Deep(LGraph, Vertex, Vertex);
bool Is_PathExist_Deep_Handler(LGraph, Vertex, Vertex, bool*);
// ������ȱ����ж��Ƿ�����������·��
bool Is_PathExist_Broad(LGraph, Vertex, Vertex);
// �ж�����ͼ�Ƿ�Ϊ�� 
bool Is_Tree(LGraph); // ���鼯���鷳�ˣ� 
bool Is_Tree1(LGraph); // ���ж��������=������-1���жϱ���һ�Σ���һ���ǲ������е��Ѿ����ʹ��� 
// �ж�����ͼ�Ƿ�Ϊ��ͨͼ
bool Is_ConnGraph(LGraph);
void Is_ConnGraph_Connected(LGraph, SetType, Vertex, Vertex);
Vertex Is_ConnGraph_Find(SetType, Vertex);
// ����DFS�ж�����ͼ�Ƿ��л�
bool Exist_Loop(LGraph); 
void Exist_Loop_Handler(LGraph, Vertex, Vertex*, bool&); 
// DFS����������� 
void OutputTopoSort(LGraph); 
void OutputTopoSort_Handler(LGraph, Vertex, int&, bool*, int*);

main () {
	LGraph Graph = BuildGraph();
//	BFS(Graph);
//	DFS(Graph);
//	OutputPath(Graph, 0, 6);
//	DFS1(Graph);
//	cout<<Is_PathExist_Deep(Graph, 0, 6);
//	cout<<Is_PathExist_Broad(Graph, 0, 6);
//	OutputPath(Graph, 0, 5);
//	cout<<Is_Tree1(Graph);
//	cout<<Is_Tree(Graph);
//	cout<<Is_ConnGraph(Graph);
//	cout<<Exist_Loop(Graph);
	OutputTopoSort(Graph); 
	return 0;
}

void OutputTopoSort(LGraph Graph) {
	// ����˼·������DFS��һ�����DFS�ݹ�������ҽ�����ָ������н��DFS�ݹ����
	// ����cnt��¼ÿ�����DFS�ݹ������ʱ�䣬�����µ�����Ӧ�±��������
	// why?��Ϊ��������Ҫ��ÿ�����һ�����Ϊ0�Ľ�㣬���Ϊ0��ζ��ָ�����Ľ�����DFS�ݹ�ʱ�������
	// Ҳ����ʱ��Խ�õĽ��Խ����� 
	// ��ÿ������¼�����DFS�ݹ��ʱ�䣬���ʱ���������������Ӧ�Ľ�㣬����TopoSort 
	bool Visited[Graph->Nv] = {false};
	int Time[Graph->Nv], cnt = 0;
	Vertex V;
	for (V = 0; V < Graph->Nv; V++) {
		if (!Visited[V]) {
			OutputTopoSort_Handler(Graph, V, cnt, Visited, Time);
		}
	}
	for (V = 0; V < Graph->Nv; V++) {
		cout<<"Vertex: "<<V<<", Time: "<<Time[V]<<endl;
	}
}

void OutputTopoSort_Handler(LGraph Graph, Vertex V, int& cnt, bool* Visited, int* Time) {
	Visited[V] = true;
	Vertex Neighbor;
	for (Neighbor = FirstNeighbor(Graph, V); Neighbor >= 0; 
		Neighbor = NextNeighbor(Graph, V, Neighbor)) {
		if (!Visited[Neighbor]) {
			OutputTopoSort_Handler(Graph, Neighbor, cnt, Visited, Time);
		}
	}
	cnt++;
	Time[V] = cnt;
}

bool Exist_Loop(LGraph Graph) {
	Vertex Colors[Graph->Nv];
	Vertex V;
	bool flag = false;
	// Colors: -1:δ���� 0:�Ѿ����ʵ�û�д�������������ڵ�����·�� 1:������� 
	for (V = 0; V < Graph->Nv; V++) Colors[V] = -1;
	for (V = 0; V < Graph->Nv; V++) {
		if (Colors[V] == -1) {
			Exist_Loop_Handler(Graph, V, Colors, flag);
			if (flag) return flag;
		}
	}
	return flag;
}

void Exist_Loop_Handler(LGraph Graph, Vertex V, Vertex* Colors, bool& flag) {
	if (flag) return;
	Vertex Neighbor;
	Colors[V] = 0;
	for (Neighbor = FirstNeighbor(Graph, V); 
		Neighbor != -1; Neighbor = NextNeighbor(Graph, V, Neighbor)) {
		// ÿ�η���δ�ڴ�����ھ� 
		if (Colors[Neighbor] == -1) {
			Colors[Neighbor] = 0;
			Exist_Loop_Handler(Graph, Neighbor, Colors, flag);
		}
		// ���ʵ�δ������ϵĽ�㣬�϶����ڻ�·
		// �����������������������ΪW��V���ڵ�·���϶��Ѿ����ʹ�W
		// �ַ��ʴ���V���ڵ�·������һ����W��·����V->W->W
		else if (!Colors[Neighbor]) {
			flag = true;
			return;
		}
	}
	Colors[V] = 1;
}

bool Is_ConnGraph(LGraph Graph) {
	SetType Set;
	Vertex V;
	for (V = 0; V < Graph->Nv; V++) Set[V] = -1;
	// �������бߣ����Σ� 
	for (V = 0; V < Graph->Nv; V++) {
		Vertex Neighbor;
		for (Neighbor = FirstNeighbor(Graph, V); Neighbor >= 0; 
			Neighbor = NextNeighbor(Graph, V, Neighbor)) {
			Is_ConnGraph_Connected(Graph, Set, V, Neighbor);
		}
	}
	int count = 0;// -1�ĸ��� 
	for (V = 0; V < Graph->Nv; V++) {
//		cout<<Set[V]<<" ";
		if (Set[V] == -1) count++;
		if (count > 1) return false;
	}
	return true;
}

void Is_ConnGraph_Connected(LGraph Graph, SetType Set, Vertex V, Vertex W) {
	Vertex Ancestor1 = Is_ConnGraph_Find(Set, V),
		   Ancestor2 = Is_ConnGraph_Find(Set, W);
	if (Ancestor1 < Ancestor2) {
		Set[Ancestor2] = Ancestor1;
	} else {
		Set[Ancestor1] = Ancestor2;
	}
}

Vertex Is_ConnGraph_Find(SetType Set, Vertex V) {
	Vertex Ancestor = Set[V];
	if (Ancestor == -1) {
		return V;
	}
	// ·��ѹ�� 
	return Set[V] = Is_ConnGraph_Find(Set, Set[V]);
}

bool Is_Tree(LGraph Graph){
	return Graph->Nv == Graph->Ne + 1 &&
		   Is_ConnGraph(Graph);
}

bool Is_Tree1(LGraph Graph) {
	// ��ͼ(ֻ���Ǽ�ͼ��Ĭ�ϳ���)+��ͨͼ+(������=����+1)=>��ͼΪ�� 
	if (!(Graph->Nv == Graph->Ne + 1)) return false;
	bool Visited[Graph->Nv] = {false};
	Vertex V;
	DFS_Handler(Graph, 0, Visited);
	for (V = 0; V < Graph->Nv && Visited[V] == true; V++);
	return V == Graph->Nv;
}

bool Is_PathExist_Broad(LGraph Graph, Vertex V, Vertex W) {
	Vertex Neighbor;
	bool Visited[Graph->Nv] = {false};
	queue<Vertex> q;
	Visited[V] = true;
	q.push(V);
	while (!q.empty()) {
		Vertex R = q.front();
		q.pop();
		for (Neighbor = FirstNeighbor(Graph, R); 
			Neighbor >= 0; Neighbor = NextNeighbor(Graph, R, Neighbor)) {
			if (Neighbor == W) return true;
			if (!Visited[Neighbor]) {
				q.push(Neighbor);
				Visited[Neighbor] = true;
			}
		}
	}
	return false;
}

bool Is_PathExist_Deep(LGraph Graph, Vertex V, Vertex W) {
	bool Visited[Graph->Nv] = {false};
	return Is_PathExist_Deep_Handler(Graph, V, W, Visited);
}

bool Is_PathExist_Deep_Handler(LGraph Graph, Vertex V, Vertex W, bool* Visited) {
	Vertex Neighbor;
	Visited[V] = true;
	if (V == W) return true;
	bool flag = false;
	for (Neighbor = FirstNeighbor(Graph, V); 
		Neighbor >= 0; Neighbor = NextNeighbor(Graph, V, Neighbor)) {
		if (flag) break;
		if (!Visited[Neighbor]) {
			flag = flag || Is_PathExist_Deep_Handler(Graph, Neighbor, W, Visited);
		}
	}
	return flag;
}

void DFS1(LGraph Graph, Vertex V) {
	// ����˼·������ջʵ�ַǵݹ��DFS��ÿ�η���һ����㣬�ͰѸý�������Ľ������ջ
	// ��ô�´η��ʵľ��������������Ľ�� 
	stack<Vertex> s;
	bool Visited[Graph->Nv] = {false};
	Visited[V] = true;
	s.push(V);
	while (!s.empty()) {
		Vertex W = s.top(), Neighbor;
		cout<<W<<" ";
		s.pop();
		for (Neighbor = FirstNeighbor(Graph, W); 
			Neighbor >= 0; Neighbor = NextNeighbor(Graph, W, Neighbor)) {
			if (!Visited[Neighbor]) {
				s.push(Neighbor);
				Visited[Neighbor] = true;
			}
		}
	}
}

void OutputPath(LGraph Graph, Vertex V, Vertex W) {
	Vertex Path[Graph->Nv];
	OutputPath_Handler(Graph, V, W, Path);
}

// count����V��W�Ѿ���count������ˣ������·������һ����㰴˳����õ����ʵ�λ�� 
void OutputPath_Handler(LGraph Graph, Vertex V, Vertex W, Vertex* Path, int count) {
	Vertex Neighbor;
	Path[count++] = V;
	if (V == W) { 
		int i;
		for (i = 0; i < count; i++) {
			cout<<Path[i]<<" ";
		}
		cout<<endl;
	}
	for (Neighbor = FirstNeighbor(Graph, V); 
		Neighbor >= 0; Neighbor = NextNeighbor(Graph, V, Neighbor)) {
		int i;
		for (i = 0; i < count && Path[i] != Neighbor; i++);//��֤��û�л�· 
		if (i == count) {
			OutputPath_Handler(Graph, Neighbor, W, Path, count);
		}
	}
}

LGraph CreateGraph(int VertexNum) {
	LGraph Graph = new (GNode);
	Graph->Nv = VertexNum;
	Graph->Ne = 0;
	Vertex V;
	for (V = 0; V < Graph->Nv; V++) {
		Graph->G[V].FirstEdge = NULL;
	}
	return Graph;
}
void InsertEdge(LGraph Graph, Edge E) {
	/* <V,W> */
	PtrToAdjVNode Node = new (struct AdjVNode);
	Node->AdjV = E->W;
	Node->Weight = E->Weight;
	Node->Next = Graph->G[E->V].FirstEdge;
	Graph->G[E->V].FirstEdge = Node;
	
	/* ����ͼ�Ĳ��� */
//	Node = new (struct AdjVNode);
//	Node->AdjV = E->V;
//	Node->Weight = E->Weight;
//	Node->Next = Graph->G[E->W].FirstEdge;
//	Graph->G[E->W].FirstEdge = Node;
}

LGraph BuildGraph() {
	int VertexNum;
	cin>>VertexNum;
	LGraph Graph = CreateGraph(VertexNum);
	cin>>Graph->Ne;
	int i;
	for (i = 0; i < Graph->Ne; i++) {
		Edge E = new (ENode);
		cin>>E->V>>E->W>>E->Weight;
		InsertEdge(Graph, E);
	}
	return Graph;
}

Vertex FirstNeighbor(LGraph Graph, Vertex V) {
	return Graph->G[V].FirstEdge ? 
		Graph->G[V].FirstEdge->AdjV : -1;
}

Vertex NextNeighbor(LGraph Graph, Vertex V, Vertex W) {
	PtrToAdjVNode VW = Graph->G[V].FirstEdge;
	for (; VW && VW->AdjV != W; VW = VW->Next);
	if (VW->Next) return VW->Next->AdjV;
	return -1;
}

void BFS(LGraph Graph) {
	bool Visited[Graph->Nv] = {false};
	Vertex V;
	for (V = 0; V < Graph->Nv; V++) {
		if (!Visited[V]) BFS_Handler(Graph, V, Visited);
	}
}

void BFS_Handler(LGraph Graph, Vertex V, bool* Visited) {
	queue<Vertex> q;
	q.push(V);
	Visited[V] = true;
	while (!q.empty()) {
		Vertex W = q.front(), Neighbor;
		cout<<W<<" ";
		q.pop();
		Neighbor = FirstNeighbor(Graph, W);
		for (; Neighbor != -1; 
			Neighbor = NextNeighbor(Graph, W, Neighbor)) {
			if (!Visited[Neighbor]) {
				q.push(Neighbor);
				Visited[Neighbor] = true;
			}
		}
	}
}

void DFS(LGraph Graph) {
	bool Visited[Graph->Nv] = {false};
	Vertex V;
	for (V = 0; V < Graph->Nv; V++) {
		if (!Visited[V]) DFS_Handler(Graph, V, Visited);
	}
}

void DFS_Handler(LGraph Graph, Vertex V, bool* Visited) {
	Visited[V] = true;
	cout<<V<<" ";
	Vertex Neighbor = FirstNeighbor(Graph, V);
	for (; Neighbor != -1; 
		Neighbor = NextNeighbor(Graph, V, Neighbor)) {
		if (!Visited[Neighbor]) {
			DFS_Handler(Graph, Neighbor, Visited);
		}
	}
}

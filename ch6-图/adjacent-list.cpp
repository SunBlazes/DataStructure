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
	Vertex AdjV; // 邻接点下标 
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
// 非递归深度优先遍历 
void DFS1(LGraph, Vertex V = 0);
void DFS_Handler(LGraph, Vertex, bool*);
// 输出结点V到结点W的所有简单路径 
void OutputPath(LGraph, Vertex, Vertex);
void OutputPath_Handler(LGraph, Vertex, Vertex, Vertex*, int count = 0);
// 深度优先遍历判断是否两个结点存在路径 
bool Is_PathExist_Deep(LGraph, Vertex, Vertex);
bool Is_PathExist_Deep_Handler(LGraph, Vertex, Vertex, bool*);
// 广度优先遍历判断是否两个结点存在路径
bool Is_PathExist_Broad(LGraph, Vertex, Vertex);
// 判断无向图是否为树 
bool Is_Tree(LGraph); // 并查集（麻烦了） 
bool Is_Tree1(LGraph); // 先判断满足边数=顶点数-1再判断遍历一次，看一下是不是所有点已经访问过了 
// 判断无向图是否为连通图
bool Is_ConnGraph(LGraph);
void Is_ConnGraph_Connected(LGraph, SetType, Vertex, Vertex);
Vertex Is_ConnGraph_Find(SetType, Vertex);
// 利用DFS判断有向图是否有环
bool Exist_Loop(LGraph); 
void Exist_Loop_Handler(LGraph, Vertex, Vertex*, bool&); 
// DFS输出拓扑排序 
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
	// 总体思路：利用DFS，一个结点DFS递归结束当且仅当它指向的所有结点DFS递归结束
	// 利用cnt记录每个结点DFS递归结束的时间，最后更新到结点对应下标的数组里
	// why?因为拓扑排序要求每次输出一个入度为0的结点，入度为0意味着指向它的结点完成DFS递归时间比它久
	// 也就是时间越久的结点越早输出 
	// 当每个结点纪录了完成DFS递归的时间，最后按时间从晚到早进行输出对应的结点，就是TopoSort 
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
	// Colors: -1:未访问 0:已经访问但没有处理完包含它在内的所有路径 1:处理完毕 
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
		// 每次访问未在处理的邻居 
		if (Colors[Neighbor] == -1) {
			Colors[Neighbor] = 0;
			Exist_Loop_Handler(Graph, Neighbor, Colors, flag);
		}
		// 访问到未处理完毕的结点，肯定存在回路
		// 如果这个情况发生，设这个结点为W，V所在的路径肯定已经访问过W
		// 又访问代表V所在的路径又有一条到W的路径，V->W->W
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
	// 遍历所有边（两次） 
	for (V = 0; V < Graph->Nv; V++) {
		Vertex Neighbor;
		for (Neighbor = FirstNeighbor(Graph, V); Neighbor >= 0; 
			Neighbor = NextNeighbor(Graph, V, Neighbor)) {
			Is_ConnGraph_Connected(Graph, Set, V, Neighbor);
		}
	}
	int count = 0;// -1的个数 
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
	// 路径压缩 
	return Set[V] = Is_ConnGraph_Find(Set, Set[V]);
}

bool Is_Tree(LGraph Graph){
	return Graph->Nv == Graph->Ne + 1 &&
		   Is_ConnGraph(Graph);
}

bool Is_Tree1(LGraph Graph) {
	// 简单图(只考虑简单图，默认成立)+连通图+(顶点数=边数+1)=>此图为树 
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
	// 总体思路：利用栈实现非递归的DFS，每次访问一个结点，就把该结点相连的结点推入栈
	// 那么下次访问的就是这个结点相连的结点 
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

// count代表V到W已经有count个结点了，方便把路径中下一个结点按顺序放置到合适的位置 
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
		for (i = 0; i < count && Path[i] != Neighbor; i++);//保证了没有回路 
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
	
	/* 无向图的插入 */
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

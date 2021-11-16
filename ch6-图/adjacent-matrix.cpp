#include<iostream>
#include<queue>
#include<stack>
#define MaxVertexNum 100
#define Infinity ~(1<<31)
using namespace std;

typedef int WeightType;

typedef struct GNode *PtrToGNode;
struct GNode {
	int Nv; // 顶点数
	int Ne; // 边数
	WeightType G[MaxVertexNum][MaxVertexNum];
};
typedef PtrToGNode MGraph;

typedef int Vertex;

typedef struct ENode *PtrToENode;
struct ENode {
	Vertex V, W;
	WeightType Weight;
};
typedef PtrToENode Edge;

typedef struct {
	Edge *elements;
	int size;
} *MinHeap, HeapStruct;

typedef Vertex SetType[MaxVertexNum];

MGraph CreateGraph(int);
void InsertEdge(MGraph, Edge);
void DeleteEdge(MGraph, Vertex, Vertex);
MGraph BuildGraph(MinHeap&);
void BFSTraverse(MGraph);
void BFS(MGraph, Vertex, bool*);
void DFSTraverse(MGraph);
void DFS(MGraph, Vertex, bool*);
// 判断图是否存在边 
bool Adjacent(MGraph, Vertex, Vertex);
// 列出给定结点的邻接的边 
void Neighbors(MGraph, Vertex);
Vertex FirstNeighbor(MGraph, Vertex);
Vertex NextNeighbor(MGraph, Vertex, Vertex); 
// 单源无权最短路径 
void ShortestPath(MGraph);
void ShortestPath_Handler(MGraph, Vertex*, int*);
// 单源有权最短路径 
void Dijkstra(MGraph);
void Dijkstra_Handler(MGraph, Vertex*, int*);
// 多源有权最短路径 
void Floyd(MGraph); 
// 最小生成树：普里姆 适用于稠密图 
void Prim(MGraph);
bool Prim_Handler(MGraph, Vertex*, int*);
// 生成最小堆 
MinHeap CreateMinHeap(int);
void MinHeap_Insert(MinHeap, Edge);
Edge MinHeap_Delete(MinHeap);
// 建立并查集 
void Set_Init(SetType, MGraph);
void Set_Connect(SetType, Edge);
Vertex Set_Find(SetType, Vertex);
// Kruskal
void Kruskal(MGraph, MinHeap, SetType);

main() {
	MinHeap H;
	SetType Set;
	MGraph Graph = BuildGraph(H);
	Set_Init(Set, Graph);
	Kruskal(Graph, H, Set);
//	BFSTraverse(Graph);
//	DFSTraverse(Graph);
//	ShortestPath(Graph);
//	Dijkstra(Graph); 
//	Floyd(Graph);
//	Prim(Graph);
	return 0;
} 

void Kruskal(MGraph Graph, MinHeap H, SetType Set) {
	// 思路: Kruskal思路是每次选出一条最低花销的边 
	// 还必须这条边不能和已经收纳的边产生回路
	// 这里的关键就是怎么挑出最低花销的边和怎么判断选出的边是否会产生回路
	// 1.采用最小堆，每次都弹出最低花销的边，稀疏图，时间复杂度为：O(logE) 
	// 2.采用并查集。开始时，每个结点都是一个集合，当每次选出的边的端点祖先结点不同时，
	//   我们认为添加这条边不会产生回路，则取边的两个结点的祖先结点的最小下标作为他
	//   们的共同祖先结点。比如a[0]=-1，a[1]=-1，a[2]=1，a[3]=0，边为(0, 2)，则经过这操作，
	//   a[0]=-1，a[1]=0，如果下次边为(1, 3)，通过迭代得到他们的两个祖先结点刚好都是0，
	//   则连接1和3必定会产生回路。这里可以每次查找某个结点的祖先结点的同时，把该路径上的结点的祖先结点
	//   都设置最后找到的祖先结点，这样一来，判断回路的时间复杂度就为O(1)
	// 总结来看，Kruskal算法主要受边数影响 
	int count = 0; // 记录边数 
	// 树的必要条件是顶点数=边数+1 
	while (count != Graph->Nv - 1 && H->size) {
		Edge E = MinHeap_Delete(H);
		if (Set_Find(Set, E->V) != Set_Find(Set, E->W)) {
			Set_Connect(Set, E);
			cout<<"("<<E->V<<", "<<E->W<<", "<<E->Weight<<")"<<endl;
			count++;
		}
	} 
	if (count != Graph->Nv - 1) {
		cout<<"该图为不连通图，无法产生最小生成树"<<endl; 
	}
}

Vertex Set_Find(SetType Set, Vertex V) {
	if (Set[V] == -1) return V;
	return Set[V] = Set_Find(Set, Set[V]);
}

void Set_Connect(SetType Set, Edge E) {
	Vertex Ancestor1 = Set_Find(Set, E->V),
	       Ancestor2 = Set_Find(Set, E->W);
	if (Ancestor1 < Ancestor2) {
		Set[Ancestor2] = Ancestor1;
	} else {
		Set[Ancestor1] = Ancestor2;
	}
}

void Set_Init(SetType Set, MGraph Graph) {
	Vertex V;
	for (V = 0; V < Graph->Nv; V++) {
		Set[V] = -1;
	}
}

// 最小堆的删除和重整 
Edge MinHeap_Delete(MinHeap H) {
	Edge MinE;
	if (H->elements[1]) MinE = H->elements[1];
	else return NULL;
	int Parent = 1;
	Edge El = H->elements[H->size--];
	while (Parent * 2 <= H->size) {
		int Child = Parent * 2;
		if (Child + 1 <= H->size) {
			if (H->elements[Child + 1]->Weight < H->elements[Child]->Weight) {
				Child++;
			}
		}
		if (H->elements[Child]->Weight >= El->Weight) break;
		H->elements[Parent] = H->elements[Child];
		Parent = Child;
	}
	H->elements[Parent] = El;
	return MinE;
}

void MinHeap_Insert(MinHeap H, Edge E) {
	int Child = ++H->size, Parent = Child / 2;
	for (; E->Weight < H->elements[Parent]->Weight; 
		Child = Parent, Parent /= 2) {
		H->elements[Child] = H->elements[Parent];
	}
	H->elements[Child] = E;
}

MinHeap CreateMinHeap(int Num) {
	MinHeap H = new (HeapStruct);
	H->elements = new Edge[Num + 1];
	H->elements[0] = new(ENode);
	H->elements[0]->V = H->elements[0]->W = -1;
	H->elements[0]->Weight = 1<<31; // 设置哨兵 
	H->size = 0;
	return H;
}

void Prim(MGraph Graph) {
	// 总体思路：设置一个已经形成的最小生成树集合MST，初始为空
	// 每次选出一条到这个最小生成树距离开销最小并且未收纳的边 
	int dist[Graph->Nv] = {0}, Parent[Graph->Nv] = {-1};
	Vertex Source = 0, V;
	dist[Source] = 0; // 收纳源点 
	// 更新到最小生成树的距离 
	for (V = Source + 1; V < Graph->Nv; V++) {
		if (Graph->G[Source][V] != -1) {
			Parent[V] = Source;
			dist[V] = Graph->G[Source][V];
		} else {
			dist[V] = Infinity;
			Parent[V] = -1;
		}
	}
	bool flag = Prim_Handler(Graph, Parent, dist);
	cout<<flag;
}

bool Prim_Handler(MGraph Graph, Vertex* Parent, int* dist) {
	int WPL = 0; // 最小生成树的权重之和 
	while (1) {
		Vertex V, W = -1, Neighbor;
		int min_dist = Infinity;
		// 选出到MST最小距离的结点 
		for (V = 0; V < Graph->Nv; V++) {
			if (dist[V] && dist[V] != Infinity && dist[V] < min_dist) {
				min_dist = dist[V];
				W = V;
			}
		}
		// W==-1意味着没有一条边可以到MST 
		if (W == -1) break;
		WPL += dist[W];
		dist[W] = 0; // 意味着这个结点已经收纳进MST，到MST距离自然为0 
		// 新加入的结点会引起一些结点到MST的距离的更新 
		for (Neighbor = FirstNeighbor(Graph, W); Neighbor >= 0; 
			Neighbor = NextNeighbor(Graph, W, Neighbor)) {
				// 重点在dist[Neighbor]=0意味着该结点已经在MST 
			if (Graph->G[W][Neighbor] < dist[Neighbor] && dist[Neighbor]) {
				dist[Neighbor] = Graph->G[W][Neighbor];
				Parent[Neighbor] = W;
			}
		}
	}
	cout<<WPL<<endl;
	Vertex V;
	for (V = 0; V < Graph->Nv; V++) {
		if (dist[V]) return false;
	}
	return true;
}

MGraph CreateGraph(int VertexNum) {
	MGraph M = new(struct GNode);
	M->Ne = 0;
	M->Nv = VertexNum;
	Vertex i, j;
	for (i = 0; i < VertexNum; i++) {
		for (j = 0; j < VertexNum; j++) {
			M->G[i][j] = -1;
		}
	}
	return M;
}

void InsertEdge(MGraph Graph, Edge E) {
	Vertex V = E->V, W = E->W;
	Graph->G[V][W] = E->Weight;
	Graph->G[W][V] = E->Weight; // 无向图的处理 
}

void DeleteEdge(MGraph Graph, Vertex V, Vertex W) {
	Graph->G[V][W] = -1;
	Graph->G[W][V] = -1;
}

MGraph BuildGraph(MinHeap& H) {
	MGraph Graph;
	int VertexNum;
	cin>>VertexNum;
	Graph = CreateGraph(VertexNum);
	cin>>(Graph->Ne);
	H = CreateMinHeap(Graph->Ne);
	int i = 0;
	while (i < Graph->Ne) {
		Edge E = new (struct ENode);
		cin>>(E->V)>>(E->W)>>(E->Weight);
		MinHeap_Insert(H, E);
		InsertEdge(Graph, E);
		i++;
	}
	return Graph;
}

void Neighbors(MGraph Graph, Vertex V) {
	Vertex W;
	for (W = 0; W < Graph->Nv; W++) {
		if (Adjacent(Graph, V, W)) {
			cout<<"("<<V<<", "<<W<<")\n";
		}
	}
}

Vertex NextNeighbor(MGraph Graph, Vertex V, Vertex W) {
	for(W = W + 1; W < Graph->Nv && Graph->G[V][W] == -1; W++);
	if (W == Graph->Nv) return -1;
	return W;
}

Vertex FirstNeighbor(MGraph Graph, Vertex V) {
	Vertex W;
	for (W = 0; W < Graph->Nv && Graph->G[V][W] == -1; W++);
	if (W == Graph->Nv) return -1; // 与V无邻接的点 
	return W;
}

bool Adjacent(MGraph Graph, Vertex V1, Vertex V2) {
	return Graph->G[V1][V2] >= 0; 
}

void BFSTraverse(MGraph Graph) {
	bool Visited[Graph->Nv] = {false};
	Vertex V = 0;
	for (; V < Graph->Nv; V++) {
		if (!Visited[V]) BFS(Graph, V, Visited);
	}
}

void BFS(MGraph Graph, Vertex V, bool* Visited) {
	queue<Vertex> q;
	Visited[V] = true;
	q.push(V);
	while (!q.empty()) {
		Vertex W = q.front();
		cout<<W<<" ";
		q.pop();
		Vertex Neighbor = FirstNeighbor(Graph, W);
		for (; Neighbor != -1; 
			Neighbor = NextNeighbor(Graph, W, Neighbor)) {
			if (!Visited[Neighbor]) {
				q.push(Neighbor);
				Visited[Neighbor] = true;
			}
		}
	}
}

void DFSTraverse(MGraph Graph) {
	bool Visited[Graph->Nv] = {false};
	Vertex V = 0;
	for (; V < Graph->Nv; V++) {
		if (!Visited[V]) DFS(Graph, V, Visited);
	}
}

void DFS(MGraph Graph, Vertex V, bool* Visited) {
	cout<<V<<" ";
	Visited[V] = true;
	Vertex Neighbor = FirstNeighbor(Graph, V);
	for (; Neighbor != -1; 
		Neighbor = NextNeighbor(Graph, V, Neighbor)) {
		if (!Visited[Neighbor]) {
			DFS(Graph, Neighbor, Visited);
		}
	}
}

void ShortestPath(MGraph Graph) {
	Vertex Path[Graph->Nv], V;
	int dist[Graph->Nv];// 代表源点到其他结点的距离 
	for (V = 0; V < Graph->Nv; V++) {
		Path[V] = -1;
		dist[V] = -1;
	}
	dist[0] = 0;
	ShortestPath_Handler(Graph, Path, dist);
	cout<<dist[3]<<endl;
	/*  正向找到3的路径 
		Vertex W = 3;
		stack<Vertex> s;
		s.push(W);
		while(Path[W] != -1) {
			s.push(Path[W]);
			W = Path[W];
		}
		while(!s.empty()) {
			cout<<s.top()<<endl;
			s.pop();
		}
	*/
}

void ShortestPath_Handler(MGraph Graph, Vertex* Path, int* dist) {
	// 利用BFS 
	queue<Vertex> q;
	Vertex source = 0;
	q.push(source);
	while (!q.empty()) {
		Vertex V = q.front();
		q.pop();
		Vertex Neighbor = FirstNeighbor(Graph, V);
		for (; Neighbor != -1; 
			Neighbor = NextNeighbor(Graph, V, Neighbor)) {
			if (dist[Neighbor] == -1) {
				q.push(Neighbor);
				dist[Neighbor] = dist[V] + 1;
				Path[Neighbor] = V;
			}
		}
	}
}

void Dijkstra(MGraph Graph) {
	Vertex Path[Graph->Nv], V;
	int dist[Graph->Nv];
	for (V = 0; V < Graph->Nv; V++) {
		Path[V] = -1;
		dist[V] = Infinity;
	}
	dist[0] = 0;
	Dijkstra_Handler(Graph, Path, dist);
	cout<<dist[5]<<endl;
	/*  正向找到3的路径 
		Vertex W = 3;
		stack<Vertex> s;
		s.push(W);
		while(Path[W] != -1) {
			s.push(Path[W]);
			W = Path[W];
		}
		while(!s.empty()) {
			cout<<s.top()<<endl;
			s.pop();
		}
	*/
}

void Dijkstra_Handler(MGraph Graph, Vertex* Path, int* dist) {
	queue<Vertex> q;
	Vertex source = 0;
	q.push(source);
	while (!q.empty()) {
		Vertex V = q.front();
		q.pop();
		Vertex Neighbor = FirstNeighbor(Graph, V);
		for (; Neighbor != -1; 
			Neighbor = NextNeighbor(Graph, V, Neighbor)) {
			if (dist[V] + Graph->G[V][Neighbor] < dist[Neighbor]) {
				dist[Neighbor] = dist[V] + Graph->G[V][Neighbor];
				Path[Neighbor] = V;
				q.push(Neighbor);
			}
		}
	}
}

void Floyd(MGraph Graph) {
	// 总体思路：用D^k[i][j]代表i到j的最短路径，其中k代表经过加入了下标为0->k-1的结点后i到j的最短路径 
	// D^-1[i][j]=Infinity说明i到j没有直接的边，否则有一条直连的边
	// k每次增加，代表每次加入一个结点，如果这个结点影响最短路径，则肯定有
	// D^k[i][j]=D^(k-1)[i][k]+D^(k-1)[k][j]否则D^k[i][j]=D^(k-1)[i][j]
	unsigned int D[Graph->Nv][Graph->Nv];
	Vertex Path[Graph->Nv][Graph->Nv];
	Vertex i, j;
	// D^-1
	for (i = 0; i < Graph->Nv; i++) {
		for (j = 0; j < Graph->Nv; j++) {
			D[i][j] = Graph->G[i][j] >= 0 ? Graph->G[i][j] : Infinity;
			Path[i][j] = -1;
		}
	}
	Vertex k;
	// D^0 ~ D^k-1
	for (k = 0; k < Graph->Nv; k++) {
		for (i = 0; i < Graph->Nv; i++) {
			for (j = 0; j < Graph->Nv; j++) {
				if (D[i][k] + D[k][j] < D[i][j]) {
					D[i][j] = D[i][k] + D[k][j];
					Path[i][j] = k;
				} 
			}
		}
	}
	/*  正向输出 到6的路径 
		Vertex Source = 0, W = 6;
		stack<Vertex> s;
		s.push(W);
		while (Path[Source][W] != -1) {
			W = Path[Source][W];
			s.push(W);
		} 
		s.push(Source);
		while (!s.empty()) {
			cout<<s.top()<<" ";
			s.pop();
		}
	*/
}

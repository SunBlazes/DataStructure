#include<iostream>
#include<queue>
#include<stack>
#define MaxVertexNum 100
#define Infinity ~(1<<31)
using namespace std;

typedef int WeightType;

typedef struct GNode *PtrToGNode;
struct GNode {
	int Nv; // ������
	int Ne; // ����
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
// �ж�ͼ�Ƿ���ڱ� 
bool Adjacent(MGraph, Vertex, Vertex);
// �г����������ڽӵı� 
void Neighbors(MGraph, Vertex);
Vertex FirstNeighbor(MGraph, Vertex);
Vertex NextNeighbor(MGraph, Vertex, Vertex); 
// ��Դ��Ȩ���·�� 
void ShortestPath(MGraph);
void ShortestPath_Handler(MGraph, Vertex*, int*);
// ��Դ��Ȩ���·�� 
void Dijkstra(MGraph);
void Dijkstra_Handler(MGraph, Vertex*, int*);
// ��Դ��Ȩ���·�� 
void Floyd(MGraph); 
// ��С������������ķ �����ڳ���ͼ 
void Prim(MGraph);
bool Prim_Handler(MGraph, Vertex*, int*);
// ������С�� 
MinHeap CreateMinHeap(int);
void MinHeap_Insert(MinHeap, Edge);
Edge MinHeap_Delete(MinHeap);
// �������鼯 
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
	// ˼·: Kruskal˼·��ÿ��ѡ��һ����ͻ����ı� 
	// �����������߲��ܺ��Ѿ����ɵı߲�����·
	// ����Ĺؼ�������ô������ͻ����ıߺ���ô�ж�ѡ���ı��Ƿ�������·
	// 1.������С�ѣ�ÿ�ζ�������ͻ����ıߣ�ϡ��ͼ��ʱ�临�Ӷ�Ϊ��O(logE) 
	// 2.���ò��鼯����ʼʱ��ÿ����㶼��һ�����ϣ���ÿ��ѡ���ıߵĶ˵����Ƚ�㲻ͬʱ��
	//   ������Ϊ��������߲��������·����ȡ�ߵ������������Ƚ�����С�±���Ϊ��
	//   �ǵĹ�ͬ���Ƚ�㡣����a[0]=-1��a[1]=-1��a[2]=1��a[3]=0����Ϊ(0, 2)���򾭹��������
	//   a[0]=-1��a[1]=0������´α�Ϊ(1, 3)��ͨ�������õ����ǵ��������Ƚ��պö���0��
	//   ������1��3�ض��������·���������ÿ�β���ĳ���������Ƚ���ͬʱ���Ѹ�·���ϵĽ������Ƚ��
	//   ����������ҵ������Ƚ�㣬����һ�����жϻ�·��ʱ�临�ӶȾ�ΪO(1)
	// �ܽ�������Kruskal�㷨��Ҫ�ܱ���Ӱ�� 
	int count = 0; // ��¼���� 
	// ���ı�Ҫ�����Ƕ�����=����+1 
	while (count != Graph->Nv - 1 && H->size) {
		Edge E = MinHeap_Delete(H);
		if (Set_Find(Set, E->V) != Set_Find(Set, E->W)) {
			Set_Connect(Set, E);
			cout<<"("<<E->V<<", "<<E->W<<", "<<E->Weight<<")"<<endl;
			count++;
		}
	} 
	if (count != Graph->Nv - 1) {
		cout<<"��ͼΪ����ͨͼ���޷�������С������"<<endl; 
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

// ��С�ѵ�ɾ�������� 
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
	H->elements[0]->Weight = 1<<31; // �����ڱ� 
	H->size = 0;
	return H;
}

void Prim(MGraph Graph) {
	// ����˼·������һ���Ѿ��γɵ���С����������MST����ʼΪ��
	// ÿ��ѡ��һ���������С���������뿪����С����δ���ɵı� 
	int dist[Graph->Nv] = {0}, Parent[Graph->Nv] = {-1};
	Vertex Source = 0, V;
	dist[Source] = 0; // ����Դ�� 
	// ���µ���С�������ľ��� 
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
	int WPL = 0; // ��С��������Ȩ��֮�� 
	while (1) {
		Vertex V, W = -1, Neighbor;
		int min_dist = Infinity;
		// ѡ����MST��С����Ľ�� 
		for (V = 0; V < Graph->Nv; V++) {
			if (dist[V] && dist[V] != Infinity && dist[V] < min_dist) {
				min_dist = dist[V];
				W = V;
			}
		}
		// W==-1��ζ��û��һ���߿��Ե�MST 
		if (W == -1) break;
		WPL += dist[W];
		dist[W] = 0; // ��ζ���������Ѿ����ɽ�MST����MST������ȻΪ0 
		// �¼���Ľ�������һЩ��㵽MST�ľ���ĸ��� 
		for (Neighbor = FirstNeighbor(Graph, W); Neighbor >= 0; 
			Neighbor = NextNeighbor(Graph, W, Neighbor)) {
				// �ص���dist[Neighbor]=0��ζ�Ÿý���Ѿ���MST 
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
	Graph->G[W][V] = E->Weight; // ����ͼ�Ĵ��� 
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
	if (W == Graph->Nv) return -1; // ��V���ڽӵĵ� 
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
	int dist[Graph->Nv];// ����Դ�㵽�������ľ��� 
	for (V = 0; V < Graph->Nv; V++) {
		Path[V] = -1;
		dist[V] = -1;
	}
	dist[0] = 0;
	ShortestPath_Handler(Graph, Path, dist);
	cout<<dist[3]<<endl;
	/*  �����ҵ�3��·�� 
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
	// ����BFS 
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
	/*  �����ҵ�3��·�� 
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
	// ����˼·����D^k[i][j]����i��j�����·��������k�������������±�Ϊ0->k-1�Ľ���i��j�����·�� 
	// D^-1[i][j]=Infinity˵��i��jû��ֱ�ӵıߣ�������һ��ֱ���ı�
	// kÿ�����ӣ�����ÿ�μ���һ����㣬���������Ӱ�����·������϶���
	// D^k[i][j]=D^(k-1)[i][k]+D^(k-1)[k][j]����D^k[i][j]=D^(k-1)[i][j]
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
	/*  ������� ��6��·�� 
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

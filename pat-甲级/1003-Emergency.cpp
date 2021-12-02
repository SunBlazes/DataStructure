#include<iostream>
#include<queue>
#define Infinity ~(1<<31)
#define MaxSize 501
using namespace std;

typedef struct {
	int Nv;
	int G[MaxSize][MaxSize];
} *MGraph, GNode;

class Solution {
	public:
		MGraph FormGraph(int cities_num, int roads_num) {
			MGraph Graph = new(GNode);
			Graph->Nv = cities_num;
			int i, j;
			for (i = 0; i < cities_num; i++) {
				for (j = 0; j < cities_num; j++) {
					Graph->G[i][j] = -1;
				}
			}
			for (i = 0; i < roads_num; i++) {
				int V, W, L;
				cin>>V>>W>>L;
				Graph->G[V][W] = L;
				Graph->G[W][V] = L;
			}
			return Graph;
		}
		int FirstNeighbor(MGraph Graph, int V) {
			int W;
			for (W = 0; W < Graph->Nv && Graph->G[V][W] == -1; W++);
			if (W == Graph->Nv) return -1; // 与V无邻接的点 
			return W;
		}
		int NextNeighbor(MGraph Graph, int V, int W) {
			for(W = W + 1; W < Graph->Nv && Graph->G[V][W] == -1; W++);
			if (W == Graph->Nv) return -1;
			return W;
		}
		void Handler() {
			int cities_num, roads_num, C1, C2;
			cin>>cities_num>>roads_num>>C1>>C2;
			// the distribution of rescue teams in each city 
			int rc_dis[cities_num];
			int i;
			for (i = 0; i < cities_num; i++) cin>>rc_dis[i];
			MGraph Graph = FormGraph(cities_num, roads_num);
			Shortest_Path(Graph, C1, C2, rc_dis);
		}
		int Find_Min(int dist[], bool Collected[], int L) {
			int i;
			int Min = Infinity;
			int V = -1;
			for (i = 0; i < L; i++) {
				if (!Collected[i] && dist[i] < Min) {
					Min = dist[i];
					V = i;
				}
			}
			return V;
		}
		void Shortest_Path(MGraph Graph, int C1, int C2, int rc_dis[]) {
			if (C1 == C2) {
				cout<<1<<" "<<rc_dis[C1]; 
				return;
			}
			int dist[Graph->Nv], r_teams[Graph->Nv] = {0};
			int count[Graph->Nv] = {0};
			count[C1] = 1;
			r_teams[C1] = rc_dis[C1];
			int i;
			for (i = 0; i < Graph->Nv; i++) {
				dist[i] = Infinity;
			}
			bool Collected[Graph->Nv] = {false};
			dist[C1] = 0;
			while (1) {
				int V = Find_Min(dist, Collected, Graph->Nv);
				if (V == -1) break;
				Collected[V] = true;
				int Neighbor;
				for (Neighbor = FirstNeighbor(Graph, V); Neighbor >= 0;
					Neighbor = NextNeighbor(Graph, V, Neighbor)) {
						int new_dist = dist[V] + Graph->G[V][Neighbor];
						if (new_dist < dist[Neighbor]) {
							r_teams[Neighbor] = r_teams[V] + rc_dis[Neighbor];
							dist[Neighbor] = new_dist;
							count[Neighbor] = count[V];
						} 
						else if (new_dist == dist[Neighbor]) {
							if (r_teams[V] + rc_dis[Neighbor] > r_teams[Neighbor]) {
								r_teams[Neighbor] = r_teams[V] + rc_dis[Neighbor];
							}
							count[Neighbor] += count[V];
						}
					}
			}
			cout<<count[C2]<<" "<<r_teams[C2];
		}
};

int main () {
	Solution S;
	S.Handler();
	return 0;
}

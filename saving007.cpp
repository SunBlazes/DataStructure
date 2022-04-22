#include<iostream>
#include<math.h>
using namespace std;

typedef struct {
	int radius;
	int x;
	int y;	
} Agent;

typedef struct {
	int x;
	int y;
	bool visisted;
} Point;

typedef struct {
	Point *points;
	int extent;
	int count;
} EscapeMap;

void Map_Init(EscapeMap &emap, int count, int extent = 50) {
	emap.points = new Point[count];
	emap.count = count;
	emap.extent = extent;
}

void Points_Input(EscapeMap &emap) {
	int i;
	for (i = 0; i < emap.count; i++) {
		Point p;
		cin>>p.x>>p.y;
		p.visisted = false;
		emap.points[i] = p;
	}
}

bool Judge_IsSafe(Agent agent, int extent) {
	if (abs(agent.x) + agent.radius >= extent ||
		abs(agent.y) + agent.radius >= extent) {
		return true;
	}
	return false;
}

void Jump(Agent &agent, Point &p) {
	agent.x = p.x;
	agent.y = p.y;
	p.visisted = true;
}

bool CanReach(Agent agent, Point p) {
	int dis = pow(p.x - agent.x, 2) + pow(p.y - agent.y, 2);
	return  dis <= pow(agent.radius, 2);
}

void Escape(EscapeMap &emap, Agent &agent, bool &flag) {
	if (flag) {
		return;
	}
	int i;
	Agent temp = agent;
	for (i = 0; i < emap.count; i++) {
		if (!emap.points[i].visisted) {
			agent = temp;
			if (CanReach(agent, emap.points[i])) {
				Jump(agent, emap.points[i]);
				if (Judge_IsSafe(agent, emap.extent)) {
					flag = true;
					return;
				}
				Escape(emap, agent, flag);
			}
		}
	}
}

int main() {
	Agent agent_007;
	cin>>agent_007.radius>>agent_007.x>>agent_007.y;
	int count;
	cin>>count;
	EscapeMap emap;
	Map_Init(emap, count);
	Points_Input(emap);
	bool flag = false;
	Escape(emap, agent_007, flag);
	if (flag) {
		cout<<"007 escaped successfully"<<endl;
	} else {
		cout<<"007 escaped failedly"<<endl;
	}
	return 0;
} 

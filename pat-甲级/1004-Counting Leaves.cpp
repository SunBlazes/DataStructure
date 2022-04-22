#include<iostream>
#include<map>
#include<string>
#include<vector>
using namespace std;

map< string, vector<string> >::iterator map_it;

int N, M;

class Solution {
	public:
		map< string, vector<string> > m;
		vector<int> count;
		void Handler() {
			cin>>N>>M;
			int i;
			for (i = 0; i < M; i++) {
				string ID;
				int K;
				cin>>ID>>K;
				vector<string> v;
				m.insert(make_pair(ID, v));
				int j;
				for (j = 0; j < K; j++) {
					string str;
					cin>>str;
					m[ID].push_back(str);
				}
			}
			DFS("01", 0);
			for (i = 0; i < count.size(); i++) {
				cout<<count[i];
				if (i != count.size() - 1)
					cout<<" ";
			}
		}
		void DFS(string ID, int level) {
			if (m.count(ID) == 0) {
				if (count.capacity() < level + 1) {
					count.resize(level + 1, 0);
				}
				count[level]++;
			} else {
				vector<string>::iterator vector_it;
				for (vector_it = m[ID].begin(); vector_it != m[ID].end(); vector_it++) {
					DFS(*vector_it, level + 1);
				}
			}
		} 
};

int main () {
	Solution S;
	S.Handler();
	return 0;
}

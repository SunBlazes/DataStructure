#include<iostream>
#include<map>
using namespace std;

class MyCompare {
	public:
		// �ı�mapĬ�ϵ���key��С����ʽ���� 
		bool operator()(int v1, int v2) {
			return v1 > v2;
		}
};

main () {
	map<int, int, MyCompare> m; 
	m.insert(make_pair(1, 10));
	m.insert(make_pair(2, 9));
	m.insert(make_pair(3, 8));
	
	map<int, int, MyCompare>::iterator it = m.begin();
	for (; it != m.end(); it++) {
		cout<<(*it).second<<" ";
	}
	cout<<endl; 
	return 0;
}

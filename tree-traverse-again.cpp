#include<iostream>
#include<stack>
#include<queue>
using namespace std;

void handler(int Pre[], int In[], int prel, int prer, int inl, int inr, queue<int> &q) {
	if (prel > prer) return;
	int data = Pre[prel];
	int loca;
	for (loca = inl; loca <= inr && data != In[loca]; loca++);
	if (loca > inr) return;
	handler(Pre, In, prel + 1, loca - inl + prel, inl, loca - 1, q);
	handler(Pre, In, loca - inl + prel + 1, prer, loca + 1, inr, q);
	q.push(data);
}

int main () {
	int count;
	cin>>count;
	stack<int> s;
	int Pre[count], In[count], i = 0, j = 0;
	while (j < count) {
		string str;
		cin>>str;
		if (str == "Push") {
			int data;
			cin>>data;
			s.push(data);
			Pre[i++] = data;
		} else if (str == "Pop") {
			In[j++] = s.top();
			s.pop();
		}
	}
	queue<int> q;
	handler(Pre, In, 0, count - 1, 0, count - 1, q);
	while (!q.empty()) {
		cout<<q.front()<<" ";
		q.pop();
	}
	return 0;
}

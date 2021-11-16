#include<iostream>
#define MaxSize 100
using namespace std;
typedef int ElementType;
typedef ElementType SetType[MaxSize];

ElementType find (SetType s, ElementType e) {
	ElementType Ancestor = e;
	if (s[e] < 0) {
		return e;
	}
	return s[e] = find(s, s[e]);
}

void isConnected (SetType s) {
	cout<<"请输入两个结点: \n";
	ElementType c1, c2;
	cin>>c1>>c2;
	ElementType Ancestor1 = find(s, c1), 
		Ancestor2 = find(s, c2);
	if (Ancestor1 == Ancestor2) {
		cout<<"yes\n";
	} else {
		cout<<"no\n"; 
	}
}

void connect(SetType s) {
	cout<<"请输入两个结点: \n";
	ElementType c1, c2;
	cin>>c1>>c2;
	ElementType Ancestor1 = find(s, c1), 
		Ancestor2 = find(s, c2);
	if (s[Ancestor1] > s[Ancestor2]) {
		s[Ancestor1] = Ancestor2;
		s[Ancestor2]--;
	} else {
		s[Ancestor2] = Ancestor1;
		s[Ancestor1]--;
	}
	int i;
	for (i = 0; i < 6; i++) {
		cout<<s[i]<<" ";
	} 
	cout<<endl;
}

int main () {
	SetType s;
	int count;
	cout<<"请输入结点数: \n";
	cin>>count;
	int i;
	for (i = 0; i < count; i++) {
		s[i] = -1;
	} 
	char in;
	do {
		cin>>in;
		ElementType i;
		switch(in) {
			case 'c': isConnected(s);break;
			case 'i': connect(s);break;
		}
	} while (in != 'e');
	return 0;
} 

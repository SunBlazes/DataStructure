#include<iostream>
using namespace std;

int set(int*&);

int main() {
	int a = 55, *p = &a;
	cout<<*p<<endl;
	set(p);
	cout<<*p<<endl;
}

int set(int*& a) {
	*a = 6565;
	a = NULL;
}

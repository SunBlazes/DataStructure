#include<iostream>
using namespace std;

class B;

class A {
	public:
		friend B;
		A() {
			p_number = 10;
		}
	private:
		int p_number;
};

class B {
	public:
		void OutputAP(const A &a) {
			cout<<a.p_number<<endl;
		}
};

main () {
	A a;
	B b;
	b.OutputAP(a);
	return 0;
}

#include<iostream>
using namespace std;

class Person {
	public:
		int change;
		Person(int c):change(c) {
		}
		Person operator+ (const Person &p) {
			Person temp(change + p.change);
			return temp;
		}
};

main () {
	Person p1(20), p2(30);
	Person p3 = p1 + p2; 
	cout<<p3.change;
	return 0;
}

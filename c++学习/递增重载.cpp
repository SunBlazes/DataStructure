#include<iostream>
using namespace std;

class Person {
	public:
		friend ostream& operator<<(ostream&, Person);
		Person(const Person &p) {
			change = p.change;
			cout<<"copy constructor\n";
		}
		Person(int c):change(c) {
		}
		Person& operator++() {
			change++;
			return *this;
		}
		Person operator++(int) {
			Person temp = *this;
			change++;
			return temp;
		}
	private:
		int change;
};

ostream& operator<<(ostream& cout, Person p) {
	cout<<p.change;
	return cout;
}

main () {
	Person p(30);
	cout<<++(++p)<<endl;
	cout<<p++<<endl;
	cout<<p;
	return 0;
}

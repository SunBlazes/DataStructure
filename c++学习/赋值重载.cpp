#include<iostream>
using namespace std;

class Person {
	public:
		int change;
		int *age;
		Person(int c, int _age):change(c) {
			age = new int(_age);
		}
		Person operator+ (const Person &p) {
			Person temp(change + p.change, *age + *p.age);
			return temp;
		}
		Person retThis() {
			return *this;
		}
		Person(const Person &p) {
			cout<<"copied\n";
			change = p.change;
			if (age != NULL) {
				age = new int(*p.age);
			}
		}
		~Person() {
			if (age != NULL) {
				delete age;
				age = NULL;
			}
		}
		Person& operator=(const Person &p) {
			if (age != NULL) {
				age = new int(*p.age);
			}
			change = p.change;
			return *this;
		}
		bool operator==(const Person &p) {
			return *p.age == *age && p.change == change;
		}
};

main () {
	Person p1(20, 18), p2(30, 28), p3(40, 38);
	p1 = p2 = p3;
	cout<<(p1==p2)<<endl;
	cout<<*p1.age;
	return 0;
}

#include<iostream>
using namespace std;

/*
class A {
	public:
		void OutputA() {
			
		}
};

template<class T>
class B {
	private: 
		T obj;
	public:
		void Output_A() {
			obj.OutputB();
		} 
};
*/

template<typename T>
class Person {
	private:
		int change;
	public:
		Person(int c):change(c) {
		}
		friend void seeFriendChange(const Person<T> &p) {
			cout<<p.change<<endl;
		}
		template<class V>
		friend void seeFriendChange1(const Person<V>&);
};

template<typename T>
void seeFriendChange1(const Person<T> &p) {
	cout<<p.change<<endl;
}

main () {
	Person<int> p(55);
	seeFriendChange(p);
	seeFriendChange1(p);
	return 0;
} 

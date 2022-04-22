#include<iostream>
#include<set>
using namespace std;

void print(const set<int> &st) {
	set<int>::const_iterator it = st.begin();
	for (; it != st.end(); it++) {
		cout<<*it<<" ";
	}
	cout<<endl;
}

void test01() {
	set<int> st;
	
	st.insert(5);
	st.insert(1);
	print(st);
	
	st.erase(5);// 删除值为5的元素 
}

void test02() {
	set<int> st;
	st.insert(5);
	st.insert(1);
	
	// pair.first返回元素的迭代器，pair.second是否插入成功
	pair<set<int>::iterator, bool> ret = st.insert(1);
	cout<<ret.second<<endl;
//	cout<<*(++ret.first)<<endl; 
	
	// find找到会返回对应元素的迭代器，否则返回st.end()迭代器 
	cout<<(st.find(6) != st.end())<<endl;
	
	// count返回值为6的元素个数，由于set不允许重复的值，所以个数只能为0 or 1
	cout<<st.count(6)<<endl;
} 

class MyCompare {
	public:
		bool operator()(int a, int b) {
			return a > b;
		}
};

void test03() {
	set<int, MyCompare> st;
	int i;
	for (i = 0; i < 10; i++) {
		st.insert(i);
	}
	set<int, MyCompare>::const_iterator it = st.begin();
	for (; it != st.end(); it++) {
		cout<<*it<<" ";
	}
	cout<<endl;
}

class MyCompare1;

class Person {
	private:
		string name;
		int age; 
	public:
		Person(string s, int a) {
			name = s;
			age = a;
		}
		friend MyCompare1;
};

class MyCompare1 {
	public:
		bool operator()(const Person&, const Person&);
};

bool MyCompare1::operator()(const Person &p1, const Person &p2) {
	if (p1.name == p2.name) {
		return p1.age < p2.age;
	}
	return p1.name < p2.name;
}

void test04() {
	set<Person, MyCompare1> st;
	Person p1("zsw", 18);
	Person p2("zsh", 17);
	Person p3("mao", 21);
	Person p4("mao", 16);
//	cout<<MyCompare1().operator()(p2, p1)<<endl;
	st.insert(p1);
	st.insert(p2);
	st.insert(p3);
	st.insert(p4);
	set<Person, MyCompare1>::iterator it = st.begin();
	// 暂时认为迭代器访问不了元素的私有成员 未解决
//	for (; it != st.end(); it++) {
//		cout<<(*it).name<<" "<<(*it).age<<endl;
//	}
	
}

int main () {
//	test01();
//	test02();
//	test03();
	test04();
	return 0;
}

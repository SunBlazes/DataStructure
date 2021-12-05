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
	
	st.erase(5);// ɾ��ֵΪ5��Ԫ�� 
}

void test02() {
	set<int> st;
	st.insert(5);
	st.insert(1);
	
	// pair.first����Ԫ�صĵ�������pair.second�Ƿ����ɹ� 
	pair<set<int>::iterator, bool> ret = st.insert(1);
	cout<<ret.second<<endl;
//	cout<<*(++ret.first)<<endl; 
	
	// find�ҵ��᷵�ض�ӦԪ�صĵ����������򷵻�st.end()������ 
	cout<<(st.find(6) != st.end())<<endl;
	
	// count����ֵΪ6��Ԫ�ظ���������set�������ظ���ֵ�����Ը���ֻ��Ϊ0 or 1
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
	// ��ʱ��Ϊ���������ʲ���Ԫ�ص�˽�г�Ա δ��� 
//	for (; it != st.end(); it++) {
//		cout<<(*it).name<<" "<<(*it).age<<endl;
//	}
	
}

main () {
//	test01();
//	test02();
//	test03();
	test04();
	return 0;
}

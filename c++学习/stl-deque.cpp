#include<iostream>
#include<deque>
#include<algorithm>
using namespace std;

void print(const deque<int> &d) {
	deque<int>::const_iterator it = d.begin();
	for (; it != d.end(); it++) {
		cout<<*it<<" ";
//		*it = 100; // const deque容器的元素都是只读，不允许修改
	}
	cout<<endl;
}

// 构造函数
void test01() {
	deque<int> d;
	d.push_front(10);
	print(d);
	
	deque<int> d1 = d; // equal to deque<int> d1(d)
	print(d1);
	
	deque<int> d2(d1.begin(), d1.end());
	print(d2);
	
	deque<int> d3(10, 100);
	print(d3);
}

// 赋值
void test02() {
	deque<int> d, d1;
	d.push_front(10);
	d1 = d;
	d1.assign(d.begin(), d.end());
	d1.assign(10, 100);
	print(d1);
}

// 大小操作
void test03() {
	deque<int> d;
	cout<<d.empty()<<endl;
	cout<<d.size()<<endl;
	d.resize(100, 10);
} 

// 插入与删除
void test04() {
	deque<int> d;
	d.push_back(2);
	d.push_front(1);
	print(d);
	
	d.insert(d.begin(), 0);
	print(d);
	
	deque<int> d1;
	d1.push_back(3);
	d1.push_back(4);
	d.insert(d.end(), d1.begin(), d1.end());
	d.insert(d.begin() + 1, *d.begin());
	d.insert(d.begin(), d.begin(), d.begin() + 2);
	print(d);
	
	d.erase(d.begin());
	d.erase(d.begin(), d.begin() + 3);
	print(d);
	
	d.clear();
} 

// 数据存取
void test05() {
	deque<int> d;
	int i;
	for (i = 0; i < 10; i++) {
		d.push_back(i + 1);
	}
	
	cout<<d[9]<<endl;
	cout<<d.at(9)<<endl;
	
	cout<<d.front()<<endl;//�����׸�Ԫ��
	cout<<d.back()<<endl;// ����ĩβԪ��
}

// 排序
void test06() {
	deque<int> d;
	int i;
	for (i = 0; i < 10; i++) {
		d.push_front(i + 1);
	}
	sort(d.begin(), d.end());
	
	print(d);
} 

int main () {
//	test01();
//	test02();
//	test03();
//	test04();
//	test05();
	test06();
	return 0;
} 

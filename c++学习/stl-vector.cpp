#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

// 构造函数 
void test01() {
	vector<int>::iterator it;
	vector<int> v;
	int i;
	for (i = 0; i < 10; i++) {
		v.push_back(i + 1);
	}

	vector<int> v1 = v;
	for (it = v1.begin(); it != v1.end(); it++) {
		cout<<*it<<" ";
	}
	cout<<endl;
	
	vector<int> v2(v.begin(), v.end());
	for (it = v2.begin(); it != v2.end(); it++) {
		cout<<*it<<" ";
	}
	cout<<endl;
	
	vector<int> v3(10, 100);
	for (it = v3.begin(); it != v3.end(); it++) {
		cout<<*it<<" ";
	}
	cout<<endl;
}

// 赋值
void test02() {
	vector<int> v1, v2;
	int i;
	for (i = 0; i < 10; i++) {
		v1.push_back(i + 1);
	}
	vector<int>::iterator it;
	v2.assign(v1.begin() + 2, v1.end() - 1);
	for (it = v2.begin(); it != v2.end(); it++) {
		cout<<*it<<" ";
	}
	cout<<endl;
	
	v2.assign(9, 55);
	for (it = v2.begin(); it != v2.end(); it++) {
		cout<<*it<<" ";
	}
} 

// 容量与大小
void test03() {
	vector<int> v;
	int i;
	for (i = 0; i < 10; i++) {
		v.push_back(i + 1);
	}
	
	cout<<v.capacity()<<endl;
	cout<<v.size()<<endl;
	
	// 若容器变长则用-1填充，否则删除超出长度的元素 
	v.resize(12, -1);// 注意这里capacity不改变由于调整后的size依旧小于capacity 
	cout<<v.capacity()<<endl;
	vector<int>::iterator it;
	for (it = v.begin(); it != v.end(); it++) {
		cout<<*it<<" ";
	}
	cout<<endl;
	
	v.resize(17, -1);//capacity变大由于调整后size超过了capacity 
	cout<<v.capacity()<<endl;
} 

// 插入和删除
void test04() {
	vector<int>::iterator it;
	vector<int> v;
	v.push_back(10);//尾部插入 
	v.pop_back();//删除尾部元素 不返回被删除的元素 
	int i;
	for (i = 0; i < 10; i++) {
		v.push_back(i + 1);
	}
	
	v.insert(v.begin() + 2, 5);
	v.insert(v.begin() + 2, 5, -1);//在位置为2的地方插入5个-1 
	v.erase(v.begin()); 
	v.erase(v.begin(), v.end() - 1);// 删除区间在[v.begin(), v.end() - 1)的元素; 
	v.clear();// 清空元素 
	for (it = v.begin(); it != v.end(); it++) {
		cout<<*it<<" ";
	}
	cout<<endl;
} 

// 数据存取
void test05() {
	vector<int> v;
	int i;
	for (i = 0; i < 10; i++) {
		v.push_back(i + 1);
	}
	
	cout<<v[9]<<endl;
	cout<<v.at(9)<<endl;
	
	cout<<v.front()<<endl;//返回首个元素 
	cout<<v.back()<<endl;// 返回末尾元素 
} 

// 容器交换元素
void test06() {
	vector<int> v;
	int i;
	for (i = 0; i < 10000; i++)
		v.push_back(i);
	// 此时容量肯定会大于长度很多，很浪费空间 
	cout<<v.capacity()<<endl;
	// 采用匿名容器对空间进行收缩
	// 1.先采用传入容器的形式初始化一个匿名容器，capacity和size相等，不存在多余的空间
	// 2.匿名容器和容器v进行swap，容器进行交换，那么v就指向了匿名容器，匿名对象就指向了v的容器，v的capacity就收缩到size
	// 3.执行完匿名容器的这行代码，系统会自动回收匿名容器，不存在匿名容器浪费空间的现象 
	vector<int>(v).swap(v);
	cout<<v.capacity();
}

// 预留空间
void test07() {
	int i;
	vector<int> v;
	v.reserve(100000);// 给容器预留100000个元素长度，可以减少容器重新分配空间的次数 
	int num = 0;
	int *p = NULL;
	for (i = 0; i < 100000; i++) {
		v.push_back(i + 1);
		if (p != &v[0]) {
			num++;
			cout<<"pre: "<<p;
			p = &v[0];
			cout<<", now: "<<p<<endl;
		}
	}
	cout<<"num: "<<num<<endl;
} 

int main () {
//	test01();
//	test02();
//	test03();
//	test04();
//	test05();
//	test06();
//	test07();
	return 0;
}

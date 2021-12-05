#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

// ���캯�� 
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

// ��ֵ
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

// �������С
void test03() {
	vector<int> v;
	int i;
	for (i = 0; i < 10; i++) {
		v.push_back(i + 1);
	}
	
	cout<<v.capacity()<<endl;
	cout<<v.size()<<endl;
	
	// �������䳤����-1��䣬����ɾ���������ȵ�Ԫ�� 
	v.resize(12, -1);// ע������capacity���ı����ڵ������size����С��capacity 
	cout<<v.capacity()<<endl;
	vector<int>::iterator it;
	for (it = v.begin(); it != v.end(); it++) {
		cout<<*it<<" ";
	}
	cout<<endl;
	
	v.resize(17, -1);//capacity������ڵ�����size������capacity 
	cout<<v.capacity()<<endl;
} 

// �����ɾ��
void test04() {
	vector<int>::iterator it;
	vector<int> v;
	v.push_back(10);//β������ 
	v.pop_back();//ɾ��β��Ԫ�� �����ر�ɾ����Ԫ�� 
	int i;
	for (i = 0; i < 10; i++) {
		v.push_back(i + 1);
	}
	
	v.insert(v.begin() + 2, 5);
	v.insert(v.begin() + 2, 5, -1);//��λ��Ϊ2�ĵط�����5��-1 
	v.erase(v.begin()); 
	v.erase(v.begin(), v.end() - 1);// ɾ��������[v.begin(), v.end() - 1)��Ԫ��; 
	v.clear();// ���Ԫ�� 
	for (it = v.begin(); it != v.end(); it++) {
		cout<<*it<<" ";
	}
	cout<<endl;
} 

// ���ݴ�ȡ
void test05() {
	vector<int> v;
	int i;
	for (i = 0; i < 10; i++) {
		v.push_back(i + 1);
	}
	
	cout<<v[9]<<endl;
	cout<<v.at(9)<<endl;
	
	cout<<v.front()<<endl;//�����׸�Ԫ�� 
	cout<<v.back()<<endl;// ����ĩβԪ�� 
} 

// ��������Ԫ��
void test06() {
	vector<int> v;
	int i;
	for (i = 0; i < 10000; i++)
		v.push_back(i);
	// ��ʱ�����϶�����ڳ��Ⱥܶ࣬���˷ѿռ� 
	cout<<v.capacity()<<endl;
	// �������������Կռ��������
	// 1.�Ȳ��ô�����������ʽ��ʼ��һ������������capacity��size��ȣ������ڶ���Ŀռ�
	// 2.��������������v����swap���������н�������ôv��ָ�����������������������ָ����v��������v��capacity��������size
	// 3.ִ�����������������д��룬ϵͳ���Զ������������������������������˷ѿռ������ 
	vector<int>(v).swap(v);
	cout<<v.capacity();
}

// Ԥ���ռ�
void test07() {
	int i;
	vector<int> v;
	v.reserve(100000);// ������Ԥ��100000��Ԫ�س��ȣ����Լ����������·���ռ�Ĵ��� 
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

main () {
//	test01();
//	test02();
//	test03();
//	test04();
//	test05();
//	test06();
//	test07();
	return 0;
}

#include<iostream>
using namespace std;

void print(int a, int b) {
	cout<<"普通函数"<<endl;
}

template<typename T>
void print(T a, T b) {
	cout<<"模板函数\n";
}

template<typename T>
void print(T a, T b, T c) {
	cout<<"重载的模板函数\n";
}

int main () {
	print(5, 6); // ��ͨ
	print<>(5, 6); // ģ��
	print(5, 6, 7); // ����
	print('a', 'b'); // ģ�� 
	return 0;
}

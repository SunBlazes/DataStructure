#include<iostream>
using namespace std;

void print(int a, int b) {
	cout<<"��ͨ����"<<endl;
}

template<typename T>
void print(T a, T b) {
	cout<<"ģ�庯��\n";
}

template<typename T>
void print(T a, T b, T c) {
	cout<<"���ص�ģ�庯��\n";
}

main () {
	print(5, 6); // ��ͨ
	print<>(5, 6); // ģ��
	print(5, 6, 7); // ����
	print('a', 'b'); // ģ�� 
	return 0;
}

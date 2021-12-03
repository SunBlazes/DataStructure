#include<iostream>
#include<string>
using namespace std;

// ���캯��
void test01() {
	string str;
	
	const char *a = "hello world";
	string str1(a);
	
	string str2(str1);
	
	string str3(9, '0');
	cout<<str3;
} 

// ��ֵ���� 
void test02() {
	string str1 = "hello ", str2 = "world";
	str1 = str2;
	cout<<str1<<endl;
	
	str1.assign("hello world");
	str1.assign(str2);
	cout<<str1<<endl;
	
	str1.assign(8, '0');
	cout<<str1<<endl;
}

// ƴ������
void test03() {
	string str1 = "hello ", str2 = "world";
	str1 += str2;
	
	str1.append("!");
	cout<<str1<<endl;
	
	str1.append(str2);
	
	str1.append(9, '!');
	cout<<str1<<endl; 
	
	str1 = "abcd"; str2 = "efghi";
	str1.append("123", 2);
	cout<<str1<<endl;
	
	str1.append(str2, 3, 2);
	cout<<str1<<endl;
} 

// ���Һ��滻
void test04() {
	string str = "abcdabc";
	
	// ���Ҷ��ٸ�"abc"
//	int n = 0, loca = 0;
//	string find_str = "abc";
//	do {
//		if ((loca = str.find(find_str, loca)) != -1) {
//			n++;
//			loca += find_str.length();
//		}
//	} while (loca != -1);
//	cout<<n<<endl;
	
//	string::iterator it_str;
//	for(it_str = str.begin(); it_str != str.end(); it_str++) {
//		cout<<*it_str;
//	}
	int pos = str.rfind("abc", str.length() - 1);
	cout<<pos<<endl;
	
	// ��str�ĵ�5λ����abc�ַ�����ǰ1���ַ� 
	pos = str.find("abc", 5, 1); 
	cout<<pos<<endl;
	
	// ��3��λ��ѡȡ1���ַ�������"DDDDD"���� 
	str.replace(3, 1, "DDDDD");
	cout<<str<<endl;
} 

// �ַ����Ƚ�
void test05() {
	string str1 = "abc", str2 = "abc";
	cout<<str1.compare(str2)<<endl;
	
	str1 = "abc", str2 = "dbc";
	cout<<str1.compare(str2)<<endl;
	
	str1 = "dbc", str2 = "abc";
	cout<<str1.compare(str2)<<endl;
} 

// �ַ���ȡ
void test06() {
	string str = "hello world";
	cout<<str[4]<<endl;
	cout<<str.at(4)<<endl;
	
	str[4] = 65;
	cout<<str[4]<<endl;
	
	str.at(4) = 66;
	cout<<str[4]<<endl;
} 

// ������ɾ�� 
void test07() {
	string str = "hello world";
	
	str.insert(5, "zero");
	cout<<str<<endl;
	
	str.insert(9, 5, ' ');
	cout<<str<<endl;
	
	str.erase(5, 9);
	cout<<str<<endl;
	
	str.erase(5);
	cout<<str<<endl;
}

// �ִ���ȡ
void test08() {
	string str = "hello world!";
	cout<<str.substr(0, 7)<<endl;
	
	string str1 = "986176132@qq.com";
	int QQ_Number_Len = str1.find('@');
	int Mail_Type_Len = str1.find('.') - QQ_Number_Len - 1;
	string QQ_Number = str1.substr(0, QQ_Number_Len);
	string Mail_Type = str1.substr(QQ_Number_Len + 1, Mail_Type_Len);
	string suffix = str1.substr(str1.rfind(".") + 1);
	cout<<QQ_Number<<'@'<<Mail_Type<<"."<<suffix<<endl;
}
 
main () {
//	test01();
//	test02();
//	test03();
//	test04();
//	test05();
//	test06();
//	test07();
	test08();
	return 0; 
}

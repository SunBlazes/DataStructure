#include<iostream>
#include<string>
using namespace std;

class Solution {
	public:
		string GetSpell(int number) {
			switch (number) {
				case 0: return "zero";
				case 1: return "one";
				case 2: return "two";
				case 3: return "three";
				case 4: return "four";
				case 5: return "five";
				case 6: return "six";
				case 7: return "seven";
				case 8: return "eight";
				case 9: return "nine";
			}
		}
		void Handler() {
			string number;
			int i;
			int sum = 0;
			int len;
			string arr[100];
			cin>>number;
			if (number == "0") {
				cout<<"zero";
				return;
			}
			for (i = 0; i < number.size(); i++) {
				sum += number[i] - '0';
			}
			i = 0;
			len = 0;
			while (sum) {
				arr[i++] = GetSpell(sum % 10);
				sum /= 10;
			}
			len = i;
			for (i = len -1; i >= 0; i--) {
				cout<<arr[i];
				if (i) {
					cout<<" ";
				}
			}
		}
}; 

int main () {
	Solution S;
	S.Handler(); 
	return 0;
} 

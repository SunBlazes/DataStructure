#include<iostream>
#include<string.h>
using namespace std;

class Solution {
	public:
		string GetSpell(int number) {
			switch (number) {
				case 0: return "ling";
				case 1: return "yi";
				case 2: return "er";
				case 3: return "san";
				case 4: return "si";
				case 5: return "wu";
				case 6: return "liu";
				case 7: return "qi";
				case 8: return "ba";
				case 9: return "jiu";
			}
		}
		int Handler() {
			string number;
			int i;
			int sum = 0;
			int len;
			string arr[100];
			cin>>number;
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
} 

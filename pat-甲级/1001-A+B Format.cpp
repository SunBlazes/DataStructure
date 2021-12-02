#include<iostream>
#include<math.h>
#include<stack>
using namespace std;

class Solution {
	public:
		void Handler() {
			int a, b;
			cin>>a>>b;
			int sum = a + b, temp = abs(sum);
			if (!sum) {
				cout<<sum;
				return;
			}
			string str = "";
			while (temp) {
				str += (char)(temp % 10 + '0');
				temp /= 10;
			}
			stack<char> s;
			int i;
			if (sum < 0) cout<<"-";
			for (i = 0; i < str.length(); i++) {
				s.push(str[i]);
				if ((i + 1) % 3 == 0 && i != str.length() - 1) {
					s.push(',');
				}
			}
			while (!s.empty()) {
				cout<<s.top();
				s.pop();
			}
		}
};

int main () {
	Solution S;
	S.Handler();
	return 0;
}

#include<iostream>
using namespace std;

class Solution {
	public:
		void Handler() {
			int n;
			int i;
			string str;
			cin>>n;
			for (i = 0; i < n; i++) {
				cin>>str;
				int j;
				int arr[3] = {0}; 
				
				int n1 = 0, n2 = 0, n3 = 0;
				bool _p = false, _t = false;
				bool fail = false;
				for (j = 0; j < str.length(); j++) {
					if (str[j] == 'P') arr[0]++;
					else if (str[j] == 'A') arr[1]++;
					else if (str[j] == 'T') arr[2]++;
					else if (str[j] != ' ') {
						fail = true;
						break;
					}
				}
				if (!fail) {
					if (arr[0] > 1 || !arr[0] || !arr[1] || arr[2] > 1 || !arr[2]) {
						fail = true;
					} else {
						for (j = 0; j < str.length(); j++) {
							if (str[j] == 'P') _p = true;
							if (str[j] == 'T') _t = true;
							if (str[j] == 'A' && !_p && !_t) n1++;
							else if (str[j] == 'A' && _p && !_t) n2++;
							else if (str[j] == 'A' && _p && _t) n3++;
						}
						if (!n2 || n1 * n2 != n3) {
							fail = true;
						}
					}
				}
				if (fail) {
					cout<<"NO";
				} else {
					cout<<"YES";
				}
				if (i != n - 1) cout<<endl;
			}
		}
}; 

int main () {
	Solution S;
	S.Handler(); 
}  

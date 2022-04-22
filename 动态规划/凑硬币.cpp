#include<iostream>
#define Max_Value ~(1<<31)

using namespace std;

/*
	@content:假定给定一个金额N，现有面值为2、5、7元硬币，
			 如何用最少的硬币集到N 
*/

class Solution {
	public:
		void handler() {
			int N;
			cin>>N;
			int i;
			int f[N + 1] = {0}; 
			int coins[] = {2, 5, 7};
			int n = 3;
			for (i = 1; i <= N; i++) {
				int j;
				f[i] = Max_Value;
				for (j = 0; j < n; j++) {
					if (i >= coins[j] && f[i - coins[j]] != Max_Value) {
						f[i] = min(f[i], f[i - coins[j]] + 1);
					}
				}
			}
			if (f[N] == Max_Value) {
				cout<<"当前已有的面值无法凑到所需的金额: "<<N<<endl;
			} else {
				cout<<f[N]<<endl;
			}
		}
}; 

int main () {
	Solution S;
	S.handler();
	return 0;
} 

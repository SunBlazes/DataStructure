#include<iostream>
#define Max_Value ~(1<<31)

using namespace std;

/*
	@content:�ٶ�����һ�����N��������ֵΪ2��5��7ԪӲ�ң�
			 ��������ٵ�Ӳ�Ҽ���N 
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
				cout<<"��ǰ���е���ֵ�޷��յ�����Ľ��: "<<N<<endl;
			} else {
				cout<<f[N]<<endl;
			}
		}
}; 

main () {
	Solution S;
	S.handler();
	return 0;
} 

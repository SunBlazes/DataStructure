#include<iostream>
using namespace std;

/*
	@content:�ٶ�����һ������a[3,2,1,0,3],a[i]��ʾ�������������
			 �������ܴ�0��λ������n-1���������ܷ����� 
*/
int N;
class Solution {
	public:
		void handler() {
			int i, j;
			cin>>N;
			int a[N], A[N] = {0};
			A[0] = 1;
			for (i = 0; i < N; i++) {
				cin>>a[i];
				if (i != 0) {
					for (j = i - 1; j >= 0; j--) {
						if (A[j]) {
							A[i] = (a[j] + j >= i);
							if (A[i]) {
								break;
							}
						}
					}
				}
			}
			cout<<A[N - 1];
		}
}; 

main () {
	Solution S;
	S.handler();
	return 0;
} 

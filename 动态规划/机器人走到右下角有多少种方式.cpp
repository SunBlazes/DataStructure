#include<iostream>

using namespace std;

/*
	@content:�ٶ�����һ������A[M][N]����ʼλ�ã�0,0���� 
	         �ߵ�ָ��λ�� ��M-1��N-1���ж������߷�
			 ����涨������ֻ�����һ��������� 
*/
int M, N;
class Solution {
	public:
		void handler() {
			int i, j;
			cin>>M>>N;
			int A[M][N];
			int m = M - 1, n = N - 1;
			for (i = 0; i < M; i++) {
				for (j = 0; j < N; j++) {
					if (!i || !j) {
						A[i][j] = 1;
					} else {
						A[i][j] = A[i-1][j] + A[i][j - 1];
					}
				}
			}
			cout<<A[m][n]<<endl;
		}
}; 

main () {
	Solution S;
	S.handler();
	return 0;
} 

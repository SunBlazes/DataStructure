#include<iostream>

using namespace std;

/*
	@content:假定给定一个矩阵A[M][N]、初始位置（0,0）， 
	         走到指定位置 （M-1，N-1）有多少种走法
			 这里规定机器人只能向右或者向下走 
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

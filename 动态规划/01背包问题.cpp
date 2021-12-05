#include<iostream>
using namespace std;

/*
	@content:
*/
int N, W;
class Solution {
	public:
		void handler() {
			cin>>N>>W;
			int i, j, A[N + 1][W + 1];
			int w[N + 1], v[N + 1];
			for (i = 1; i <= N; i++) {
				cin>>w[i]>>v[i];
			}
			for (i = 0; i <= N; i++) {
				for (j = 0; j <= W; j++) {
					if (!i || !j) {
						A[i][j] = 0;
					} else {
						if (j >= w[i]) {
							A[i][j] = max(A[i - 1][j - w[i]] + v[i], A[i - 1][j]);
						} else {
							A[i][j] = A[i - 1][j];
						}
					}
				}
			}
			for (i = 1; i <= N; i++) {
				for (j = 1; j <= W; j++) {
					cout<<A[i][j]<<"\t";
				}
				cout<<endl;
			}
			cout<<A[N][W];
		}
}; 

main () {
	Solution S;
	S.handler();
	return 0;
} 

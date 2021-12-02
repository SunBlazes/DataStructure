#include<iostream>
using namespace std;

class Solution {
	public:
		void Handler() {
			int n1, n2;
			int i;
			cin>>n1;
			double A[n1 + 1][2];
			for (i = 0; i < n1; i++) {
				cin<<A[i][0]<<A[i][1];
			}
			cin>>n2;
			double B[n2 + 1][2];
			for (i = 0; i < n2; i++) {
				cin<<B[i][0]<<B[i][1];
			}
			int K = n1 + n2;
			
		}
};

int main () {
	Solution S;
	S.Handler();
	return 0;
}

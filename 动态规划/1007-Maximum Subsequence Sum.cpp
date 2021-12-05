#include<iostream>
using namespace std;
int K;
int a[10001];

class Solution {
	public:
		void Handler() {
			cin>>K;
			int i;
			for (i = 1; i <= K; i++) {
				cin>>a[i];
			}
			int sum = -1, tmp = 0, l = 1, r = K, p = 1;
			for (i = 1; i <= K; i++) {
				if (tmp + a[i] < 0) {
					tmp = 0;
					p = i + 1;
				} else {
					tmp += a[i];
					if (tmp > sum) {
						l = p;
						r = i;
						sum = tmp;
					}
				}
			}
			if (sum == -1) {
				cout<<0<<" "<<a[1]<<" "<<a[K];
			} else {
				cout<<sum<<" "<<a[l]<<" "<<a[r];
			}
		}
};

int main () {
	Solution S;
	S.Handler();
	return 0;
}

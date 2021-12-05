#include<iostream>
using namespace std;
int K;
int a[10001];
// 思路:
// 1.最大子序列第一个肯定是非负数
// 2.假设当前子序列之和为temp,起始点为start,末尾点为end
//   如果碰到一个索引为end+1的值使temp变小，说明索引区间start~end，temp值为最大 
//   但由于这个区间便不是完整区间，所以需要缓存这个temp，start，end  
class Solution {
	public:
		void Handler() {
			cin>>K;
			int i;
			for (i = 1; i <= K; i++) {
				cin>>a[i];
			}
			int sum = 0, start = 0, end = 0, temp = 0, t_start = 0, t_end = 0;
			int n_num = 0;
			for (i = 1; i <= K; i++) {
				if (a[i] + temp >= 0) {
					if (a[i] + temp > temp) {
						temp += a[i];
						if (!t_start) t_start = i;
						t_end = i;
					} else {
						if (sum < temp) {
							sum = temp;
							start = t_start;
							end = t_end;
						}
						int j, ttemp = temp + a[i];
						t_end = i;
						for (j = i + 1; j <= K; j++) {
							if (a[j] + ttemp > max(ttemp, temp)) {
								t_end = j;
								ttemp += a[j];
							} else {
								break;
							}
						}
						i = j;
						if (sum < ttemp) {
							sum = ttemp;
							end = t_end;
						}
						temp = 0;
						t_start = 0;
						t_end = 0;
					}
				} else {
					temp = 0;
					t_start = i + 1;
					n_num++;
				}
			}
			if (sum < temp) {
				sum = temp;
				end = t_end;
				start = t_start;
			}
			if (n_num == K) {
				cout<<0<<" "<<a[1]<<" "<<a[K]; 
			} else {
				cout<<sum<<" "<<a[start]<<" "<<a[end];
			}
		}
};

int main () {
	Solution S;
	S.Handler();
	return 0;
}

#include<iostream>
using namespace std;
int K;
int a[10001];
// ˼·:
// 1.��������е�һ���϶��ǷǸ���
// 2.���赱ǰ������֮��Ϊtemp,��ʼ��Ϊstart,ĩβ��Ϊend
//   �������һ������Ϊend+1��ֵʹtemp��С��˵����������start~end��tempֵΪ��� 
//   �������������㲻���������䣬������Ҫ�������temp��start��end  
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

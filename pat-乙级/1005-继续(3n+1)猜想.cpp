#include<iostream>
using namespace std;

class Solution {
	public:
		int find_loca(int arr[], int el, int len) {
			int loca = -1;
			int i;
			for (i = 0; i < len; i++) {
				if (arr[i] == el) {
					loca = i;
					break;
				}
			}
			return loca;
		}
		int Handler() {
			int count;
			int i;
			cin>>count;
			int arr[count];
			bool covered[count] = {false};
			for (i = 0; i < count; i++) {
				cin>>arr[i];
			}
			for (i = 0; i < count; i++) {
				if (!covered[i]) {
					int number = arr[i];
					while (number != 1) {
						if (number % 2) {
							number = (number * 3 + 1) / 2;
						} else {
							number /= 2;
						}
						int loca = find_loca(arr, number, count);
						if (loca != -1) {
							covered[loca] = true;
						}
					}
				}
			}
			int len = 0;
			for (i = 0; i < count; i++) {
				if (!covered[i]) {
					arr[len++] = arr[i];
				}
			}
			for (i = 1; i < len; i++) {
				int j;
				int P = arr[i];
				for (j = i; j > 0 && arr[j - 1] < P; j--) {
					arr[j] = arr[j - 1];
				}
				arr[j] = P;
			}
			for (i = 0; i < len; i++) {
				cout<<arr[i];
				if (i != len - 1) {
					cout<<" ";
				}
			}
		}
}; 

int main () {
	Solution S;
	S.Handler(); 
} 

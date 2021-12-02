#include<iostream>
#include<math.h>
using namespace std;

class Solution {
	public:
		bool is_Prime(int number) {
			int end = ceil(sqrt(number));
			int i;
			for (i = 2; i <= end; i++) {
				if (!(number % i)) return false;
			}
			return true;
		}
		void Handler() {
			int n;
			int i;
			int count = 0;
			cin>>n;
			for (i = 2; i <= n - 2; i++) {
				if (is_Prime(i) && is_Prime(i + 2)) count++;
			}
			cout<<count;
		}
}; 

int main () {
	Solution S;
	S.Handler(); 
	return 0;
} 

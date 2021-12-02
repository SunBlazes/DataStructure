#include<iostream>
using namespace std;

class Solution {
	public:
		int Handler() {
			int number;
			int count = 0;
			cin>>number;
			while (number != 1) {
				if (number % 2) {
					number = (number * 3 + 1) / 2;
				} else {
					number /= 2;
				}
				count++;
			}
			cout<<count;
		}
}; 

int main () {
	Solution S;
	S.Handler(); 
} 

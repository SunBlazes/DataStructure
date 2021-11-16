#include <stdio.h>

int main() {
	int n;
	scanf("%d", &n);
	int isPrime[n], i = 0;
	
	for (; i < n; i++){
		isPrime[i] = 1;
	}
	
	for (i = 2; i < n; i++) {
		if (isPrime[i]) {
			int j = 2;
			for (; j * i < n; j++) {
				isPrime[j * i] = 0;
			}
		}
	}
	
	for (i = 1; i < n; i++) {
		if (isPrime[i]) {
			printf("%d\t", i);
		}
	}
}


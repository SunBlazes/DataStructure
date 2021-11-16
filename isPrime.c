#include <stdio.h>

int isPrime(int x, int knowsPrimes[], int numberOfPrimes);

int main()
{
	int number = 100;
	int primes[100] = {2};
	int count = 1;
	int i = 3;
	
	while (count < number) {
		if (isPrime(i, primes, count) != -1) {
			primes[count++] = i;
		} 
		i++;
	}
	
	for (i = 0; i < number; i++) {
		printf("%d\n", primes[i]);
	}
}

int isPrime(int x, int knowsPrimes[], int numberOfPrimes) {
	int i = 0, ret = 1;
	
	for (; i < numberOfPrimes; i++) {
		if (x % knowsPrimes[i] == 0) {
			ret = -1;
			break;
		}
	}
	
	return ret;
}


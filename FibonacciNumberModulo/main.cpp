#include <cassert>
#include <iostream>
using namespace std;

int getPisano(int m) {
	int a = 0;
	int b = 1;
	
	for (int i=2;true;i++){
		std::swap(a, b);
		// b += a;
		b = (b + a) % m;
		if (b == 0 && a == 1){
			return i;
		}
	}
}

int fibonacci_fast(int n, int m) {
	if (n <= 1)
		return n;
	int a = 0;
	int b = 1;
	
	for (int i=2;i<=n;i++){
		std::swap(a, b);
		b = (b + a) % m;
	}
	return b;
}

long long get_fibonacci_huge_optimized(long long n, long long m) {
	int pisano = getPisano(m);
	return fibonacci_fast(n % pisano, m);
}


long long get_fibonacci_huge_naive(long long n, long long m) {
	if (n <= 1)
		return n;

	long long previous = 0;
	long long current  = 1;

	for (long long i = 0; i < n - 1; ++i) {
		long long tmp_previous = previous;
		previous = current;
		current = tmp_previous + current;
	}

	return current % m;
}

int main() {
	long long n, m;
	assert (getPisano(3) == 8);
	std::cin >> n >> m;
	// std::cout << get_fibonacci_huge_naive(n, m) << '\n';
	std::cout << get_fibonacci_huge_optimized(n, m) << '\n';
}

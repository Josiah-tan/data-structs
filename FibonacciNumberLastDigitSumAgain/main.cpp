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

int fibonacci_sum_optimized(long long n){
	return get_fibonacci_huge_optimized(n + 2, 10) - 1;
}

int fibonacci_sum_naive(long long n) {
    if (n <= 1)
        return n;

    long long previous = 0;
    long long current  = 1;
    long long sum      = 1;

    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
        sum += current;
    }

    return sum % 10;
}

int main() {
    long long m, n;
    std::cin >> m >> n;
    // std::cout << fibonacci_sum_naive(n);
		std::cout << (10 + fibonacci_sum_optimized(n) - fibonacci_sum_optimized(m - 1)) % 10;
}

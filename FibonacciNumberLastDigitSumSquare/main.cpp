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
	int fn_1, fn;
	fn_1 = get_fibonacci_huge_optimized(n - 1, 10);
	fn = get_fibonacci_huge_optimized(n, 10);
	return (fn + fn_1) * fn % 10;
}




int main() {
    long long n = 0;
    std::cin >> n;
    std::cout << fibonacci_sum_optimized(n);
}

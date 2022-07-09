#include <iostream>

int get_fibonacci_last_digit_naive(int n) {
    if (n <= 1)
        return n;

    int previous = 0;
    int current  = 1;

    for (int i = 0; i < n - 1; ++i) {
        int tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
    }

    return current % 10;
}

int get_fibonacci_last_digit_fast(int n) {
	if (n <= 1)
		return n;
	int a = 0;
	int b = 1;
	for (int i=2;i<=n;i++){
		if (i & 1) { // I think this is odd probably
			b = (b + a) % 10;
			// b += a;
		}
		else {
			// a += b;
			a = (a + b) % 10;
		}
	}
	return n & 1 ? b : a;
}

int main() {
    int n;
    std::cin >> n;
    // int c = get_fibonacci_last_digit_naive(n);
    int c = get_fibonacci_last_digit_fast(n);
    std::cout << c << '\n';
    }

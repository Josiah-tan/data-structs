#include <iostream>

int gcd_naive(int a, int b) {
  int current_gcd = 1;
  for (int d = 2; d <= a && d <= b; d++) {
    if (a % d == 0 && b % d == 0) {
      if (d > current_gcd) {
        current_gcd = d;
      }
    }
  }
  return current_gcd;
}

int gcd_optimized(int a, int b){
	if (a == b){
		return a;
	}
	if (a == 0 || b == 0){
		return a + b;
	}
	if (a > b){
		return gcd_optimized(b, a % b);
	}
	else{
		return gcd_optimized(a, b % a);
	}
}

void test() {
  int a, b;
  std::cin >> a >> b;
  // std::cout << gcd_naive(a, b) << std::endl;
  std::cout << gcd_optimized(a, b) << std::endl;
}

void stress(){
	while(true){
		int a, b;
		a = rand() % 10000 + 1;
		b = rand() % 10000 + 1;
		if (gcd_optimized(a, b) != gcd_naive(a, b)){
			std::cout << "gcd_optimized(a, b) " << gcd_optimized(a, b) << std::endl;
			std::cout << "gcd_naive(a, b) " << gcd_naive(a, b) << std::endl;
		}
			std::cout << "gcd_optimized(a, b) " << gcd_optimized(a, b) << std::endl;
	}
}

int main() {
  // test();
	stress();
  return 0;
}

#include <iostream>

long long lcm_naive(int a, int b) {
  for (long l = 1; l <= (long long) a * b; ++l)
    if (l % a == 0 && l % b == 0)
      return l;

  return (long long) a * b;
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

long long lcm_optimized(int a, int b) {
	return (long long) (a) * b / gcd_optimized(a, b);
}


int main() {
  int a, b;
  std::cin >> a >> b;
  // std::cout << lcm_naive(a, b) << std::endl;
  std::cout << lcm_optimized(a, b) << std::endl;
  return 0;
}

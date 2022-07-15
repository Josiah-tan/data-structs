#include <cassert>
#include <iostream>
#include <vector>

using std::vector;

vector<int> optimal_summands(int n) {
  vector<int> sums;
	int sum = 0;
	for (int i = 1; i <= n; i++){
		if (sum + i > n){
			sums[sums.size() - 1] += n - sum;
			sum += n - sum;
			break;
		}
		else if (sum + i == n){
			sums.push_back(i);
			sum += i;
			break;
		}
		else {
			sums.push_back(i);
			sum += i;
		}
	}
	assert (sum == n);
  return sums;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> summands = optimal_summands(n);
  std::cout << summands.size() << '\n';
  for (size_t i = 0; i < summands.size(); ++i) {
    std::cout << summands[i] << ' ';
  }
}

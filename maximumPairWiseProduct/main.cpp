#include <limits>
#include <iostream>
#include <vector>
#include <algorithm>

long long maxPairwiseProduct(const std::vector<int>& numbers) {
	long long max_product = 0;
	int n = numbers.size();

	for (int first = 0; first < n; ++first) {
		for (int second = first + 1; second < n; ++second) {
			max_product = std::max(max_product,
					((long long) numbers[first]) * numbers[second]);
		}
	}

	return max_product;
}

long long maxPairwiseProductOptimal(const std::vector<int>& numbers){
	int n = numbers.size();
	int a = 0;
	int b = 0;
	for (int i=1;i<n;i++){
		if (numbers[a] < numbers[i]){
			a = i;
		}
	}
	for (int i=1;i<n;i++){
		if (i != a && numbers[b] < numbers[i]){
			b = i;
		}
	}
	return ((long long) numbers[a]) * numbers[b];
}

int test(){
	int n;
	std::cin >> n;
	std::vector<int> numbers(n);
	for (int i = 0; i < n; ++i) {
		std::cin >> numbers[i];
	}

	// std::cout << maxPairwiseProduct(numbers) << "\n";
	std::cout << maxPairwiseProductOptimal(numbers) << "\n";
	return 0;
}

int stress(){
	while (true){
		int n = rand() % 100 + 2; // [2, 101]
		std::vector<int> numbers(n);
		for (int i = 0; i < n; ++i) {
			numbers[i] = rand() % 1000;
		}
		if (maxPairwiseProductOptimal(numbers) == maxPairwiseProductOptimal(numbers)){
			printf("correct!");
			std::cout << "maxPairwiseProductOptimal(numbers) " << maxPairwiseProductOptimal(numbers)  << std::endl;
		  std::cout << "maxPairwiseProductOptimal(numbers) " << maxPairwiseProductOptimal(numbers) << std::endl;
		}
		else{
			printf("incorrect!");
			std::cout << "maxPairwiseProductOptimal(numbers) " << maxPairwiseProductOptimal(numbers)  << std::endl;
		  std::cout << "maxPairwiseProductOptimal(numbers) " << maxPairwiseProductOptimal(numbers) << std::endl;
		}
	}
}

int main() {
	// test();
	stress();
}

#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;

struct IndexPrice
{
	int index;
	double price;
	IndexPrice(int index, double price) : index(index), price(price) {}
};

struct less_than_key
{
    inline bool operator() (const IndexPrice& struct1, const IndexPrice& struct2)
    {
        return (struct1.price < struct2.price);
    }
};

double get_optimal_value(int capacity, vector<int> weights, vector<int> values) {
	double value = 0.0;
	int n = weights.size();
	std::vector <IndexPrice> v;
	for (int i = 0; i < n; i++){
		v.push_back(IndexPrice(i, (double)(values[i]) / weights[i]));
	}
	std::sort(v.begin(), v.end(), less_than_key());
	for (int i = n - 1; i >= 0; i--){
		if (capacity == 0){
			break;
		}
		int weight = std::min(capacity, weights[v[i].index]);
		value += weight * v[i].price;
		capacity -= weight;
	}
	return value;
}

int main() {
  int n;
  int capacity;
  std::cin >> n >> capacity;
  vector<int> values(n);
  vector<int> weights(n);
  for (int i = 0; i < n; i++) {
    std::cin >> values[i] >> weights[i];
  }

  double optimal_value = get_optimal_value(capacity, weights, values);

  std::cout.precision(10);
  // std::cout << optimal_value << std::endl;
	printf("%.4f", optimal_value);
  return 0;
}

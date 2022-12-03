#include <algorithm>
#include <cmath>
#include <iostream>
#include <cassert>
#include <vector>

using std::vector;
using std::endl;
using std::cout;

int binary_search(const vector<int> &a, int x) {
  int left = 0, right = (int)a.size() - 1; 
	while (left < right){
		int mid = (left + right) / 2;
		if (a[mid] == x){
			right = mid;
		}
		else if (a[mid] < x){
			left = mid + 1;
		}
		else{
			right = mid - 1;
		}
	}
	return left == right && a[right] == x ? right : -1;
}

int linear_search(const vector<int> &a, int x) {
  for (size_t i = 0; i < a.size(); ++i) {
    if (a[i] == x) return i;
  }
  return -1;
}

void test() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); i++) {
    std::cin >> a[i];
  }
  int m;
  std::cin >> m;
  vector<int> b(m);
  for (int i = 0; i < m; ++i) {
    std::cin >> b[i];
  }
  for (int i = 0; i < m; ++i) {
    //replace with the call to binary_search when implemented
    // std::cout << linear_search(a, b[i]) << ' ';
  std::cout << binary_search(a, b[i]) << ' ';
  }
}

void stress(){
	int t = 0;
	while(t < 1000){
		t++;
		int n = rand() % (10) + 1;
		vector<int> a(n);
		for (int i = 0; i < n; i++){
			a[i] = rand() % 100 + 1;
		}
		int k = rand() % 10 + 1;
		vector<int> b(k);
		for (int i = 0; i < k; i++){
			b[i] = rand() % 100 + 1;
		}
		std::sort(a.begin(), a.end());
		for (int i = 0; i < k; ++i){
			int bin = binary_search(a, b[i]);
			cout << "bin " << bin << endl;
			int linear = linear_search(a, b[i]);
			cout << "linear " << linear << endl;
			assert (bin == linear);
		}
	}
}

int main() {
  // test();
	stress();
}

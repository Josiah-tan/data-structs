#include"template.h"
#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>
#include<string>
#include<cassert>
#include<numeric>
#include<queue>

using namespace std;

int maxElement(int n, int maxSum, int k){
	int above = maxSum;
	int below = 1;
	int sm = 0;
	int ans = 0;
	while (above >= below){
		int m = (above + below) / 2;
		sm = m;
		if (k - (m - 1) < 0){
			sm += k * (m - 1 + m - k) / 2;
		}
		else {
			sm += k - (m - 1) + (m-1) * m / 2;
		}
		if (k + (m - 1) >= n){
			sm += (n - k - 1) * (m - 1 + m - 1 - (n - k - 2)) / 2;
		}
		else {
			sm += (m - 1) * m / 2 + n - (k + m - 1) - 1;
		}
		if (sm > maxSum){
			above = m - 1;
		}
		else if (sm <= maxSum){
			ans = max(ans, m);
			below = m + 1;
		}
	}
	return ans;
}

int maxElementNaive(int n, int maxSum, int k){
	vector<int> array(n, 1);
	int sum = n;
	while (sum <= maxSum){
		array[k]++;
		sum++;
		for (int i = k; i > 0 && array[i - 1] != array[i] - 1; i--){
			sum++;
			array[i - 1]++;
		}
		for (int i = k; i < n - 1 && array[i + 1] != array[i] - 1; i++){
			sum++;
			array[i + 1]++;
		}
		for (const auto & element: array){
			std::cout << element << " ";
		}
		std::cout << std::endl;
		std::cout << "sum = " << sum << std::endl;
	}
	return array[k] - 1;
}

int maxElementChocolate(int n, int num_chocolates, int pos) {
    assert(1 <= pos && pos <= n && n <= num_chocolates && num_chocolates <= 1000000000);

    auto check = [&](int x) {
        auto sumn = [](int k) { return (k * (k + 1)) / 2; };

        auto sumx = [&](int k) {
            if (x <= k) {
                return sumn(x) + k - x;
            } else {
                return sumn(x) - sumn(x - k);
            }
        };

        int ans = sumx(pos) + sumx(n - pos + 1) - x;
        return ans <= num_chocolates;
    };

    int lo = 1;
    int hi = num_chocolates + 1;

    while (hi - lo > 1) {
        int mid = (hi + lo) / 2;
        if (check(mid)) {
            lo = mid;
        } else {
            hi = mid;
        }
    }

    return lo;
}

int main(void){
	int n = 50;
	int maxSum = 100000;
	int k = 18;
	int naive = maxElementNaive(n, maxSum, k);
	cout << "naive: " << naive << endl;
	int real = maxElement(n, maxSum, k);
	cout << "real: " << real << endl;
	int chocolate = maxElementChocolate(n, maxSum, k);
	cout << "chocolate: " << chocolate << endl;
}


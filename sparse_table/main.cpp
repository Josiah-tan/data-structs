#include"template.h"
#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>
#include<string>
#include<cassert>
#include<numeric>
#include<queue>
#include<math.h>

using namespace std;

int log2Floor(unsigned long i){
	return i ? __builtin_clzll(1) - __builtin_clzll(i) : -1;
}

class SparseTable{
	private:
		vector<int> array;
		int k;
		int n;
	protected:
		int (*function)(int, int);
		vector<vector<int>> dp; // K = 25, MAX_N = 10 ^ 7
	public:
		SparseTable(vector<int> array, int (*function)(int, int)): array(array), function(function){
			// O(N log(N)) (space and time)
			n = array.size();
			k = log2Floor(n);
			dp = vector<vector<int>> (k, vector<int>(n));
			exit(0);
			std::copy(array.begin(), array.end(), dp[0].begin());

			for (int i = 1; i <= k; i++){
				for (int j = 0; j + (1 << i) <= n; j++){
					// [j, j + 2 ^ i - 1] = [j, j + 2 ^ (i - 1) - 1] + [j + 2 ^ (i - 1), j + 2 ^ i - 1];
					dp[i][j] = function(dp[i - 1][j], dp[i - 1][j + (1 << (i - 1))]);
					cout << "i: " << i << ", j: " << j << ", state[i][j]: " << dp[i][j] << endl;
				}
			}
		}
		long long query(int left, int right){
			// O (log(N));
			long long result = 0;
			for (int i = k; ~i; i--){
				if ((1 << i) <= right - left + 1){
					result = function(result, dp[i][left]);
					left += 1 << i;
				}
			}
			return result;
		}
};


class SparseTableMax : public SparseTable {
	public:
		SparseTableMax(vector<int> array) : SparseTable(array, [](int a, int b){return a > b ? a : b;}){
			// O(N log(N)) (space and time)
		}
		int query(int left, int right){
			// O(1)
			int length = right - left + 1;
			int log_length = log2Floor(length);
			// function((left, left + 2 ** log_length - 1), (right - 2 ** log_length + 1, right));
			// dp[i][j] = (j, j + 2 ^ i - 1);
			return function(dp[log_length][left], dp[log_length][right - (1 << log_length) + 1]);
	}
};

int main(void){
	SparseTable sparse_table_sum = SparseTable({1, 2, 3, 4}, [](int a, int b){return a + b;});
	assert(sparse_table_sum.query(2, 3) == 7);
	assert(sparse_table_sum.query(1, 3) == 9);
	SparseTableMax sparse_table_max = SparseTableMax({1, 2, 3, 4});
	assert(sparse_table_max.query(2, 3) == 4);
	assert(sparse_table_max.query(1, 3) == 4);
	assert(sparse_table_max.query(1, 2) == 3);
}

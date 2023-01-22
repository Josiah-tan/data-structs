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
	protected:
		int (*function) (int, int);
		vector<vector<int>> dp;
		int n;
		int k;
	public:
		SparseTable(vector<int> &array, int (*function) (int, int)): array(array), function(function){
			n = array.size();
			k = log2Floor(n);
			dp = vector<vector<int>>(k + 1, vector<int>(n));
			// dp[i][j] = [j, (j + 2^i - 1)]
			std::copy(array.begin(), array.end(), dp[0].begin());
			for (int i = 1; i <= k; i++){
				for (int j = 0; (j + (1 << i)) <= n; j++){
					// [j, (j + 2 ^ i - 1)] = [j, (j + 2 ^ (i - 1) - 1)] + [j + 2 ^ (i - 1), (j + 2 ^ i - 1)]
					dp[i][j] = function(dp[i - 1][j], dp[i - 1][j + (1 << (i - 1))]);
				}
			}
		}
		int query(int left, int right) {
			int answer = 0;
			for (int i = k; ~i; i--){
				if (1 << i <= right - left + 1){
					answer = function(answer, dp[i][left]);
					left += 1 << i;
				}
			}
			return answer;
		}
};

class TwoOverlapSparseTable : public SparseTable {
	public:
		TwoOverlapSparseTable(vector<int> &array, int(*function)(int, int)) : SparseTable(array, function){}
		int query(int left, int right){
			int length = right - left + 1;
			int log_length = log2Floor(length);
			return function(dp[log_length][left], dp[log_length][right - (1 << log_length) + 1]);
		}
};

class SparseTableMax : public TwoOverlapSparseTable {
	public:
		SparseTableMax(vector<int> &array) : TwoOverlapSparseTable(array, [](int a, int b){return a > b ? a : b;}){
		}
};

class SparseTableMin : public TwoOverlapSparseTable {
	public:
		SparseTableMin(vector<int> &array) : TwoOverlapSparseTable(array, [](int a, int b){return a < b ? a : b;}){
		}
};

int main(void){
	vector<int> array;
	array = {1, 2, 3, 4};
	SparseTable sparse_table_sum = SparseTable(array, [](int a, int b){return a + b;});
	assert(sparse_table_sum.query(2, 3) == 7);
	assert(sparse_table_sum.query(1, 3) == 9);
	array = {1, 2, 3, 4};
	SparseTableMax sparse_table_max = SparseTableMax(array);
	assert(sparse_table_max.query(2, 3) == 4);
	assert(sparse_table_max.query(1, 3) == 4);
	assert(sparse_table_max.query(1, 2) == 3);
	SparseTableMin sparse_table_min = SparseTableMin(array);
	assert(sparse_table_min.query(2, 3) == 3);
	assert(sparse_table_min.query(1, 3) == 2);
	assert(sparse_table_min.query(1, 2) == 2);
}

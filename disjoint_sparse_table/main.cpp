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

int floorLog2(int value){
	return __builtin_clz(value) ^ 31;
}

template <typename T, typename monoid, T identity>
class DisjointSparseTable{
	private:
		vector<vector<T>> dp;
		int log_size;
		int size;
	public:
		DisjointSparseTable(vector<T> array){
			// O(size * log_size) space + time
			size = array.size();
			log_size = floorLog2(size);
			if (1 << log_size < size){
				size = 1 << (++log_size);
			}
			array.resize(size, identity);
			dp.resize(log_size, vector<T>(size));
			for (int level = 0; level < log_size; level++){
				for (int block = 0; block < (1 << level); block++){
					const auto start = block << (log_size - level);
					const auto end = (block + 1) << (log_size - level);
					const auto middle = (start + end) >> 1;
					auto value = array[middle];
					dp[level][middle] = value;
					for (auto i = middle + 1; i < end; i++){
						value = monoid{}(value, array[i]);
						dp[level][i] = value;
					}

					value = array[middle - 1];
					dp[level][middle - 1] = value;
					for (auto i = middle - 2; i >= start; i--){
						value = monoid{}(array[i], value);
						dp[level][i] = value;
					}
				}
			}
		}
		T query(int left, int right) const {
			// O(1) → beautiful
			assert (left <= right);
			right--;
			if (right == left - 1){
				return identity;
			}
			if (right == left){
				return dp.back()[left];
			}
			// position_difference = logn - 1 - level;
			const auto position_difference = __builtin_clz(left ^ right) ^ 31;
			const auto level = log_size - 1 - position_difference;
			return monoid{}(dp[level][left], dp[level][right]);
		}
};

int main(void){
	vector<int> data{6, 2, 4, 1, 7, 3, 4, 2, 7, 2, 4, 1, 6};

	// vector<int> data(1000); // just to make absolutely sure it works
	// srand(time(0));
	// generate(data.begin(), data.end(), rand);
	
	DisjointSparseTable<int, plus<>, 0> DST{data};
	for (int start = 0; start < data.size(); ++start) {
		for (int end = start; end <= data.size(); ++end){
			assert(DST.query(start, end) == accumulate(begin(data) + start, begin(data) + end, 0));
		}
	}
}


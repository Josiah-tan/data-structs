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

template<typename T, typename monoid, T identity>
class SqrtDecomposition{
	private:
		int n;
		vector<T> array;
		int ceil_sqrt_n; // size of and number of blocks
		vector<T> blocks;
	public:
		SqrtDecomposition(vector<T> array): n(array.size()), array(array), ceil_sqrt_n((int)(sqrt((double)(n))) + 1), blocks(ceil_sqrt_n, identity){
			for (int i = 0; i < n; i++){
				blocks[i / ceil_sqrt_n] = monoid{}(blocks[i / ceil_sqrt_n], array[i]);
			}
		}
		int query(int left, int right){
			int solution = identity;
			int left_block = left / ceil_sqrt_n;
			int right_block = right / ceil_sqrt_n;
			if (left_block == right_block){
				for (int i = left; i <= right; i++){
					solution = monoid{}(solution, array[i]);
				}
			}
			else {
				for (int i = left, end = (left_block + 1) * ceil_sqrt_n; i < end; i++){
					solution = monoid{}(solution, array[i]);
				}
				for (int i = left_block + 1; i < right_block; i++){
					solution = monoid{}(solution, blocks[i]);
				}
				for (int i = right_block * ceil_sqrt_n; i <= right; i++){
					solution = monoid{}(solution, array[i]);
				}
			}
			return solution;
		}
};

int main(void){
	vector<int> array = {1, 2, 3, 4, 5};
	SqrtDecomposition<int, plus<>, 0> range_sum(array);
	assert(accumulate(array.begin() + 1, array.end(), 0) == range_sum.query(1, 4));
	assert(accumulate(array.begin() + 3, array.end(), 0) == range_sum.query(3, 4));
	assert(accumulate(array.begin() + 0, array.end(), 0) == range_sum.query(0, 4));
}


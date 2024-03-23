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

int floor2log(unsigned int x){
	return x ? __builtin_clz(x) ^ 31 : -1;
}

template<class T>
void disp(const vector<T> &list){
	for (auto const& element: list){
		cout << element << " ";
	}
	cout << endl;
}

class BitSlidingWindow{
	private:
		int log_window;
		int window;
		int pointer;
		int mask;
		vector<unsigned int> array;
		unsigned long long sum;
	public:
		BitSlidingWindow(int log_window) : log_window(log_window), window(1 << log_window), pointer(0), mask(window - 1), array(window, 0), sum(0){
		}
		unsigned int update(unsigned int element){
			sum -= array[pointer];
			sum += element;
			// sum += element - array[pointer];
			array[pointer] = element;
			pointer = (pointer + 1) & mask;
			return sum >> log_window;
		}
};


int main(void){
	int n = 10000;
	vector<unsigned int> array(n);
	int log_window = 25;
	generate(array.begin(), array.end(), []()->unsigned int{return rand();});
	// disp(array);
	BitSlidingWindow sliding_window(log_window);
	for (int i = 0; i < n; i++){
		unsigned long long answer = 0;
		for (int k = max(i - (1 << log_window ) + 1, 0); k <= i; k++){
			answer += array[k];
		}
		answer = answer >> log_window;
		unsigned int attempt = sliding_window.update(array[i]);
		// cout << i << " " << answer << " " << attempt << endl;
		assert(answer == attempt);
	}
}


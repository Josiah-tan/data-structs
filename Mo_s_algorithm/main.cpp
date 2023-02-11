#include"template.h"
#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>
#include<string>
#include<cassert>
#include<numeric>
#include<queue>
#include<cmath>

using namespace std;

// for this one use query sum as an example

struct Query {
	int left, right;
};

vector<int> querySumsNaive(int a[], int n, Query query[], int m){
	vector<int> solution;
	for (int i = 0; i < m; i++){
		int left = query[i].left;
		int right = query[i].right;
		int summation = 0;
		for (int j = left; j <= right; j++){
			summation += a[j];
		}
		cout << summation << endl;
		solution.push_back(summation);
	}
	return solution;
}

int block;

bool compare(Query x, Query y){
	// if (x.left / block != y.left / block){
	// 	return x.left / block < y.left / block;
	// }
	// return x.right < y.right;
	return make_pair(x.left / block, x.right) < make_pair(y.left / block, y.right);
}

vector<int> querySums(int a[], int n, Query query[], int m){
	vector<int> solution;
	block = (int) sqrt(n);
	// O(m log m)
	sort(query, query + m, compare);
	int current_left = 0, current_right = -1; // specifying initial empty range
	int current_sum = 0;
	// total operations: O((m + n)√n) → left moved m * √n times; right moved n * √n times
	// total complexity (O(m + n)F√n) O(F) complexity of add and remove function
	for (int i = 0; i < m; i++){
		int left = query[i].left, right = query[i].right;
		while (current_left < left) current_sum -= a[current_left++];
		while (current_left > left) current_sum += a[--current_left];
		while (current_right < right) current_sum += a[++current_right];
		while (current_right > right) current_sum -= a[current_right--];
		cout << current_sum << endl;
		solution.push_back(current_sum);
	}
	return solution;
}

int main(void){
	int a[] = {1, 1, 2, 1, 3, 4, 5, 2, 8};
	int n = sizeof(a) / sizeof(a[0]);
	Query q[] = {{0, 4}, {1, 3}, {2, 4}};
	int m = sizeof(q)/sizeof(q[0]);
	querySumsNaive(a, n, q, m);
	std::cout << "##########" << std::endl;
	querySums(a, n, q, m);
}


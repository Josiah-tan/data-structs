#include"template.h"
#include<cassert>
#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>
#include<string>

using namespace std;


std::pair<int, int> partition(vector<int>& v, int start, int end){
	int random = rand() % (end - start + 1) + start; // [start, end]
	std::swap(v[start], v[random]);
	std::pair<int, int> a = std::make_pair(start, start);
	for (int i = start + 1; i <= end; i++){
		if (v[i] == v[a.first]){
			std::swap(v[++a.second], v[i]);
		}
		else if (v[i] < v[a.first]){
			std::swap(v[a.first++], v[i]);
			std::swap(v[++a.second], v[i]);
		}
	}
	// for (int i = start; i <= end; i++){
	// 	cout << v[i] << ' ';
	// }
	// cout << endl;
	return a;
}
	
void quick_sort_3(vector<int>& v, int start, int end){
	if (start >= end){
		return;
	}
	std::pair<int, int> a = partition(v, start, end);
	quick_sort_3(v, start, a.first - 1);
	quick_sort_3(v, a.second + 1, end);
}

/*
 * @brief quick_sort quickly sorts through something
 * @param
 * v: vector containing elements
 * @returns
 * none
*/
void quick_sort_3(vector<int>& v){
	quick_sort_3(v, 0, v.size() - 1);
}

void test() {
	int N;
	cin >> N;
	vector<int>v = vector<int>(N);
	for (int i = 0; i < N; i++){
		cin >> v[i];
	}
	// std::sort(v.begin(), v.end());
	quick_sort_3(v);
	for (int i = 0; i < N; i++){
		cout << v[i] << ' ';
	}
	cout << endl;
}


void stress() {
	int T = 10000;
	for (int i = 0; i < T; i++){
		int N = 100;
		vector<int>v = vector<int>(N);
		vector<int>v1 = vector<int>(N);
		for (int i = 0; i < N; i++){
			v[i] = rand() % N;
			v1[i] = v[i];
		}
		quick_sort_3(v);
		std::sort(v1.begin(), v1.end());
		for (int i = 0; i < N; i++){
			assert(v[i] == v1[i]);
		}
	}
}


int main(void){
	// test();
	stress();
}


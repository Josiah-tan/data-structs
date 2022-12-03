#include"cassert"
#include"template.h"
#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>
#include<string>

using namespace std;

std::pair<int, vector<int>> mergeSort(vector<int>& v, int left, int right){
	vector<int>v_new;
	if (left == right){
		v_new.push_back(v[left]);
		return std::make_pair(0, v_new);
	}
	int middle = (left + right) / 2;
	std::pair<int, vector<int>> ans1 = mergeSort(v, left, middle);
	std::pair<int, vector<int>> ans2 = mergeSort(v, middle + 1, right);
	unsigned int i = 0;
	unsigned int j = 0;
	int ans = 0;
	while (i < ans1.second.size() && j < ans2.second.size()){
		if (ans1.second[i] <= ans2.second[j]){
			v_new.push_back(ans1.second[i++]);
			ans += j;
		}
		else{
			v_new.push_back(ans2.second[j++]);
		}
	}
	while (i < ans1.second.size()){
		v_new.push_back(ans1.second[i++]);
		ans += j;
	}
	while (j < ans2.second.size()){
		v_new.push_back((ans2.second[j++]));
	}
	return std::make_pair(ans1.first + ans2.first + ans, v_new);
}

int numberInversions(vector<int>& v){
	std::pair<int, vector<int>> ans = mergeSort(v, 0, v.size() - 1);
	return ans.first;
}

int numberInversionsNaive(vector<int>& v){
	int ans = 0;
	for (int i = 0; i < v.size(); i++){
		for (int j = i + 1; j < v.size(); j++){
			if (v[i] > v[j]){
				ans += 1;
			}
		}
	}
	return ans;
}

void test() {
  	int N;
  	cin >> N;
  	vector<int>v = vector<int>(N);
  	for (int i = 0; i < N; i++){
  		cin >> v[i];
  	}
  	int ans = numberInversionsNaive(v);
  	assert(ans == numberInversions(v));
  	cout << ans;
}


void stress() {
	int T = 100;
	for (int j = 0; j < T; j++){
		int N = rand() % 1000 + 1;
		vector<int>v = vector<int>(N);
		for (int i = 0; i < N; i++){
			v[i] = rand() % 100 + 1;
		}
		int ans = numberInversionsNaive(v);
		assert(ans == numberInversions(v));
	}
}


int main(void){
	// test();
	stress();
}


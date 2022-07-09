#include"template.h"
#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>
#include<string>

using namespace std;


int main(void){
	// helloWorld();
	int T, N;
	cin >> T;
	for (int t = 0; t < T;t ++){
		cin >> N;
		vector<int>v = vector<int>(N);
		for (int i = 0; i < N; i++){
			cin >> v[i];
		}
		std::sort(v.begin(), v.end());
		for (int i = 0; i < N; i++){
			cout << v[i] << ' ';
		}
		cout << endl;
	}
}


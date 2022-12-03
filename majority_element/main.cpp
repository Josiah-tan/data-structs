#include"template.h"
#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>
#include<string>

using namespace std;

int main(void){
	// helloWorld();
	int N;
	cin >> N;
	vector<int>v = vector<int>(N);
	for (int i = 0; i < N; i++){
		cin >> v[i];
	}
	sort(v.begin(), v.end());
	// for (int i = 0; i < N; i++){
	// 	cout << v[i] << endl;
	// }
	int count = 1;
	int ans = 0;
	for (int i = 1; i < N; i++){
		if (v[i] == v[i-1]){
			count += 1;
			if (count > N/2){
				ans = 1;
			}
		}
		else{
			count = 1;
		}
	}
	cout << ans;
}


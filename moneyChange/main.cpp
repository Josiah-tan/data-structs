#include"template.h"
#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>
#include<string>

using namespace std;

const int number_denomination = 3;
int denominations [number_denomination] = {1, 5, 10};

int main(void){
	int m;
	cin >> m;
	int ans = 0;
	for (int i = number_denomination - 1; i >= 0 && m != 0; i--){
		ans += m / denominations[i];
		m %= denominations[i];
	}
	cout << ans;
}


#include <memory>
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
	// int m;
	// cin >> m;
	// int ans = 0;
	// for (int i = number_denomination - 1; i >= 0 && m != 0; i--){
	// 	ans += m / denominations[i];
	// 	m %= denominations[i];
	// }
	// cout << ans;
	shared_ptr<int> hello = std::make_shared<int>(10);
	cout << "hello.use_count(); " << hello.use_count() << endl;
	cout << "hello.use_count(); " << hello.use_count() << endl;
}


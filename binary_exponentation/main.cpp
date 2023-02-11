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

int naivePower(int a, int n){
	int answer = 1;
	for (int i = 0; i < n; i++){
		answer *= a;
	}
	return answer;
}

int power(int a, int n){
	int answer = 1;
	while (n > 0){
		if (n & 1){
			answer *= a;
		}
		a *= a;
		n >>= 1;
	}
	return answer;
}

int main(void){
	assert(power(5, 5) == naivePower(5, 5));
}


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

vector<string> duval(const string &s){
	int n = s.size();
	int i = 0;
	vector<string> factorisation;
	while (i < n){
		// [i, k) → region of Lyndon strings
		// [k, j) → j - k = length of repeating block
		// stare at this:
		// 1231231230
		// ^	 ^	^
		// i     k  j
		//
		// 1231231230
		// ^    ^  ^
		// i    k  j
		int k = i, j = i + 1;
		while (j < n){
			if (s[k] > s[j]){
				break;
			}
			else if (s[k] < s[j]){
				k = i;
				j++;
			}
			else {
				k++;
				j++;
			}
		}
		while (i <= k){
			factorisation.push_back(s.substr(i, j - k));
			i += j - k;
		}
	}
	return factorisation;
}

string minCyclicString(string s){
	s += s;
	int n = s.size();
	int i = 0, answer = 0;
	while (i < n / 2){
		answer = i;
		int k = i, j = i + 1;
		while (j < n){
			if (s[k] > s[j]){
				break;
			}
			else if (s[k] < s[j]){
				k = i;
				j++;
			}
			else {
				j++;
				k++;
			}
		}
		while (i <= k){
			i += j - k;
		}
	}
	return s.substr(answer, n / 2);
}

int main(void){
	string s;
	s = "abcabad";
	vector<string> answer;
	answer = duval(s);
	assert(same(answer, {"abc", "abad"}));
	print(answer);
	s = "ba";
	answer = duval(s);
	assert(same(answer, {"b", "a"}));
	print(answer);
	s = "1231231231";
	answer = duval(s);
	assert(same(answer, {"123", "123", "123", "1"}));
	print(answer);
	s = "1231234231";
	answer = duval(s);
	assert(same(answer, {"123123423", "1"}));
	print(answer);
	assert(minCyclicString(s) == "1123123423");
	s = "123123123";
	assert(minCyclicString(s) == "123123123");
}


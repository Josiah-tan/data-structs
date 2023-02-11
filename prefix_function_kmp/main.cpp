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

vector<int> prefixKmp(string s){
	int n = s.size();
	vector<int> pi(n);
	for (int i = 1; i < n; i++){
		int j = pi[i - 1];
		while (j && s[j] != s[i]) j = pi[j - 1];
		pi[i] = j + (s[j] == s[i]);
	}
	return pi;
}

vector<vector<int>> computeAutomatonNaive(string s){
	s += "#";
	int n = s.size();
	vector<int> pi = prefixKmp(s);
	vector<vector<int>> automaton(n, vector<int>(26));
	for (int i = 0; i < n; i++){
		for (int c = 0; c < 26; c++){
			int j = i;
			while (j > 0 && 'a' + c != s[j]) j = pi[j-1];
			automaton[i][c] = j + ('a' + c == s[j]);
		}
	}
	return automaton;
}

vector<vector<int>> computeAutomaton(string s){
	s += "#";
	int n = s.size();
	vector<int> pi = prefixKmp(s);
	vector<vector<int>> automaton(n, vector<int>(26));
	for (int i = 0; i < n; i++){
		for (int c = 0; c < 26; c++){
			automaton[i][c] = (i && 'a' + c != s[i]) ? automaton[pi[i-1]][c] : i + ('a' + c == s[i]);
		}
	}
	return automaton;
}

vector<int> computeAllMatches(string pattern, string text){
	vector<vector<int>> automaton = computeAutomaton(pattern);
	vector<int> solutions;
	for (int i = 0, pointer = 0; i < text.size(); i++){
		pointer = automaton[pointer][text[i] - 'a'];
		if (pointer == pattern.size()){
			solutions.push_back(i - pattern.size() + 1);
		}
	}
	return solutions;
}

int main(void){
	vector<int> answer;
	answer = {0, 0, 0, 1, 2, 3, 0};
	same(prefixKmp("abcabcd"), answer);
	answer = {0, 1, 0, 1, 2, 2, 3};
	same(prefixKmp("aabaaab"), answer);
	same(computeAutomaton("hello world"), computeAutomatonNaive("hello world"));
	same(computeAllMatches("ab", "abcabcd"), {0, 3});
}


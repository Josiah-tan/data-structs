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
			while (j && 'a' + c != s[j]) j = pi[j - 1];
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
			automaton[i][c] = (i && 'a' + c != s[i]) ? automaton[pi[i - 1]][c] : i + ('a' + c == s[i]);
		}
	}
	return automaton;
}

vector<int> computeAllMatches(string pattern, string text){
	vector<vector<int>> automaton = computeAutomaton(pattern);
	vector<int> solutions;
	for (int i = 0, j = 0; i < text.size(); i++){
		j = automaton[j][text[i] - 'a'];
		if (j == pattern.size()){
			solutions.push_back(i - j + 1);
		}
	}
	return solutions;
}

// string generateGray(int number){
// 	string gray = "a";
// 	for (int i = 1; i < number; i++){
// 		string new_character = string(1, i + 'a');
// 		gray = gray + new_character + gray;
// 	}
// 	return gray;
// }

string generateGray(int number){
	string result = "";
	for (int i = 0; i < number; i++){
		result = result + string(1, i + 'a') + result;
	}
	return result;
}

int computeGrayMatch(string match, int k){
	// G[i][j] → start state j, processing string i, value of automaton after finish
	// K[i][j] → starting with state j, number of occurrences of s in g_i
	vector<vector<int>> automaton = computeAutomaton(match);
	vector<vector<int>> G(k + 1, vector<int>(automaton.size()));
	vector<vector<int>> K(k + 1, vector<int>(automaton.size()));
	for (int j = 0; j < automaton.size(); j++){
		K[0][j] = 0;
		G[0][j] = j;
	}
	for (int i = 1; i <= k; i++){
		for (int j = 0; j < automaton.size(); j++){
			int middle = automaton[G[i - 1][j]][i - 1];
			G[i][j] = G[i - 1][middle];
			K[i][j] = K[i - 1][j] + (middle == match.size()) + K[i - 1][middle];
		}
	}
	return K[k][0];
}

int main(void){
	vector<int> answer;
	answer = {0, 0, 0, 1, 2, 3, 0};
	same(prefixKmp("abcabcd"), answer);
	answer = {0, 1, 0, 1, 2, 2, 3};
	same(prefixKmp("aabaaab"), answer);
	same(computeAutomaton("hello world"), computeAutomatonNaive("hello world"));
	same(computeAllMatches("ab", "abcabcd"), {0, 3});
	assert(generateGray(3) == "abacaba");
	string match = "abac";
	assert(computeAllMatches(match, generateGray(4)).size() == 2);
	assert(computeAllMatches(match, generateGray(5)).size() == 4);
	assert(computeAllMatches(match, generateGray(5)).size() == computeGrayMatch(match, 5));
	assert(computeAllMatches(match, generateGray(10)).size() == computeGrayMatch(match, 10));
}

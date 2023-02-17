#include"template.h"
#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>
#include<string>
#include<cassert>
#include<numeric>
#include<map>
#include<unordered_set>
#include<stack>
#include<set>

using namespace std;
// number of states <= 2n - 1 (n >= 2)
// number of transitions <= 3n - 4 (n >= 3)
// linear time proof:
// suffix link traversal: adding transitions
// 		number of transitions linear → amortised O(1)
// copying transitions when q cloned into state clone
//      number of states linear → amortised O(1)
// changing transition to q, redirect to clone
//    	longest(link(link(last))) increases monotonically
// number of states proof:
// 		initially one state, first and second only one created, remaining n - 2 at most 2 created each:
// 		1 + 1 + 1 + 2 * (n - 2) = 2n - 1
// method 2:
//		endpos set: parent ⊇ child → degree(inner vertices) > 1 && number of leaves <= n → # vertices <= 2n - 1
//		example:
//		"abbb...bbb" → 2n - 1
// number of transitions proof:
//  	continuous transitions, consider spanning tree of 2n - 1 nodes → answer <= 2n - 2 (assuming <= 2n - 1 nodes)
//  	noncontinuous transitions, <= n - 1 because, only n non-empty suffixes of s, and can't contain s
//  	combining: 3n - 3, however 3n - 4 is possible with the test case "abbb...bbb"
int naiveNumberOfDifferentSubstrings(string s){
	unordered_set<string> unique_substrings;
	string possible_string;
	for (int i = 0; i < s.size(); i++){
		for (int j = i; j < s.size(); j++){
			possible_string = s.substr(i, j - i + 1);
			unique_substrings.insert(possible_string);
		}
	}
	return unique_substrings.size();
}
int naiveTotalLengthOfAllDifferentSubstrings(string s){
	unordered_set<string> unique_substrings;
	string possible_string;
	for (int i = 0; i < s.size(); i++){
		for (int j = i; j < s.size(); j++){
			possible_string = s.substr(i, j - i + 1);
			unique_substrings.insert(possible_string);
		}
	}
	int answer = 0;
	for (auto iterator = unique_substrings.begin(); iterator != unique_substrings.end(); iterator++){
		answer += iterator->size();
	}
	return answer;
}

string naiveLexicographicalString(string s, int k){
	set<string> ordered_substrings;
	for (int i = 0; i < s.size(); i++){
		for (int j = i; j < s.size(); j++){
			string substring = s.substr(i, j - i + 1);
			if (ordered_substrings.find(substring) == ordered_substrings.end()){
				ordered_substrings.insert(substring);
			}
		}
	}
	// cout << "size:" << ordered_substrings.size() << endl;
	int counter = 0;
	for (const auto& ordered_substring: ordered_substrings){
		if (counter == k){
			return ordered_substring;
		}
		counter++;
	}
	return "";
}

class SuffixAutomaton{
	private:
		struct State {
			// len → longest
			// link → next endpos set ⊇ current endpos set
			int len, link;
			map<char, int> next;
		};
		vector<State> states;
		int max_size;
		int size;
		int last;
		int pointer;
	public:
		SuffixAutomaton(int max_size): max_size(max_size){
			states.resize(max_size * 2);
			states[0].len = 0;
			states[0].link = -1;
			size = 1;
			last = 0;
		}
		void extend(char c){
			int cur = size++;
			states[cur].len = states[last].len + 1;
			int p = last;
			while (p != -1 && !states[p].next.count(c)){
				states[p].next[c] = cur;
				p = states[p].link;
			}
			if (p == -1){
				states[cur].link = 0;
			}
			else {
				int q = states[p].next[c];
				if (states[p].len + 1 == states[q].len){
					//minlen(last) = len(p) + 1 → minlen(cur) = len(q) + 1
					states[cur].link = q;
				}
				else {
					int clone = size++;
					// make everything pointing to/from q point to clone
					// q contains longer substrings than clone
					// therefore, clone contains more endpos classes
					states[clone].len = states[p].len + 1;
					states[clone].next = states[q].next;
					states[clone].link = states[q].link;
					while (p != -1 && states[p].next[c] == q){
						states[p].next[c] = clone;
						p = states[p].link;
					}
					states[q].link = states[cur].link = clone;
				}
			}
			last = cur;
		}
		void extend(string s){
			for (const char &c: s){
				extend(c);
			}
		}
		int longestPrefix(string pattern){
			int state = 0;
			int counter = 0;
			for (const char& c: pattern){
				if (states[state].next.count(c)){
					state = states[state].next[c];
					counter++;
				}
			}
			return counter;
		}
		int recurseNumberOnumberOfDifferentSubstrings(int state){
			if (state >= size){
				return 0;
			}
			int number_ways = 1;
			for (const auto& [key, value]: states[state].next){
				number_ways += recurseNumberOnumberOfDifferentSubstrings(value);
			}
			return number_ways;
		}
		vector<int> numberWays(){
			// using dfs but in a loop mwah hah hah
			vector<int> number_ways(size, 1);
			stack<pair<int, map<char, int>::iterator>> dfs;
			vector<bool> visited(size, 0);
			dfs.push({0, states[0].next.begin()});
			visited[0] = true;
			while (dfs.size()){
				pair<int, map<char, int>::iterator> top = dfs.top();
				int state = top.first;
				map<char, int>::iterator iterator = top.second;
				dfs.pop();
				if (iterator != states[state].next.end()){
					dfs.push({state, next(iterator)});
					while (iterator != states[state].next.end()){
						if (!visited[iterator->second]){
							visited[iterator->second] = true;
							dfs.push({iterator->second, states[iterator->second].next.begin()});
						}
						iterator++;
					}
				}
				else {
					for (const auto &[key, value]: states[state].next){
						number_ways[state] += number_ways[value];
					}
				}
			}
			return number_ways;
		}
		int numberOfDifferentSubstrings(){
			vector<int> number_ways = numberWays();
			assert(number_ways[0] - 1 == recurseNumberOnumberOfDifferentSubstrings(0) - 1);
			return number_ways[0] - 1;
		}
		int totalLengthOfAllDifferentSubstrings(){
			vector<int> number_ways(size, 1);
			// answer[leaf_node] = 0 // from leaf state there is no path hence no string.
			// answer[state] = for each child add a transition character to it to make a new string, hence answer[child] + number_ways[child]
			// answer[state] = length of substrings that follow a path from state
			vector<int> answer(size, 0);
			stack<pair<int, map<char, int>::iterator>> dfs;
			vector<bool> visited(size, 0);
			dfs.push({0, states[0].next.begin()});
			visited[0] = true;
			while (dfs.size()){
				pair<int, map<char, int>::iterator> top = dfs.top();
				int state = top.first;
				map<char, int>::iterator iterator = top.second;
				dfs.pop();
				if (iterator != states[state].next.end()){
					dfs.push({state, next(iterator)});
					while (iterator != states[state].next.end()){
						if (!visited[iterator->second]){
							visited[iterator->second] = true;
							dfs.push({iterator->second, states[iterator->second].next.begin()});
						}
						iterator++;
					}
				}
				else {
					for (const auto &[key, value]: states[state].next){
						number_ways[state] += number_ways[value];
						answer[state] += answer[value] + number_ways[value];
					}
				}
			}
			return answer[0];
		}
		string lexicographicalString(int k){
			vector<int> number_ways = numberWays();
			int state = 0;
			k++;
			string s = "";
			while (k){
				for (const auto &[character, next]: states[state].next){
					if (k > number_ways[next]){
						k -= number_ways[next];
					}
					else {
						s += character;
						k--;
						state = next;
						break;
					}
				}
			}
			return s;
		}
};




int main(void){
	SuffixAutomaton suffix_automaton(100);
	suffix_automaton.extend("abcbc");
	assert(suffix_automaton.longestPrefix("bcba") == 3);
	assert(suffix_automaton.longestPrefix("bca") == 2);
	int answer = naiveNumberOfDifferentSubstrings("abcbc");
	assert(suffix_automaton.numberOfDifferentSubstrings() == naiveNumberOfDifferentSubstrings("abcbc"));
	SuffixAutomaton suffix_automaton_2(100);
	suffix_automaton_2.extend("abcb");
	assert(suffix_automaton_2.numberOfDifferentSubstrings() == 9);
	assert(suffix_automaton_2.totalLengthOfAllDifferentSubstrings() == naiveTotalLengthOfAllDifferentSubstrings("abcb"));
	assert(suffix_automaton.totalLengthOfAllDifferentSubstrings() == naiveTotalLengthOfAllDifferentSubstrings("abcbc"));
	// lexicographically kth string
	for (int i = 0; i < 9; i++){
		assert(suffix_automaton_2.lexicographicalString(i) == naiveLexicographicalString("abcb", i));
	}
	for (int i = 0; i < 12; i++){
		assert(suffix_automaton.lexicographicalString(i) == naiveLexicographicalString("abcbc", i));
	}
	// smallest cyclic shift
}


#include"template.h"
#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>
#include<string>
#include<cassert>
#include<numeric>
#include<queue>
#include<cassert>

using namespace std;

vector<int> sortCyclicShifts(const string &s){
	int n = s.size();
	const int alphabet = 256;
	// c[i] = class for s[i], lowest character gets lower class
	// p[i] = location of ith sorted character in original string
	vector<int> p(n), c(n), cnt(max(alphabet, n), 0);
	for (int i = 0; i < n; i++)
		cnt[s[i]]++;
	for (int i = 1; i < alphabet; i++)
		cnt[i] += cnt[i - 1];
	for (int i = 0; i < n; i++)
		p[--cnt[s[i]]] = i;
	c[p[0]] = 0;
	int classes = 1; // current number of classes
	for (int i = 1; i < n; i++){
		if (s[p[i]] != s[p[i - 1]])
			classes++;
		c[p[i]] = classes - 1;
	}
	vector<int> pn(n), cn(n);
	for (int h = 0; (1 << h) < n; h++){
		// using principle of radix sort, sort by second element first
		// pn[i] points to the location of ith string s[pn[i], pn[i] + (1 << (h + 1))]
		for (int i = 0; i < n; i++){
			pn[i] = p[i] - (1 << h);
			if (pn[i] < 0)
				pn[i] += n;
		}
		// sorting by first element
		fill(cnt.begin(), cnt.begin() + classes, 0);
		for (int i = 0; i < n; i++)
			cnt[c[pn[i]]]++;
		for (int i = 1; i < classes; i++)			
			cnt[i] += cnt[i - 1];
		// reverse because same class for first element but not for the second
		// remember, second is already sorted
		for (int i = n - 1; i >= 0; i--)
			p[--cnt[c[pn[i]]]] = pn[i];
		cn[p[0]] = 0;
		classes = 1;
		for (int i = 1; i < n; i++){
			pair<int, int> cur = {c[p[i]], c[(p[i] + (1 << h)) % n]};
			pair<int, int> prev = {c[p[i - 1]], c[(p[i - 1] + (1 << h)) % n]};
			if (cur != prev)
				++classes;
			cn[p[i]] = classes - 1;
		}
		c.swap(cn);
	}
	return p;
}

vector<int> suffixArrayConstruction(string s){
	// $ has the lowest lexicographical order
	s += "$";
	vector<int> sorted_shifts = sortCyclicShifts(s);
	// remove the first one ($s)
	sorted_shifts.erase(sorted_shifts.begin());
	return sorted_shifts;
}

int main(void){
	string s = "dabbb";
	same(suffixArrayConstruction(s), {1, 4, 3, 2, 0});
	s = "aaba";
	same(suffixArrayConstruction(s), {3, 0, 1, 2});
}


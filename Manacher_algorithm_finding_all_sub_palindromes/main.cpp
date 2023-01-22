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

template<class T>
bool same(vector<T> question, vector<T> answer){
	int question_size = question.size(), answer_size = answer.size();
	bool same = question_size == answer_size;
	for (int i = 0; i < min(question_size, answer_size); i++)
	{
		same &= question[i] == answer[i];
	}
	if (!same){
		cout << "Q: ";
		for (int i = 0; i < question_size; i++)
		{
			cout << question[i] << ' ';
		}
		cout << "\nA: ";
		for (int i = 0; i < answer_size; i++)
		{
			cout << answer[i] << ' ';
		}
		cout << endl;
	}
	return same;
}

vector<int> Manacher_odd(string s){
	int n = s.size();
	s = "$" + s + "^";
	vector<int> p(n + 2);
	int l = 1, r = 1;
	for (int i = 1; i <= n; i++)
	{
		p[i] = i > r ? 0 : min(r - i, p[l + (r - i)]);
		while (s[i + p[i]] == s[i - p[i]]){
			p[i]++;
		}
		if (p[i] + i > r){
			r = p[i] + i, l = i - p[i];
		}
	}
	return vector<int>(begin(p) + 1, end(p) - 1);
}

vector<int> Manacher(string s){
	string t;
	for (const char c: s){
		t += string("#") + c;
	}
	vector<int> intermediate = Manacher_odd(t + "#");
	return intermediate;
}

int main(void){
	assert(same(Manacher_odd("abcba"), {1, 1, 3, 1, 1}));

}


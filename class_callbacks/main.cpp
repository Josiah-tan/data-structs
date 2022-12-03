#include"template.h"
#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>
#include<string>

using namespace std;

class Hello
{
	private:
		vector<int> &a;
	public:

		Hello(vector<int> &a): a(a) {}

		static void Spanish(vector<int>& a, int b){
			cout << "Spanish" << endl;
			for (unsigned int i = 0; i < a.size(); i++){
				cout << a[i] << " ";
			}
			cout << b << endl;
		}

		static void English(vector<int>& a, int b){
			cout << "English" << endl;
			for (unsigned int i = 0; i < a.size(); i++){
				cout << a[i] << " ";
			}
			cout << b << endl;
		}
};

void print(void (*language) (vector<int>&, int), vector<int>& a, int b){
	language(a, b);
}

void print(vector<int>& a, int b){
	print(Hello::English, a, b);
}

int main(void){
	vector<int> a(5, 1);
	// Hello hello(a);
	vector<void (*) (vector<int>&, int)> languages = {Hello::English, Hello::Spanish};
	for (unsigned int i = 0; i < languages.size(); i++){
		print(languages[i], a, 8);
	}
	// print(Hello::English, a, 7);
	// print(Hello::Spanish, a, 5);
}


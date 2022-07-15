#include <algorithm>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;

bool compare(const string& s1, const string& s2){
	for (u_int i = 0; i < std::min(s1.size(), s2.size()); i++){
		if (s1[i] < s2[i]){
			return true;
		}
		else if (s1[i] > s2[i]){
			return false;
		}
	}
	return s1.length() > s2.length();
}

string largest_number(vector<string> a) {
	std::sort(a.begin(), a.end(), compare);
	string ans = "";
	for (u_int i = 0; i < a.size(); i++){
		ans += a[a.size() - i - 1];
	}
	return ans;
}

int main() {
  int n;
  std::cin >> n;
  vector<string> a(n);
  for (size_t i = 0; i < a.size(); i++) {
    std::cin >> a[i];
  }
  std::cout << largest_number(a);
}

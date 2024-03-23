#include <stdio.h>
#define FOO 0x0010

int first_var;
int* second_var;
void procedure(int input) {
	if (input >= 42) {
		first_var = first_var +10;
		procedure(first_var);
	}
}

int main() {
	first_var = 0;
	second_var = (int*) FOO;
	procedure(*second_var);
	printf("%d", first_var);
}

int maxElement(int n, int maxSum, int k){
	int above = maxSum;
	int below = 1;
	int sm = 0;
	int ans = 0;
	while (above >= below){
		int m = (above + below) / 2;
		sm = m;
		if (k - (m - 1) < 0){
			sm += k * (m - 1 + m - k) / 2;
		}
		else {
			sm += k - (m - 1) + (m-1) * m / 2;
		}
		if (k + (m - 1) >= n){
			sm += (n - k - 1) * (m - 1 + m - 1 - (n - k - 2)) / 2;
		}
		else {
			sm += (m - 1) * m / 2 + n - (k + m - 1) - 1;
		}
		if (sm > maxSum){
			above = m - 1;
		}
		else if (sm <= maxSum){
			ans = max(ans, m);
			below = m + 1;
		}
	}
	return ans;
}

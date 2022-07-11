#include<cassert>
#include"template.h"
#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>
#include<string>

using namespace std;


class Greedy{
	/* only works for D = 2 */
	private:
		vector<int>v;
		int N;
		int D;
	public:
		Greedy(vector<int>v, int N, int D): v(v), N(N), D(D) {}
		int state(int i, int k){
			assert (i < N);
			return (v[i] - k + D) % D;
		}
		int minimum(int d){
			return min(d, D - d);
		}
		int solve(int i, int j, int k){
			int vi = minimum(state(i, k));
			int vj = minimum(state(j, k));
			if (i >= j){
				return vj;
			}
			else if (vi == 0 && vj == 0){
				return solve(i + 1, j - 1, k);
			}
			else if (vi == 0 && vj == 1){
				return solve(i + 1, j, k);
			}
			else if (vi == 1 && vj == 0){
				return solve(i, j - 1, k);
			}
			else {
				return 1 + solve(i + 1, j - 1, k + 1);
			}
		}
		int solve(){
			return solve(0, N-1, 0);
		}
};



int main(void){
	// helloWorld();
	int T, N, D;
	cin >> T;
	for (int t = 1; t <= T;t ++){
		cin >> N >> D;
		vector<int>v = vector<int>(N);
		for (int i = 0; i < N; i++){
			cin >> v[i];
		}
		cout << "Case #" << t << ": " << Greedy(v, N, D).solve() << endl;
	}
}


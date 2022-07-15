#include <climits>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
using std::max;
using std::endl;

int compute_min_refills(int dist, int tank, vector<int> & stops) {
	int ans = 0;
	int last_stop = 0;
	int n = stops.size();
	// int current_tank = tank;
	// for (int i = 0; i < n; i++){
	// 	if (current_tank >= dist){
	// 		return ans;
	// 	}
	// 	if (current_tank < stops[i]){
	// 		if (current_tank == tank){
	// 			return -1;
	// 		}
	// 		else{
	// 			ans += 1;
	// 			current_tank = tank;
	// 		}
	// 	}
	// 	else {
	// 		current_tank -= stops[i] - last_stop;
	// 	}
	// }
	
	// for (int i = 0; i < n; i++){
	// 	if (dist - last_stop <= tank){
	// 		return ans;
	// 	}
	// 	if (stops[i] - last_stop > tank){
	// 		return -1;
	// 	}
	// 	while (i < n){
	// 		if (stops[i] - last_stop <= tank){
	// 			i += 1;
	// 		}
	// 		else{
	// 			last_stop = stops[--i];
	// 			ans += 1;
	// 			break;
	// 		}
	// 	}
		
	int i = 0;
	while (i < n){
		// assume here that last_stop means just refilled
		if (dist - last_stop <= tank){
			return ans;
		}
		if (stops[i] - last_stop > tank){
			return -1;
		}
		// while (i <= n){
		// 	if (i == n){
		// 		return ans + ((dist - last_stop) > tank);
		// 	}
		// 	if (stops[i] - last_stop <= tank){
		// 		i++;
		// 	}
		// 	else {
		// 		ans += 1;
		// 		last_stop = stops[i - 1];
		// 		break;
		// 	}
		// }
		if (i == n-1){
			if (stops[n-1] + tank < dist){
				return -1;
			}
		}
		if ((stops[i] - last_stop <= tank && i == n-1) || (i + 1 < n && stops[i + 1] - last_stop > tank)){
			ans += 1;
			last_stop = stops[i];
		}
		i ++;
	}
	return ans;
}

int refills(int location, vector<int>& stops, int tank, int dist){
	if (location + tank >= dist){
		return 0;
	}
	if (stops.empty() or (stops[0] - location) > tank){
		return INT_MIN;
	}
	int lastStop = location;
	while (!stops.empty() && (stops[0] - location) <= tank){
		lastStop = stops[0];
		stops.erase(stops.begin());
	}
	return 1 + refills(lastStop, stops, tank, dist);
}
int solution_given(int dist, int tank, vector<int> & stops) {
	int ans = refills(0, stops, tank, dist);
	if (ans < 0){
		return -1;
	}
	return ans;
}



int main() {
    // int d = 0;
    // cin >> d;
    // int m = 0;
    // cin >> m;
    // int n = 0;
    // cin >> n;
    //
    // vector<int> stops(n);
    // for (int i = 0; i < n; ++i)
    //     cin >> stops.at(i);
    //
    // /* cout << compute_min_refills(d, m, stops) << "\n"; */
    // cout << solution_given(d, m, stops) << "\n";

		while (true){
			int d = rand() % 1000 + 1;//% 10000 + 1;
			int m = rand() % 400 + 1;
			int n = rand() % 4 + 1; //% 300 + 1;
			cout << "d " << d << endl;
			cout << "m " << m << endl;
			cout << "n " << n << endl;
			vector<int>stops(n);
			
			for (int i = 0; i < n; ++i){
				stops[i] = (i ? stops[i-1] : 0) + (rand() % ((d-1)/n) + 1);
			}
			for (int i = 0; i < n; ++i){
				cout << "stops[i] " << stops[i] << endl;
			}
			int test = compute_min_refills(d, m, stops);
			int solution = solution_given(d, m, stops);
			cout << "solution " << solution << endl;
			cout << "test " << test << endl;
			if (solution != test){
				break;
			}
		}
		return 0;
}

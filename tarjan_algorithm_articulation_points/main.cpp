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

class TarjanAlgorithm{
	private:
		vector<int> low;
		vector<int> discovery;
		vector<int> articulation_points;
		int time;
		vector<vector<int>> _adjacency;
	public:
		int dfsArticulationPoints(int node, int parent){
			int children = 0;
			low[node] = discovery[node] = ++time;
			for (int next: _adjacency[node]){
				if (next == parent) continue;
				if (!discovery[next]){
					children++;
					dfsArticulationPoints(next, node);
					if (discovery[node] <= low[next] && parent != -1){
						articulation_points.push_back(node);
					}
					low[node] = min(low[node], low[next]);
				}
				else {
					low[node] = min(low[node], discovery[next]);
				}
			}
			return children;
		}
		vector<int> articulationPoints(vector<vector<int>>& adjacency){
			_adjacency = adjacency;
			low = discovery = vector<int>(adjacency.size(), 0);
			articulation_points = vector<int>(0);
			time = 0;
			for (int i = 0; i < adjacency.size(); i++)
			{
				if (!discovery[i]){
					int children = dfsArticulationPoints(i, -1);
					if (children > 1){
						articulation_points.push_back(i);
					}
				}
			}
			return articulation_points;
		}
};

int main(void){
	TarjanAlgorithm tarjan_algorithm;
	vector<vector<int>> adjacency;
	adjacency = {{1, 2}, {0, 2}, {0, 1}};
	same(tarjan_algorithm.articulationPoints(adjacency), {});
	adjacency = {{1}, {0, 2, 3}, {1, 3}, {1, 2}};
	same(tarjan_algorithm.articulationPoints(adjacency), {1});
	adjacency = {{1, 4, 5}, {0, 2, 3}, {1, 3}, {1, 2}, {0, 5}, {0, 4}};
	same(tarjan_algorithm.articulationPoints(adjacency), {1, 0});
	adjacency = {{1, 4, 5}, {0, 2, 3}, {1, 3}, {1, 2}, {0, 5}, {0, 4}};
}


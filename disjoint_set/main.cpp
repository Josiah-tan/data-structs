#include"template.h"
#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>
#include<string>
#include<cassert>
#include<numeric>
#include<queue>

#include<boost/pending/disjoint_sets.hpp>

using namespace std;

class DisjointSet{
	private:
		int size;
		vector<int> rank;
		vector<int> parent;
	public:
		DisjointSet(int size): size(size), rank(size, 0), parent(size){
			iota(parent.begin(), parent.end(), 0); // increment from left to right
		}
		int find(int element){
			if (parent[element] != element){
				parent[element] = find(parent[element]);
			}
			return parent[element];
		}
		void perform_union(int first, int second){
			int parent_first = find(first);
			int parent_second = find(second);
			
			if (parent_first == parent_second){
				return;
			}

			if (rank[parent_first] < rank[parent_second]){
				parent[parent_first] = parent_second;
			}
			else if (rank[parent_first] > rank[parent_second]){
				parent[parent_second] = parent_first;
			}
			else {
				parent[parent_first] = parent_second;
				rank[parent_second]++;
			}
		}
};

int main(void){
	vector<int> rank(100);
	vector<int> parent(100);
	iota(parent.begin(), parent.end(), 0); // elements increment by one
	boost::disjoint_sets<int*, int*> disjoint(&rank[0], &parent[0]);

	DisjointSet disjoint_set(100);
	
	disjoint.union_set(1, 2);
	disjoint.union_set(1, 3);
	disjoint.union_set(1, 4);

	disjoint_set.perform_union(1, 2);
	disjoint_set.perform_union(1, 3);
	disjoint_set.perform_union(1, 4);
	
	assert((disjoint.find_set(1) != disjoint.find_set(5)) == (disjoint_set.find(1) != disjoint.find_set(5)));
	assert((disjoint.find_set(2) != disjoint.find_set(4)) == (disjoint_set.find(2) != disjoint.find_set(4)));
}


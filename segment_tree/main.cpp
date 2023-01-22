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

// nodes in heap-like order (1 indexed)
// node contains [left_segment, right_segment] (result of operation over that region)
class SegmentTreeNaive{
	private:
		vector<int> array;
		vector<int> tree;
		int size;
		int (*function)(int, int);
	public:
		SegmentTreeNaive(vector<int>& array, int(function)(int, int)): array(array), function(function){
			size = array.size();
			tree = vector<int>(size * 4);
			build(1, 0, size - 1);
		}
		void build(int node, int left_segment, int right_segment){
			if (left_segment == right_segment){
				tree[node] = array[left_segment];
			}
			else{
				int left_node = node * 2;
				int right_node = node * 2 + 1;
				int middle_segment = (left_segment + right_segment) / 2;
				build(left_node, left_segment, middle_segment);
				build(right_node, middle_segment + 1, right_segment);
				tree[node] = function(tree[left_node], tree[right_node]);
			}
			std::cout << "node = " << node << std::endl;
			std::cout << "tree[node] = " << tree[node] << std::endl;
		}
		int query(int left, int right){
			return query(1, 0, size - 1, left, right);
		}
		int query(int node, int segment_left, int segment_right, int left, int right){
			if (left > right){
				return 0;
			}
			if (segment_left == left && segment_right == right){
				return tree[node];
			}
			else {
				int node_left = node * 2;
				int node_right = node * 2 + 1;
				int segment_middle = (segment_left + segment_right) / 2;
				return function(
						query(node_left, segment_left, segment_middle, left, min(right, segment_middle)),
						query(node_right, segment_middle + 1, segment_right, max(left, segment_middle + 1), right)
						);
			}
		}
		void update(int position, int value){
			update(1, 0, size - 1, position, value);
		}
		void update(int node, int segment_left, int segment_right, int position, int value){
			if (segment_left == segment_right){
				tree[node] = value;
			}
			else {
				int left_node = 2 * node;
				int right_node = 2 * node + 1;
				int segment_middle = (segment_left + segment_right) / 2;
				if (position <= segment_middle){
					update(left_node, segment_left, segment_middle, position, value);
				}
				else {
					update(right_node, segment_middle + 1, segment_right, position, value);
				}
				tree[node] = function(tree[left_node], tree[right_node]);
			}
		}
};

// O(2N) memory rather than O(4N) memory
// use Euler tour traversal (preorder traversal)
// for current node, segment [left, right], size = right - left + 1
// number elements = 2 * size - 1
// given left node represent segment [left, middle] → size = right - left + 1
// right node = current node + (2 * (middle - left + 1)) - 1 + 1 = current node + (2 * (middle - left + 1))

class SegmentTree{
	private:
		vector<int>& array;
		int(*function)(int, int);
		int size;
		vector<int> tree;
	public:
		SegmentTree(vector<int>& array, int (*function)(int, int)): array(array), function(function){
			size = array.size();
			tree = vector<int>(size * 2);
			build(1, 0, size - 1);
		}
		void build(int node, int segment_left, int segment_right){
			if (segment_left == segment_right){
				tree[node] = array[segment_left];
			}
			else {
				int segment_middle = (segment_left + segment_right) / 2;
				int left_node = node + 1;
				int right_node = node + 2 * (segment_middle - segment_left + 1);
				build(left_node, segment_left, segment_middle);
				build(right_node, segment_middle + 1, segment_right);
				tree[node] = function(tree[left_node], tree[right_node]);
			}
		}
		int query(int left, int right){
			return	query(1, 0, size - 1, left, right);
		}
		int query(int node, int segment_left, int segment_right, int left, int right){
			if (left > right){
				return 0;
			}
			else if (segment_left == left && segment_right == right){
				return tree[node];
			}
			else {
				int segment_middle = (segment_left + segment_right) / 2;
				int left_node = node + 1;
				int right_node = node + 2 * (segment_middle - segment_left + 1);
				return function(
						query(left_node, segment_left, segment_middle, left, min(segment_middle, right)),
						query(right_node, segment_middle + 1, segment_right, max(segment_middle + 1, left), right)
						);
			}
		}
		void update(int position, int value){
			update(1, 0, size - 1, position, value);
		}
		void update(int node, int segment_left, int segment_right, int position, int value){
			if (segment_left == segment_right){
				tree[node] = value;
			}
			else {
				int segment_middle = (segment_left + segment_right) / 2;
				int left_node = node + 1;
				int right_node = node + 2 * (segment_middle - segment_left + 1);
				if (position <= segment_middle){
					update(left_node, segment_left, segment_middle, position, value);
				}
				else{
					update(right_node, segment_middle + 1, segment_right, position, value);
				}
				tree[node] = function(tree[left_node], tree[right_node]);
			}
		}
};

int main(void){
	vector<int> array;
	array = {1, 2, 3, 4};
	SegmentTree segment_tree = SegmentTree(array, [](int a, int b){return a + b;});
	assert(segment_tree.query(1, 2) == 5);
	assert(segment_tree.query(1, 3) == 9);
	segment_tree.update(2, 5);
	assert(segment_tree.query(1, 2) == 7);
	assert(segment_tree.query(1, 3) == 11);
}


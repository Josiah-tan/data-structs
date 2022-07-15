#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>

using std::vector;

struct Segment {
  int start, end;
};

struct less_than_key {
	inline bool operator() (const Segment& a, const Segment& b){
		return (a.end < b.end);
	}
};

vector<int> optimal_points(vector<Segment> &segments) {
  vector<int> points;
	// probably just sort by the endpoints of the segments
	std::sort(segments.begin(), segments.end(), less_than_key());

	points.push_back(segments[0].end);
	for (u_long i = 0; i < segments.size(); i++){
		if (!(segments[i].start <= points[points.size() - 1]
				&& segments[i].end >= points[points.size() - 1]
				)){
			points.push_back(segments[i].end);
		}
	}
  return points;
}

int main() {
  int n;
  std::cin >> n;
  vector<Segment> segments(n);
  for (size_t i = 0; i < segments.size(); ++i) {
    std::cin >> segments[i].start >> segments[i].end;
  }
  vector<int> points = optimal_points(segments);
  std::cout << points.size() << "\n";
  for (size_t i = 0; i < points.size(); ++i) {
    std::cout << points[i] << " ";
  }
}

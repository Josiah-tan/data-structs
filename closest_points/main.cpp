#include"solution.h"
#include<cassert>
#include <cstdint>
#include <cstdlib>
#include<math.h>
#include<climits>
#include<limits>
#include"template.h"
#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>
#include<string>

using namespace std;

struct Point{
		int x;
		int y;
		Point(void){}
		Point(int x, int y): x(x), y(y){}
};

float EuclideanDistance(Point a, Point b){
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

float closestDistanceNaive(vector<Point>& points){
	unsigned int size = points.size();
	assert(size > 1);
	float ans = numeric_limits<float>::max();
	for (unsigned int i = 0; i < size - 1; i++){
		for (unsigned int j = i + 1; j < size; j++){
			ans = min(ans, EuclideanDistance(points[i], points[j]));
		}
	}
	return ans;
}


bool lessX(Point& a, Point& b){
	 return a.x == b.x ? a.y < b.y : a.x < b.x;
}

bool lessY(Point& a, Point& b){
	return a.y == b.y ? a.x < b.x : a.y < b.y;
}

float stripClosest(vector<Point> strip, float distance){
	float minimum = distance;
	for (unsigned int i = 0; i < strip.size() - 1; i++){
		for (unsigned int j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) < minimum; j++){
			minimum = min(minimum, EuclideanDistance(strip[i], strip[j]));
		}
	}
	return minimum;
}

float closestDistanceRecursive(
		vector<Point>& x_points, vector<Point>& y_points, unsigned int size){
	if (size <= 3){
		return closestDistanceNaive(x_points);
	}

	unsigned int middle_index = size / 2;
	vector<Point> x_left_points;
	vector<Point> x_right_points;
	vector<Point> y_left_points;
	vector<Point> y_right_points;

	for (unsigned int i = 0; i < size; i++){
		if ((y_points[i].x < x_points[middle_index].x || 
				(y_points[i].x == x_points[middle_index].x &&
				 y_points[i].y < x_points[middle_index].y)) &&
				y_left_points.size() < middle_index){
			y_left_points.push_back(y_points[i]);
		}
		else{
			y_right_points.push_back(y_points[i]);
		}
		if (i < middle_index){
			x_left_points.push_back(x_points[i]);
		}
		else{
			x_right_points.push_back(x_points[i]);
		}
	}
	float ans_left = closestDistanceRecursive(x_left_points, y_left_points, middle_index);
	float ans_right = closestDistanceRecursive(x_right_points, y_right_points, size - middle_index);
	// float distance = closestDistanceRecursive(points[0:size/2], points[size/2 + 1])
	float distance = min(ans_left, ans_right);

	vector<Point> strip;
	for (unsigned int i = 0; i < size; i++){
		if (abs(y_points[i].x - x_points[middle_index].x) < distance){
			strip.push_back(y_points[i]);
		}
	}
	return stripClosest(strip, distance);
}

float closestDistance(vector<Point>& points){
	vector<Point> x_points;
	vector<Point> y_points;
	for (unsigned int i = 0; i < points.size(); i++){
		x_points.push_back(points[i]);
		y_points.push_back(points[i]);
	}

	sort(x_points.begin(), x_points.end(), lessX);
	sort(y_points.begin(), y_points.end(), lessY);
	return closestDistanceRecursive(x_points, y_points, points.size());
	// pair<vector<pair<int, int>>, vector<pair<int, int>> split = splitHalfX(points);
	// return min(closestDistance(split.first), closestDistance(split.second));
	// return 5.0;
}

void mySolutionTest() {
	unsigned int N;
	cin >> N;
	vector<Point> points(N);
	for (unsigned int i = 0; i < N; i++){
		cin >> points[i].x >> points[i].y;
	}
	float ans = closestDistance(points);
	// ans = closestDistanceNaive(points);
	printf("%.3f", ans);
}

void geekSolutionTest() {
	unsigned int N;
	cin >> N;
	Point2D *points = (Point2D*) malloc(sizeof(Point2D) * N);
	for (unsigned int i = 0; i < N; i++){
		cin >> points[i].x >> points[i].y;
	}
	float ans = closest(points, N);
	// ans = closestDistanceNaive(points);
	printf("%.3f", ans);
	free(points);
}

int main(void){
	// mySolutionTest();
	geekSolutionTest();
}


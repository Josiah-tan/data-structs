#include<iostream>
#include"template.h"

using namespace std;

void helloWorld(void){
	cout << "hello world\n";
}

class Point {
	public:
		int y, x;
		Point(int y, int x) : y(y), x(x) {}
		Point operator+(Point other) {
			return Point(this->y + other.y, this->x + other.x);
		}
		Point operator-(Point other) {
			return Point(this->y - other.y, this->x - other.x);
		}
		friend std::ostream &operator<<(std::ostream &os, const Point &m) { 
			return os << "(" << m.y << ", " << m.x << ")";
		}
};

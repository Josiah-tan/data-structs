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

class Hilbert{
	private:
		int n;
	public:
		Hilbert(){}
		Hilbert(int n): n(n){
			// n must be square number
		}
	int coordinateToDistance(int y, int x){
		int region_x, region_y, length, distance = 0;
		for (length = n >> 1; length > 0; length >>= 1){
			region_x = (x & length) > 0;
			region_y = (y & length) > 0;
			distance += length * length * ((3 * region_x) ^ region_y);
			rotate(n, y, x, region_y, region_x);
		}
		std::cout << "distance = " << distance << std::endl;
		return distance;
	}
	void distanceToCoordinate(int distance, int &y, int &x){
		int region_x, region_y, length;
		x = y = 0;
		for (length = 1; length < n; length <<= 1){
			region_x = 1 & (distance >> 1);
			region_y = 1 & (distance ^ region_x);
			rotate(length, y, x, region_y, region_x);
			x += length * region_x;
			y += length * region_y;
			distance >>= 2;
		}
		std::cout << "y = " << y << std::endl;
		std::cout << "x = " << x << std::endl;
	}
	void rotate(int size, int &y, int &x, int region_y, int region_x){
		if (region_y == 0){
			if (region_x == 1){
				x = size - 1 - x;
				y = size - 1 - y;
			}
			swap(x, y);
		}
	}
};
//rotate/flip a quadrant appropriately
void rot(int size, int *x, int *y, int rx, int ry) {
    if (ry == 0) {
        if (rx == 1) {
            *x = size-1 - *x;
            *y = size-1 - *y;
        }

        //Swap x and y
        int t  = *x;
        *x = *y;
        *y = t;
    }
}


//convert (x,y) to d
int xy2d (int n, int x, int y) {
    int rx, ry, s, d=0;
    for (s=n/2; s>0; s/=2) {
        rx = (x & s) > 0;
        ry = (y & s) > 0;
        d += s * s * ((3 * rx) ^ ry);
        rot(n, &x, &y, rx, ry);
    }
    return d;
}

//convert d to (x,y)
void d2xy(int n, int distance, int *x, int *y) {
    int region_x, region_y, length; 
    *x = *y = 0;
    for (length=1; length<n; length <<= 1) {
        region_x = 1 & (distance >> 1);
        region_y = 1 & (distance ^ region_x);
        rot(length, x, y, region_x, region_y);
        *x += length * region_x;
        *y += length * region_y;
		distance >>= 2;
    }
}


int main(void){
	Hilbert h;
	h = Hilbert(2);
	assert(h.coordinateToDistance(0, 0) == 0);
	assert(h.coordinateToDistance(0, 1) == 3);
	h = Hilbert(8);
	assert(h.coordinateToDistance(7, 7) == 42);
	// int x, y;
	// int distance = xy2d(8, 7, 5);
	// d2xy(8, distance, &x, &y);
	// assert (x == 7 && y == 5);

	
	int distance = h.coordinateToDistance(5, 7);
	int x, y;
	h.distanceToCoordinate(distance, y, x);
	assert(y == 5 && x == 7);
}


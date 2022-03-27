#ifndef _POINT_H_
#define _POINT_H_

#include <iostream>
#include "io_utilities.h"

class Point {
	int x = 1, y = 1;
public:
	Point() {};
	Point(int _x, int _y) :x(_x), y(_y) {};
	int getx() const{ return x; }
	int gety() const{ return y; }
	void setPoint(Point p) { x = p.getx(); y = p.gety(); }
	void draw(char ch) const;
	void move(Direction direction, int rows, int cols);
	Point reverse();
};
struct Node {
	Point pt;
	int dist;
};

#endif
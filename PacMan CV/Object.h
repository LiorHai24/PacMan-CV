#pragma once
#include "Color.h"
#include "Point.h"
#include "Board.h"

class Object {
	protected:
	Point bodyLocation;
	char body;
	Direction dir;
	Color color;
public:
	virtual bool checkLegal(const Board& b);
	void setLocation(Point p) { bodyLocation = p; }
	void draw()const;
	Point getLocation() const { return bodyLocation; }
	virtual void move(int rows, int cols, bool NoColor) = 0;
	void setFigure(char c);
	void setColor(Color c) { color = c; }
	char getbody() { return body; }
	Color getColor() { return color; }
	void setDirection(Direction d) { dir = d; }
	Direction getDir() { return dir; }
};
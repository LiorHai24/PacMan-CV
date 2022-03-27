#pragma once
#include "Point.h"
#include "Color.h"
#include "Board.h"
#include "Object.h"
#include<cstring>

class Ghost : public Object {
	char prevspace = '.';// maybe ' '
	LEVEL lv;
	//string smart;
public:
	void move(int rows, int cols, bool NoColor);
	void setLvl(LEVEL l) { lv = l; }
	LEVEL getLvl() { return lv; }
	void setDirectionG() { dir =(Direction)( rand() % 5); }
	void setFailedDirection() { dir = Direction::STAY; }
	char getPrevspace() const{ return prevspace; }
	Point getLocation() const{ return bodyLocation; }
	std::string AfficientMove(const Board& b, Point src, Point dest);
	void setprevspace(char c) { prevspace = c; }
	void SmartSetDirection(const Board& b, Point pacman);
};
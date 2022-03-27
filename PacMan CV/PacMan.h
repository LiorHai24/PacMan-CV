#ifndef _PACMAN
#define _PACMAN

#include "point.h"
#include "Color.h"
#include "Board.h"
#include "Object.h"

class PacMan: public Object{
	char arrowKeys[5];
public:
	Direction getDirection(char key) const;
	void move(int rows, int cols, bool NoColor);
	bool checkLegal(const Board& b)override;
	void setArrowKeys(const char* keys) 
	{ 
			arrowKeys[0] = keys[0];//up
			arrowKeys[1] = keys[1];//down
			arrowKeys[2] = keys[2];//left
			arrowKeys[3] = keys[3];//right
			arrowKeys[4] = keys[4];//stay
	}
	void Animation(bool NoColor);

};
#endif

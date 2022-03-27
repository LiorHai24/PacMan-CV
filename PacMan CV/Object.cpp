#include"Object.h"

bool Object::checkLegal(const Board& b)
{
	int x, y;
	x = bodyLocation.getx();
	y = bodyLocation.gety();
	switch (dir) {
	case Direction::UP: // up
		if (y == 0 || b.getBoard()[y - 1][x] == '#')
		{
			dir = Direction::STAY;
			return false;
		}
		return true;
	case Direction::DOWN: // DOWN
		if (y == b.getRows() - 1 || b.getBoard()[y + 1][x] == '#')
		{
			dir = Direction::STAY;
			return false;
		}
		return true;
	case Direction::LEFT: // LEFT
		if (x == 0||b.getBoard()[y][x - 1] == '#')
		{
			dir = Direction::STAY;
			return false;
		}
		return true;
	case Direction::RIGHT: // RIGHT
		if (x == b.getCols() - 1 || b.getBoard()[y][x + 1] == '#')
		{
			dir = Direction::STAY;
			return false;
		}
		return true;
	case Direction::STAY: // STAY
		return false;
	}
	return false;
}
void Object::setFigure(char c)
{
	body = c;
}
void Object::draw() const
{
	bodyLocation.draw(body);
}

#include "Point.h"

void Point::draw(char ch) const {
	gotoxy(x, y);
	std::cout << ch << std::endl;
	gotoxy(x, y);
}

void Point::move(Direction dir, int rows, int cols) {
	switch (dir) {
	case Direction::UP:// UP
		if (y == 0) {
			y = rows - 1;
		}
		else
		--y;
		break;
	case Direction::DOWN:// DOWN
		if (y == rows - 1) {
			y = 0;
		}
		else
		++y;
		break;
	case Direction::LEFT: // LEFT
		if (x == 0) {
			x = cols - 1;
		}
		else
			x--;
		break;
	case Direction::RIGHT: // RIGHT
		if (x == cols - 1) {
			x = 0;
		}
		else
			x++;
		break;
	case Direction::STAY: // STAY
		break;
	}
}
Point Point::reverse()
{
	return { y, x };
}
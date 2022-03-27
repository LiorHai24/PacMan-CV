#include "PacMan.h"
Direction PacMan::getDirection(char key) const
{
	for (int i = 0; i < 5; i++)
	{
		if (key == arrowKeys[i])
			return (Direction)i;
	}
	return Direction::FAIL;
}

void PacMan::move(int rows, int cols, bool NoColor)
{
	if (dir != Direction::STAY)
	{
		gotoxy(bodyLocation.getx(), bodyLocation.gety());
		std::cout << ' ';
		bodyLocation.move(dir, rows, cols);
		if (!NoColor)
			setTextColor(color);
		bodyLocation.draw(body);
	}
}

bool PacMan::checkLegal(const Board& b)
{
	int x, y;
	x = bodyLocation.getx();
	y = bodyLocation.gety();
	switch (dir) {
	case Direction::UP: // up
		if (y == 0)
			return true;
		if (b.getBoard()[y - 1][x] == '#' )
		{
			dir = Direction::STAY;
			return false;
		}
			return true;
	case Direction::DOWN: // DOWN
		if (y == b.getRows() - 1)
			return true;
		if (b.getBoard()[y + 1][x] == '#')
		{
			dir = Direction::STAY;
			return false;
		}
		return true;
	case Direction::LEFT: // LEFT
		if(x == 0)
			return true;
		if (b.getBoard()[y][x - 1] == '#')
		{
			dir = Direction::STAY;
			return false;
		}
			return true;
	case Direction::RIGHT: // RIGHT
		if (x == b.getCols() - 1)
			return true;
		if (b.getBoard()[y][x + 1] == '#')
		{
			dir = Direction::STAY;
			return false;
		}
			return true;
	case Direction::STAY: // STAY
		return true;
	}
	return true;
}
void PacMan::Animation(bool NoColor)
{
	for (int i = 0; i < 3; i++)//death animation
	{
		std::cout << ' ';
		gotoxy(getLocation().getx(),getLocation().gety());
		hideCursor();
		Sleep(200);
		if (!NoColor)
			setTextColor(getColor());
		std::cout << getbody();
		gotoxy(getLocation().getx(), getLocation().gety());
		hideCursor();
		Sleep(200);
	}
}
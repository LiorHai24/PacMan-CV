#include "Fruit.h"
void Fruit::move(int rows, int cols, bool NoColor)
{
	if (dir != Direction::STAY)
	{
		gotoxy(bodyLocation.getx(), bodyLocation.gety());
		if (!NoColor)
			setTextColor(Color::WHITE);
		cout << prevspace;
		bodyLocation.move(dir, rows, cols);
		if (!NoColor)
			setTextColor(color);
		bodyLocation.draw(body);
	}
}
void Fruit::setNewF(const Board& b)
{
	int rows, cols;
	setDirectionF();
	body = ((rand() % 5) + 5) + '0';
	rows = b.getRows();
	cols = b.getCols();
	setLocation({ rand() % cols, rand() % rows });
	while (b.getBoard()[getLocation().gety()][getLocation().getx()] != '.')
	{
		setLocation({ rand() % cols, rand() % rows });
	}
	setprevspace(b.getBoard()[getLocation().gety()][getLocation().getx()]);
}
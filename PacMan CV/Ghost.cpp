#include "Ghost.h"
using namespace std;
void Ghost::move(int rows, int cols, bool NoColor)
{
	if (dir != Direction::STAY)
	{
		
		gotoxy(bodyLocation.getx(), bodyLocation.gety());
		if(!NoColor)
			setTextColor(Color::WHITE);
		cout << prevspace;
		bodyLocation.move(dir, rows, cols);
		if(!NoColor)
			setTextColor(color);
		bodyLocation.draw(body);
	}
}

bool Valid(int row, int col, int boardRow, int boardCol) { return (row >= 0) && (col >= 0) && (row < boardRow) && (col < boardCol); }

string Ghost::AfficientMove(const Board& b, Point src, Point dest)
{
	int boardRow, boardCol;
	queue<Node> q;
	Point pt;
	Node next, curr;
	Node s = { src, 0 };
	int rows[4] = { -1, 0, 0, 1 };
	int ptx, pty, dist;
	int cols[4] = { 0, -1, 1, 0 };

	boardRow = b.getRows();
	boardCol = b.getCols();
	int** mat = new int* [boardRow];
	bool** Boolmat = new bool* [boardRow];

	for (int i = 0; i < boardRow; i++)
	{
		mat[i] = new int[boardCol];
		fill_n(mat[i], boardCol, -1);

		Boolmat[i] = new bool[boardCol];
		fill_n(Boolmat[i], boardCol, false);
	}

	mat[src.getx()][src.gety()] = 0;
	Boolmat[src.getx()][src.gety()] = true;///
	q.push(s);

	bool ok = false;
	string path = "";
	while (!q.empty())
	{
		curr = q.front();
		pt = curr.pt;
		ptx = pt.getx();
		pty = pt.gety();
		if (ptx == dest.getx() && pty == dest.gety())
		{

			dist = curr.dist;
			mat[ptx][pty] = dist;
			while (ptx != src.getx() || pty != src.gety())
			{
				if (ptx < boardRow - 1 && mat[ptx + 1][pty] == dist - 1)
				{
					ptx++;
					path += 'U';
				}
				if (ptx > 0 && mat[ptx - 1][pty] == dist - 1)
				{
					ptx--;
					path += 'D';
				}
				if (pty > 0 && mat[ptx][pty - 1] == dist - 1)
				{
					pty--;
					path += 'R';
				}
				if (pty < boardCol - 1 && mat[ptx][pty + 1] == dist - 1)
				{
					pty++;
					path += 'L';
				}
				dist--;
			}
			reverse(path.begin(), path.end());
			ok = true;
			break;
		}
		q.pop();
		for (int i = 0; i < 4; i++)
		{
			int afterRow = pt.getx() + rows[i];
			int afterCol = pt.gety() + cols[i];

			if (Valid(afterRow, afterCol, boardRow, boardCol) && b.getBoard()[afterRow][afterCol] != '#' && !Boolmat[afterRow][afterCol])
			{
				Boolmat[afterRow][afterCol] = true;
				next = { { afterRow, afterCol }, curr.dist + 1 };
				q.push(next);
				mat[afterRow][afterCol] = curr.dist + 1;
			}
		}
	}
	if (!ok)
		return " ";
	return path;

}
void Ghost::SmartSetDirection(const Board&b, Point pacman)
{
	string hardness;
	hardness = AfficientMove(b, getLocation().reverse(), pacman.reverse());
	switch (hardness[0]) {
	case 'U':
	{
		setDirection(Direction::UP);
		break;
	}
	case 'D':
	{
		setDirection(Direction::DOWN);
		break;
	}
	case 'L':
	{
		setDirection(Direction::LEFT);
		break;
	}
	case 'R':
	{
		setDirection(Direction::RIGHT);
		break;
	}
	}
	return;
}

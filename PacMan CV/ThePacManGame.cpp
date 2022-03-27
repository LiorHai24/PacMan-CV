#include "ThePacManGame.h"
using namespace std;
bool ThePacManGame::firstGame = true;

bool ThePacManGame::init()//make a const enum points to start for pacman and ghosts.
{
	Menu start;
	static LEVEL l;
	char level = NULL;
	short GhostCount;
	srand(time(NULL));
	if (!firstGame || start.StartScreenPrint(NoColor))
	{
		if (b.ReadBoard())
		{//only from read board u get how much ghosts there are which is needed before^^
			if (b.getRows() == -1)
			{
				return false;
			}
			GhostCount = b.getIndex();
			if (firstGame)
			{
				l = start.GhostLevel();
			}
			obj[0] = new PacMan;
			obj[1] = new Fruit;
			for (int i = 0; i < GhostCount; i++)
			{
				obj[i + 2] = new Ghost;
				((Ghost*)obj[i + 2])->setFigure('$');
				((Ghost*)obj[i + 2])->setLocation(b.getGhost(i));
				((Ghost*)obj[i + 2])->setDirection(Direction::STAY);
				((Ghost*)obj[i + 2])->setLvl(l);
			}
			((PacMan*)obj[0])->setArrowKeys("wxads");
			((Fruit*)obj[1])->setFigure(((rand() % 5) + 5) + 48);
			((PacMan*)obj[0])->setFigure(153);
			((Fruit*)obj[1])->setNewF(b);
			((PacMan*)obj[0])->setLocation(b.getpac());
			((PacMan*)obj[0])->setDirection(Direction::STAY);
			if (!NoColor)
			{
				obj[1]->setColor(Color::RED);//fruit color
				b.setColor(Color::BLUE);
				obj[0]->setColor(Color::YELLOW);//pacman color
				for (int i = 0; i < GhostCount; i++)// needed here.
				{
					switch (i) {
					case 0:
					{
						obj[i + 2]->setColor(Color::GREEN);
						break;
					}
					case 1:
					{
						obj[i + 2]->setColor(Color::DARKGREY);
						break;
					}
					case 2:
					{
						obj[i + 2]->setColor(Color::LIGHTMAGENTA);
						break;
					}
					case 3:
					{
						obj[i + 2]->setColor(Color::LIGHTCYAN);
						break;
					}
					}
				}
			}
			firstGame = false;
			clear_screen();
			return true;
		}
		else
			return false;
	}
	else
		return false;
}

bool ThePacManGame::run()
{
	char End = NULL;
	bool slow = false, gain = false;

	char key = 's';
	bool resLife = false;
	int rows, cols, smartClock = 0, randomClock = 0, total = b.getTotal();
	static int lives = 3;
	short GhostCount, fruitime = 0;
	Direction dir= Direction::STAY;
	Direction NewDir;
	string hardness = "";
	rows = b.getRows();
	cols = b.getCols();
	GhostCount = b.getIndex();

	gotoxy(0, 0);
	b.printBoard(NoColor);
	gotoxy(b.getScore().getx(), b.getScore().gety());
	if (!NoColor)
		setTextColor(Color::WHITE);
	cout << "LIVES:";
	for (int  i = 0; i < lives; i++)
	{
		cout << " " << obj[0]->getbody();
	}
	gotoxy(b.getScore().getx(), b.getScore().gety() + 2);
	cout << "Points: 0";
	for (int i = 0; i < GhostCount + 2; i++)
	{
		if (!NoColor)
			setTextColor(obj[i]->getColor());
		obj[i]->draw();
	}

	do {
		if (_kbhit())
		{
			key = _getch();
			if (key == ESC)
			{
				gotoxy(0, 24);//
				if (!NoColor)
					setTextColor(Color::WHITE);
				cout << "Game paused. Press ESC to continue." << endl;
				key = _getch();
				while (key != ESC)
					key = _getch();
				gotoxy(0, 24);
				cout << "                                   ";
			}
			else
			{
				/*/NewDir = ((PacMan*)obj[0])->getDirection(key);
				if (dir != NewDir)// != Direction::FAIL)
					obj[0]->setDirection(NewDir);*/
				NewDir = ((PacMan*)obj[0])->getDirection(key);
				if (obj[0]->getDir() != NewDir)
					obj[0]->setDirection(NewDir);
			}
		}
		for (int i = 0; i < GhostCount + 2; i++)
		{
			bool bonus = false;
			if (typeid(*(obj[i])) == typeid(PacMan))
			{
				if (obj[i]->checkLegal(b))
				{
						obj[i]->move(rows, cols, NoColor);
					if (b.getBoard()[obj[i]->getLocation().gety()][obj[i]->getLocation().getx()] == '.')
					{
						gain = true;
						b.setBoard(obj[i]->getLocation().gety(), obj[i]->getLocation().getx(), ' ');
						b.WakaWaka();
					}
					for (int i = 0; i < GhostCount; i++)
					{
						if (checkPandGColide(i + 2, resLife, lives))
							break;
					}
					bonus = checkPandFColide();
					if (gain || bonus)
					{
						printScore();
						gain = false;
					}
				}
			}
			else if (typeid(*(obj[i])) == typeid(Ghost))
			{
				if (slow && resLife == false)
				{
					switch (((Ghost*)obj[i])->getLvl()) {
					case LEVEL::EASY:
					{
						((Ghost*)obj[i])->setDirectionG();
						break;
					}
					case LEVEL::INTERMEDIATE:
					{
						if (smartClock < 20)
						{
							smartClock++;
							((Ghost*)obj[i])->SmartSetDirection(b, obj[0]->getLocation());
						}
						else if(randomClock < 5)//smartclock is 20
						{
							((Ghost*)obj[i])->setDirectionG();
							randomClock++;
							if (randomClock == 5)
							{
								randomClock = 0;
								smartClock = 0;
							}
						}
						break;
					}
					case LEVEL::HARD:
					{

						((Ghost*)obj[i])->SmartSetDirection(b, obj[0]->getLocation());
						break;
					}
					}
					if (obj[i]->checkLegal(b))
					{
						((Ghost*)obj[i])->setprevspace(b.getBoard()[obj[i]->getLocation().gety()][obj[i]->getLocation().getx()]);
						obj[i]->move(rows, cols, NoColor);
						if (checkPandGColide(i, resLife, lives))
							break;
						if (obj[i]->getLocation().gety() == obj[1]->getLocation().gety() && obj[i]->getLocation().getx() == obj[1]->getLocation().getx())
						{
							Colide();
						}
					}
				}
			}
			else if (typeid(*(obj[i])) == typeid(Fruit))
			{
				((Fruit*)obj[i])->SpawnTime();
				if (slow && (obj[i]->getbody()!='0'))
				{
					((Fruit*)obj[i])->setDirectionF();
					if (obj[i]->checkLegal(b))
					{
						((Fruit*)obj[i])->setprevspace(b.getBoard()[obj[i]->getLocation().gety()][obj[i]->getLocation().getx()]);
						obj[i]->move(rows, cols, NoColor);
						if(!bonus)
							if (checkPandFColide())
								printScore();
						for (int j = 0; j <GhostCount; j++)
						{
							if (obj[j + 2]->getLocation().gety() == obj[1]->getLocation().gety() && obj[j + 2]->getLocation().getx() == obj[1]->getLocation().getx())
								Colide();
						}
					}
				}
				if (obj[i]->getbody() == '0' && ((Fruit*)obj[i])->getFruitTimer() > 80)
				{
					((Fruit*)obj[i])->Rest();
					((Fruit*)obj[i])->setNewF(b);
				}
				else if (((Fruit*)obj[i])->getbody() != '0' && ((Fruit*)obj[i])->getFruitTimer() > 120)
				{
					((Fruit*)obj[i])->Rest();
					gotoxy((obj[i])->getLocation().getx(), (obj[i])->getLocation().gety());
					if (!NoColor)
						setTextColor(Color::WHITE);
					cout << ((Fruit*)obj[i])->getprevspace();
					Colide();
				}
			}
		}
		slow = !slow;
		Sleep(100);
	} while (b.ReturnNumOfDots() != 0 && resLife == false);//need function to check end game
	((PacMan*)obj[0])->Animation(NoColor);
	gotoxy(0, 24);
	if(!NoColor)
		setTextColor(Color::WHITE);
	if (resLife == true)
	{
		cout << "GAME OVER!   " << "Better luck next time:)" << endl;
		Sleep(3000);
	}
	else
	{
		cout << "Congrats! You Won This Round!" << endl
			<< "Press any key to continue" << endl;
		do {
			if (_kbhit())
			{
				End = _getch();
			}
		} while (End == NULL);
		b.nextscore();
	}
	for (int i = 0; i < GhostCount + 2; i++)
	{
		delete[] obj[i];
	}
	return !resLife;
}

bool ThePacManGame::Death(int& lives)
{
	int slot = b.getScore().getx() + 5;
	short GhostCount = b.getIndex();
	slot = slot + (lives * 2);
	((PacMan*)obj[0])->Animation(NoColor);
	gotoxy(slot, b.getScore().gety());
	cout << ' ';
	lives--;
	gotoxy(0, 24);
	if (!NoColor)
		setTextColor(Color::WHITE);
	cout << "Oops! You Ran Into A Ghost Which Took One Of Your Lives. You Have " << lives << " Remaining Lives." << endl;
	Sleep(4000);
	gotoxy(0, 24);
	cout << "                                                                                    " << endl;
	if (lives == 0)
		return true;
	else {
		for (int i = 0; i < GhostCount + 2; i++)
		{
			if (typeid(*(obj[i])) == typeid(PacMan))
			{
				obj[i]->setLocation(b.getpac());
				obj[i]->setDirection(Direction::STAY);
			}
			if (typeid(*(obj[i])) == typeid(Ghost)|| typeid(*(obj[i])) == typeid(Fruit))
			{
				gotoxy(obj[i]->getLocation().getx(),obj[i]->getLocation().gety());
				if (!NoColor)
					setTextColor(Color::WHITE);
				if (typeid(*(obj[i])) == typeid(Ghost))
				{
					cout << ((Ghost*)obj[i])->getPrevspace();
					obj[i]->setLocation(b.getGhost(i - 2));
				}
				else
				{
					if(obj[i]->getbody()!='0')
						cout << ((Fruit*)obj[i])->getprevspace();
					((Fruit*)obj[i])->setNewF(b);
				}

			}

			if (!NoColor)
				setTextColor(obj[i]->getColor());
			obj[i]->draw();
		}
		return false;
	}
}

bool ThePacManGame::checkPandGColide(int i, bool& resLife, int& lives)
{
	if ((obj[i]->getLocation().getx() == obj[0]->getLocation().getx()) &&
		(obj[i]->getLocation().gety() == obj[0]->getLocation().gety()))
	{
		resLife = Death(lives);
		return true;
	}
	return false;
}
bool ThePacManGame::checkPandFColide()
{
	short fPower;
	if (obj[0]->getLocation().gety() == obj[1]->getLocation().gety() && obj[0]->getLocation().getx() == obj[1]->getLocation().getx())
	{
		fPower = ((Fruit*)obj[1])->getbody() - 48;
		b.AddToTotal(fPower);
		Colide();
		return true;
	}
	return false;
}
void ThePacManGame::printScore()
{
	gotoxy(b.getScore().getx() + 8, b.getScore().gety() + 2);
	if (!NoColor)
		setTextColor(Color::WHITE);
	cout << b.getTotal() - b.ReturnNumOfDots() << endl;
}
void ThePacManGame::Colide()
{
	obj[1]->setFigure('0');
	obj[1]->setDirection(Direction::STAY);
	obj[1]->setLocation({ NULL, NULL });
}
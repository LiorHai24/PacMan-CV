#include "Menu.h"
using namespace std;

LEVEL Menu::GhostLevel()
{
	char i, c = NULL;
	clear_screen();
	cout << "Please enter the hardness of the game you would like:" << endl
		<< "Enter 1 for easy 2 for intermediate, and 3 for hard." << endl;
	do {
		if (_kbhit())
		{
			i = _getch();
			if (i == '1' || i == '2' || i == '3')
			{
				c = i;
			}
			else
				cout << "You have entered a non optional option, please choose again." << endl;
		}
	} while (c == NULL);
	return (LEVEL)(c - '0');
}
void Menu::ShowRules()
{
	clear_screen();
	cout << "Controls: W - up, A - left, D - right, X - Down, S - stay." << endl
		<< "Your objective is to eat all the dots without touching the ghosts." << endl
		<< "If the ghost touches you, you die." << endl
		<< "If you die 3 times, its Game Over." << endl;
}
bool Menu::StartScreenPrint(bool& NoColor)
{
	char i = NULL;
	cout << "Welcome To PacMan :) Please Choose One Of The Following:" << endl << "1.Start Game With Colors" << endl << "2.Start Game Without Colors" << endl << "8.Show Directions & Rules"
		<< endl << "9.Exit" << endl;
	do {
		if (_kbhit())
		{
			i = _getch();
		}
	} while (i == NULL);
	switch (i) {
	case '1':
		return true;
	case'2':
	{
		NoColor = true;
		return true;
	}
	case '8':
		ShowRules();
		cout << endl;
		StartScreenPrint(NoColor);
		break;
	case '9':
		return false;
	default:
		clear_screen();
		cout << "You entered a non registered option. Please choose again." << endl;
		StartScreenPrint(NoColor);
		break;
	}
	return true;
}
//Name: Lior Hai
//Id: 207134990
//Name: Ori Marko
//Id: 318846615
#define _CRT_SECURE_NO_WARNINGS
using namespace std;
#include "ThePacManGame.h"

int main()
{
	ThePacManGame game;
	while (1)
	{
		clear_screen();
		if (game.init()&& game.run())
				continue;
			else
				break;
	}
}
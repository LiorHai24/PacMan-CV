#pragma once
#define _HAS_STD_BYTE 0
#include "Board.h"
#include "Fruit.h"
#include "Menu.h"
#include "PacMan.h"
#include "Ghost.h"
#include "Object.h"
#include "Color.h"
#include <time.h>
class ThePacManGame {
	enum {ESC = 27};
	Board b;
	Object* obj[6];
	bool NoColor = false;
	static bool firstGame;
public:
	bool init();
	void printScore();
	bool run();
	bool Death(int& lives);
	void Colide();
	bool checkPandFColide();
	bool checkPandGColide(int i, bool& resLife, int& lives);
	bool getFirst() { return firstGame; }
};
#pragma once
#include "Object.h"
class Fruit : public Object {
	int FruitTimer = 0;
	char prevspace;
public:
	//void setprevSpace(char c) { prevSpace = c; }
	char getprevspace() { return prevspace; }
	void setDirectionF() { setDirection((Direction)(rand() % 5)); }
	void setprevspace(char c) { prevspace = c; }
	void move(int rows, int cols, bool NoColor) override;
	void setNewF(const Board& b);
	int getFruitTimer() { return FruitTimer; };
	void SpawnTime() { FruitTimer += (rand() % 3); };
	void Rest() { FruitTimer = 0; };
	//void SetDigit() { digit = (rand() % 5) + 5; }
};
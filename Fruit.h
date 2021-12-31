#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "GameObject.h"
#include "Board.h"

using namespace std;

class Fruit : public GameObject {

private:
	int value;
	int initialX;
	int initialY;

public:
	//Getters
	const int getValue() const { return value; }
	const int getInitialX() const { return initialX; }
	const int getInitialY() const { return initialY; }

	//Setters
	void setInitialX(int initialX) { this->initialX = initialX; }
	void setInitialY(int initialY) { this->initialY = initialY; }

	//Builders
	Fruit();
	Fruit(int initialX, int initialY);

	//Functions
	int makeTurnFruit(Board& gameBoard , int& save_mode_direcion);
	void setLocation(Board& gameBoard);
	void print()
	{
		gotoxy(y, x);
		cout << getValue();
	}
};
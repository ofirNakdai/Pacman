#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "GameObject.h"
#include "Board.h"

using namespace std;

class Ghost : public GameObject {

private:
	int initialX;
	int initialY;

public:
	//Getters
	const int getInitialX() const { return initialX; }
	const int getInitialY() const { return initialY; }

	//Setters
	void setInitialX(int initialX) { this->initialX = initialX; }
	void setInitialY(int initialY) { this->initialY = initialY; }

	//Builders
	Ghost();
	Ghost(int initialX, int initialY);

	//Functions
	int generateCell(int pacmanX, int pacmanY, Board& gameBoard);
	int makeMoveGhost(int newX, int newY, Board& gameBoard);
};
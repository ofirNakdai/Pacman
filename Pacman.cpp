#include "Pacman.h"

Pacman::Pacman()
	: GameObject('@', -1, -1, 1)
{
	initialX = -1;
	initialY = -1;
}

Pacman::Pacman(int initialX, int initialY) 
	: GameObject('@', initialX, initialY, 1)
{
	this->initialX = initialX;
	this->initialY = initialY;
}

int Pacman::makeMovePacman(int& newX, int& newY, Board& gameBoard)
{
	if (newX == (gameBoard.getTopBorder() - 1))// top Boreder 0 newX = -1
	{
		newX = (gameBoard.getBottomBorder());
	}
	else if (newY == (gameBoard.getRightBorder() + 1))
	{
		newY = (gameBoard.getLeftBorder());
	}
	else if (newX == (gameBoard.getBottomBorder() + 1))
	{
		newX = (gameBoard.getTopBorder());
	}
	else if (newY == (gameBoard.getLeftBorder() - 1))
	{
		newY = (gameBoard.getRightBorder());
	}
	if (gameBoard.getCellPtr(newX, newY)->getObject() == nullptr)
	{
		gameBoard.getCellPtr(x, y)->setObject(nullptr);
		gameBoard.getCellPtr(x, y)->printCell();
		setX(newX);
		setY(newY);
		if (gameBoard.getCellContent(newX, newY) == CRUMB)
		{
			gameBoard.getCellPtr(newX, newY)->setContent(EMPTY);
			gameBoard.setCrumbs(gameBoard.getCrumbs() - 1);
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else if (gameBoard.getCellPtr(newX, newY)->getObject()->getSign() == '+')
	{
		gameBoard.getCellPtr(x, y)->setObject(nullptr);
		gameBoard.getCellPtr(x, y)->printCell();
		setX(newX);
		setY(newY);
		return 2;
	}
	else
	{
		return -1;
	}
}
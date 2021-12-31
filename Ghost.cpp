#include "Ghost.h"

Ghost::Ghost()
	: GameObject('$', -1, -1, 2)
{
	initialX = -1;
	initialY = -1;
}

Ghost::Ghost(int initialX, int initialY)
	: GameObject('$', initialX, initialY, 2)
{
	this->initialX = initialX;
	this->initialY = initialY;
}

int Ghost::makeMoveGhost(int newX, int newY, Board& gameBoard)
{
	if (newX == gameBoard.getTopBorder() || newX == gameBoard.getBottomBorder())
	{
		return -1;
	}
	if (newY == gameBoard.getRightBorder() || newY == gameBoard.getLeftBorder())
	{
		return -1;
	}
	if (gameBoard.getCellContent(newX, newY) == WALL)
	{
		return -1;
	}
	else
	{
		if (gameBoard.getCellPtr(newX, newY)->getObject() == nullptr)
		{
			gameBoard.getCellPtr(getX(), getY())->setObject(nullptr);
			gameBoard.getCellPtr(getX(), getY())->printCell();
			setX(newX);
			setY(newY);
			return 0;
		}
		else if (gameBoard.getCellPtr(newX, newY)->getObject()->getSign() == '+')
		{
			gameBoard.getCellPtr(getX(), getY())->setObject(nullptr);
			gameBoard.getCellPtr(getX(), getY())->printCell();
			setX(newX);
			setY(newY);
			return 1;
		}
		else if(gameBoard.getCellPtr(newX, newY)->getObject()->getSign() == '@')
		{
			gameBoard.getCellPtr(newX, newY)->setObject(nullptr);
			gameBoard.getCellPtr(newX, newY)->printCell();
			gameBoard.getCellPtr(getX(), getY())->setObject(nullptr);
			gameBoard.getCellPtr(getX(), getY())->printCell();
			setX(initialX);
			setY(initialY);
			return 2;
		}
		else
		{
			gameBoard.getCellPtr(getX(), getY())->setObject(nullptr);
			gameBoard.getCellPtr(getX(), getY())->printCell();
			setX(newX);
			setY(newY);
			return 3;
		}
	}
}

int Ghost::generateCell(int pacmanX, int pacmanY, Board& gameBoard)
{
	int disX, disY;
	if (x >= pacmanX)
	{
		disX = x - pacmanX;
	}
	else
	{
		disX = pacmanX - x;
	}
	if (y >= pacmanY)
	{
		disY = y - pacmanY;
	}
	else
	{
		disY = pacmanY - y;
	}
	if (disX == 0)
	{
		if (y >= pacmanY)
		{
			return 3;
		}
		else
		{
			return 4;
		}
	}
	else if (disY == 0)
	{
		if (x >= pacmanX)
		{
			return 1;
		}
		else
		{
			return 2;
		}
	}
	else if (disX <= disY)
	{
		if (x >= pacmanX)
		{
			return 1;
		}
		else
		{
			return 2;
		}
	}
	else
	{
		if (y >= pacmanY)
		{
			return 3;
		}
		else
		{
			return 4;
		}
	}
}
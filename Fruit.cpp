#include"Fruit.h"

Fruit::Fruit()
	: GameObject('+', -1, -1, 4)
{
	value = generateRandomNumber(5, 9);
	initialX = -1;
	initialY = -1;
}

Fruit::Fruit(int initialX, int initialY)
	: GameObject('+', initialX, initialY, 4)
{
	value = generateRandomNumber(5, 9);
	this->initialX = initialX;
	this->initialY = initialY;
}
void Fruit::setLocation(Board& gameBoard)
{
	int i, j;
	for (i = gameBoard.getTopBorder()+1; i < gameBoard.getRows(); i++)
	{
		for (j = gameBoard.getLeftBorder()+1; j < gameBoard.getCols(); j++)
		{
			if (gameBoard.getCellPtr(i, j)->getObject() == nullptr && gameBoard.getCellPtr(i, j)->getContent() != WALL)
			{
				initialX = i;
				x = i;
				initialY = j;
				y = j;
				return;
			}
		}
	}
}

int Fruit::makeTurnFruit(Board& gameBoard, int& save_mode_direcion)
{
	int direction;
	direction = generateRandomNumber(1, 4);
	save_mode_direcion = direction; //for docomentation in save mode file

	if (direction == 1)
	{
		if (gameBoard.getCellContent(x - 1, y) != WALL && gameBoard.getCellContent(x - 1, y) != gameBoard.getTopBorder())
		{
			if (gameBoard.getLeftBorder() == x - 1)
			{
				return 0;
			}
			else if (gameBoard.getCellPtr(x - 1, y)->getObject() == nullptr)
			{
				gameBoard.getCellPtr(x, y)->setObject(nullptr);
				gameBoard.getCellPtr(x, y)->printCell();
				setX(x - 1);
				return 1;
			}
			else if (gameBoard.getCellPtr(x - 1, y)->getObject()->getSign() == '@')
			{
				gameBoard.getCellPtr(x, y)->setObject(nullptr);
				gameBoard.getCellPtr(x, y)->printCell();
				return 2;
			}
			else
			{
				gameBoard.getCellPtr(x, y)->setObject(nullptr);
				gameBoard.getCellPtr(x, y)->printCell();
				return 3;
			}
		}
	}
	else if (direction == 2)
	{
		if (gameBoard.getCellContent(x + 1, y) != WALL && gameBoard.getCellContent(x - 1, y) != gameBoard.getBottomBorder())
		{
			if (gameBoard.getRightBorder() == x + 1)
			{
				return 0;
			}
			else if (gameBoard.getCellPtr(x + 1, y)->getObject() == nullptr)
			{
				gameBoard.getCellPtr(x, y)->setObject(nullptr);
				gameBoard.getCellPtr(x, y)->printCell();
				setX(x + 1);
				return 1;
			}
			else if (gameBoard.getCellPtr(x + 1, y)->getObject()->getSign() == '@')
			{
				gameBoard.getCellPtr(x, y)->setObject(nullptr);
				gameBoard.getCellPtr(x, y)->printCell();
				return 2;
			}
			else
			{
				gameBoard.getCellPtr(x, y)->setObject(nullptr);
				gameBoard.getCellPtr(x, y)->printCell();
				return 3;
			}
		}
	}
	else if (direction == 3)
	{
		if (gameBoard.getCellContent(x, y + 1) != WALL && gameBoard.getCellContent(x - 1, y) != gameBoard.getRightBorder())
		{
			if (gameBoard.getBottomBorder() == y + 1)
			{
				return 0;
			}
			else if (gameBoard.getCellPtr(y + 1, y)->getObject() == nullptr)
			{
				gameBoard.getCellPtr(x, y)->setObject(nullptr);
				gameBoard.getCellPtr(x, y)->printCell();
				setY(y + 1);
				return 1;
			}
			else if (gameBoard.getCellPtr(y + 1, y)->getObject()->getSign() == '@')
			{
				gameBoard.getCellPtr(x, y)->setObject(nullptr);
				gameBoard.getCellPtr(x, y)->printCell();
				return 2;
			}
			else
			{
				gameBoard.getCellPtr(x, y)->setObject(nullptr);
				gameBoard.getCellPtr(x, y)->printCell();
				return 3;
			}
		}
	}
	else
	{
		if (gameBoard.getCellContent(x, y - 1) != WALL && gameBoard.getCellContent(x - 1, y) != gameBoard.getLeftBorder())
		{
			if (gameBoard.getCellContent(x, y - 1) != WALL)
			{
				if (gameBoard.getTopBorder() == y - 1)
				{
					return 0;
				}
				else if (gameBoard.getCellPtr(y - 1, y)->getObject() == nullptr)
				{
					gameBoard.getCellPtr(x, y)->setObject(nullptr);
					gameBoard.getCellPtr(x, y)->printCell();
					setY(y + 1);
					return 1;
				}
				else if (gameBoard.getCellPtr(y - 1, y)->getObject()->getSign() == '@')
				{
					gameBoard.getCellPtr(x, y)->setObject(nullptr);
					gameBoard.getCellPtr(x, y)->printCell();
					return 2;
				}
				else
				{
					gameBoard.getCellPtr(x, y)->setObject(nullptr);
					gameBoard.getCellPtr(x, y)->printCell();
					return 3;
				}
			}
		}
	}
	return 0;
}
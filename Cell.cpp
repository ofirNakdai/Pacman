#include "Cell.h"

Cell::Cell()
{
	x = -1;
	y = -1;
	content = EMPTY;
	object = nullptr;
}

Cell::~Cell()
{
	if (object != nullptr)
	{
		delete object;
	}
}


Cell::Cell(int x, int y, int content, GameObject* object)
{
	this->x = x;
	this->y = y;
	this->content = content;
	this->object = object;
}

void Cell::printCell()
{
	gotoxy(y, x);
	if (object != nullptr)
	{
		object->printObject();
	}
	else
	{
		printContent();
	}
}

void Cell::printContent()
{
	switch (content)
	{
	case WALL:
		cout << '#';
		break;
	case EMPTY:
		cout << ' ';
		break;
	case CRUMB:
		cout << '*';
		break;
	}
}
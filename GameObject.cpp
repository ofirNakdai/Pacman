#include "GameObject.h"

GameObject::GameObject()
{
	sign = '?';
	x = -1;
	y = -1;
	pace = 0;
}

GameObject::GameObject(char sign, int x, int y, int pace)
{
	this->sign = sign;
	this->x = x;
	this->y = y;
	this->pace = pace;
}

void GameObject::printObject()
{
	cout << getSign();
}
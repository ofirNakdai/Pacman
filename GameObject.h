#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <math.h>
#include "Utilities.h"
#include "Random.h"

using namespace std;

class GameObject {

protected:
	char sign;
	int x;
	int y;
	int pace;

public:
	//Getters
	char getSign() const { return sign; }
	const int getX() const { return x; }
	const int getY() const { return y; }
	const int getPace() const { return pace; }
	
	//Setters
	void setSign(char sign_val) { sign = sign_val; }
	void setX(int x) { this->x = x; }
	void setY(int y) { this->y = y; }
	void setPace(int pace) { this->pace = pace; }

	//Builders
	GameObject();
	GameObject(char sign, int x, int y, int pace);

	//Functions
	void printObject();
};
#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include "Utilities.h"
#include "Random.h"
#include "GameObject.h"

using namespace std;

const int WALL = 0;
const int EMPTY = 1;
const int CRUMB = 2;

class Cell {

protected:
	int x;
	int y;
	int content;
	GameObject* object = nullptr;

public:
	//Getters
	const int getX() const { return x; }
	const int getY() const { return y; }
	const int getContent() const { return content; }
	GameObject* getObject() { return object; }

	//Setters
	void setX(int x) { this->x = x; }
	void setY(int y) { this->y = y; }
	void setContent(int content) { this->content = content; }
	void setContent(char content)
	{
		switch (content)
		{
		case'*':
			setContent(CRUMB);
			break;
		case' ':
			setContent(CRUMB);
			break;
		case'%':
			setContent(EMPTY);
			break;
		case'#':
			setContent(WALL);
			break;
		default:
			setContent(EMPTY);
			break;
		}
	}
	void setObject(GameObject* object) { this->object = object; }

	//Constructors
	Cell();
	Cell(int x, int y, int content, GameObject* object);
	~Cell();

	//Functions 
	void printCell();
	void printContent();
};
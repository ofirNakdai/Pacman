#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <map>
#include "Cell.h"


using namespace std;

class Board {

private:
	static int count;
	int rows;
	int cols;
	int crumbs;
	Cell** gameBoard = nullptr;
	map<string, int> borders;

public:
	//Getters
	const int getRows() const { return rows; }
	const int getCols () const { return cols; }
	const int getCrumbs() const { return crumbs; }
	const int getCellContent(int x, int y) const { return gameBoard[x][y].getContent(); }
	const int getTopBorder() const { return borders.at("Top"); }
	const int getBottomBorder() const { return borders.at("Bottom"); }
	const int getLeftBorder() const { return borders.at("Left"); }
	const int getRightBorder() const { return borders.at("Right"); }
	Cell* getCellPtr(int x, int y) { return &(gameBoard[x][y]); }

	//Setters
	void setRows(int rows) { this->rows = rows; }
	void setCols(int cols) { this->cols = cols; }
	void setCrumbs(int crumbs) { this->crumbs = crumbs; }
	void setBoard(Cell** new_Board) { gameBoard = new_Board; }
	void setTopBorder(int new_border) { borders["Top"] = new_border; }
	void setBottomBorder(int new_border) { borders["Bottom"] = new_border; }
	void setLeftBorder(int new_border) { borders["Left"] = new_border; }
	void setRightBorder(int new_border) { borders["Right"] = new_border; }

	//Builders
	Board();
	Board(int rows, int cols);
	Board(const Board& other);

	//Functions
	void printBoard();
	void findBorders(const pair<int, int> data);
	int findTopBorder(int DataRow);
	int findBottomBorder(int DataRow);
	int findLeftBorder(int DataCol);
	int findRightBorder(int DataCol);
	void allocateCells(int rows, int cols);
};
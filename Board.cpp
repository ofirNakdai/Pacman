#include "Board.h"
int Board::count = 0;
Board::Board()
{
	rows = -1;
	cols = -1;
	crumbs = -1;
	borders["Top"] = -1;
	borders["Bottom"] = -1;
	borders["Left"] = -1;
	borders["Right"] = -1;
}

Board::Board(int rows, int cols)
{
	int i = 0, j = 0;
	
	this->crumbs = 0;
	this->rows = rows;
	this->cols = cols;
	borders["Top"] = -1;
	borders["Bottom"] = -1;
	borders["Left"] = -1;
	borders["Right"] = -1;

	gameBoard = new Cell* [rows];
	for (i = 0; i < rows; i++)
	{
		gameBoard[i] = new Cell[cols];
	}
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			gameBoard[i][j].setX(i);
			gameBoard[i][j].setY(j);
		}
	}
}

Board::Board(const Board& other) : rows(other.rows), cols(other.cols)
{
	int rows = other.rows;
	int cols = other.cols;

	//Allocating Cells
	gameBoard = new Cell * [rows];
	for (int i = 0; i < rows; i++)
	{
		gameBoard[i] = new Cell[cols];
	}

	//Initiating cells
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			gameBoard[i][j].setX(i);
			gameBoard[i][j].setY(j);
			gameBoard[i][j].setContent(other.gameBoard[i][i].getContent());
			gameBoard[i][j].setObject(other.gameBoard[i][i].getObject());
		}
	}

	//Initiating borders map
	borders["Top"] = 0;
	borders["Bottom"] = 0;
	borders["Left"] = 0;
	borders["Right"] = 0;

	count++;

}
void Board::printBoard()
{
	int i = 0, j = 0;
	if (gameBoard != nullptr)
	{
		for (i = 0; i < rows; i++)
		{
			for (j = 0; j < cols; j++)
			{

				gameBoard[i][j].printCell();
			}
		}
	}
}
void Board::findBorders(const pair<int, int> data)
{
	setTopBorder(findTopBorder(data.first));
	setBottomBorder(findBottomBorder(data.first));
	setLeftBorder(findLeftBorder(data.second));
	setRightBorder(findRightBorder(data.second));
}

int Board::findLeftBorder(int DataRow)
{
	int row = 0, col = 0;
	for (col = 0; col < this->cols; col++)
	{
		for (row = 0; row < this->rows; row++)
		{
			if (gameBoard[row][col].getContent() == WALL)
				return col;
		}
	}
	return -1;
}

int Board::findBottomBorder(int DataRow)
{
	int row, col;
	for (row = rows-1; row >= 0; row--)
	{
		for (col = 0; col < this->cols; col++)
		{
			if (gameBoard[row][col].getContent() == WALL)
				return row;
		}
	}
	return -1;

}
int Board::findTopBorder(int DataCol)
{
	int row, col;
	for (row = 0; row < this->rows; row++)
	{
		for (col = 0; col < this->cols; col++)
		{
			if (gameBoard[row][col].getContent() == WALL)
				return row;
		}
	}
	return -1;
}
int Board::findRightBorder(int DataCol)
{
	int row = 0, col = 0;
	for (col = this->cols - 1; col >= 0; col--)
	{
		for (row = 0; row < this->rows; row++)
		{
			if (gameBoard[row][col].getContent() == WALL)
				return col;
		}
	}
	return -1;
}

void Board::allocateCells(int rows, int cols)
{
	int i, j;
	if (gameBoard != nullptr)
	{
		for (i = 0; i < this->rows; i++)
		{
			for (j = 0; j < this->cols; j++)
			{
				if (gameBoard[i][j].getObject() != nullptr)
				{
					gameBoard[i][j].setObject(nullptr);
				}
			}
		}
		for (int i = 0; i < this->rows; i++)
		{
			delete[] gameBoard[i];
		}
		delete[] gameBoard;
		gameBoard = nullptr;
	}

	this->rows = rows;
	this->cols = cols;
	gameBoard = new Cell * [rows];
	for (i = 0; i < rows; i++)
	{
		gameBoard[i] = new Cell[cols];
	}
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			gameBoard[i][j].setX(i);
			gameBoard[i][j].setY(j);
		}
	}
}

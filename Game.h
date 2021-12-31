#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <typeinfo>
#include <map>
#include <vector>
#include <set>
#include <filesystem>
#include <iterator>
#include <string>
#include <fstream>
#include <string>

#include "Utilities.h"
#include "Random.h"
#include "Pacman.h"
#include "Ghost.h"
#include "Fruit.h"

namespace fs = std::filesystem;
using namespace std;

const int GAME_WON = 1;
const int IN_PROGRESS = 0;
const int GAME_OVER = -1;



class Game {

private:
	int mode;
	Board board;
	Pacman pacman;
	vector <Ghost> ghostArr;
	Fruit* fruit = nullptr;
	map <string, int> statusMap;

	set<string> m_screenFiles;
	pair<int, int> m_dataLocation;

	string currFileName;
	vector<int> fileOffsets;// [0] = pacnam, [1] = fruit, [2...] = ghosts

public:
	//Builders
	Game(int gameMode = NORMAL_MODE);
	~Game();

	//Getters
	const int getLives() const { return statusMap.at("Lives"); }
	const int getScore() const { return statusMap.at("Score"); }
	const int getDifficulty() const { return statusMap.at("Difficulty"); }
	const int getCrumbs() const { return statusMap.at("Crumbs"); }
	const int getScreenNum() const { return statusMap.at("Screen"); }

	//Setters
	void setScreenNum(int num) { statusMap["Screen"] = num; }
	void setLives(int lives) { statusMap["Lives"] = lives; }
	void setScore(int score) { statusMap["Score"] = score; }
	void setCrumbs(int crumbs) { statusMap["Crumbs"] = crumbs; }
	void setDataLocation(int x, int y) { m_dataLocation = pair<int, int>(x, y); }

	//Functions
	void menu();
	void printMainMenu();
	void startGame();
	int makeTurn(char direction, int* ghostDirection, int turn, int& fruit_direction);
	void pauseGame();
	bool isValidMovementKey(char input);
	void getNewCoord(char direction, int* x, int* y);
	bool checkWall(char direction, int x, int y);
	void receiveGhostLevel();
	void clearGhostArr();
	void printBoard() { board.printBoard(); }
	void printData();

	//Files
	void load_screen_files();
	void load_screen(int screen_num);
	void load_screen(const string& fileName);
	bool load_next_screen();
	string receiveScreenFile();
	void printControlsMenu();
	const string get_curr_screen_file();
	void LoadFile(const string File_Name);
	static int getRowsFromFile(ifstream& inFile);
	static int getColsFromFile(ifstream& inFile);
	void checkFileCharecter(char c, int row, int col);
	
	//Save mode files - ofir update exe3
	void open_appendix_file(const string& append);
	void write_pacman_to_file(char direction);
	void write_fruit_to_file(int direction, int x, int y);
	void write_ghost_to_file(int direction, int ghostNum);
	void write_event_to_ResFile(int pointOfTime,const string& event);
};
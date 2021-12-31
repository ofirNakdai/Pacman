#define CRT_SECURE_NO_WARNINGS
#pragma once
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <string>

using namespace std;

const int SAVE_MODE = 10;
const int LOAD_MODE = 11;
const int SILENT_LOAD_MODE = 12;
const int NORMAL_MODE = 13;

void clearScreen();
void gotoxy(short row, short col);//Get row and col, put the cursor in the index.
bool is_key_in_fileName(const string& fileName, const string& key);// fuction get a string an a key, returns true if the key axsists in fileName
int get_Game_Mode(char** args, int size);
bool is_equal_string(const string& base, const string& toCheck);
int get_string_size(const char* string);
string delete_screen_from_fileName(const string& fileName);
int getDigitsOfNum(int num);
string convert_int_to_string(int num);





#pragma once
#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <sstream>

using namespace std;

class Field
{
public:

	Field(int f_length = 138, int f_width = 58);

	Field(const Field & other);

	~Field();

	vector<vector<char>> data;
	int f_length, f_width;
	char alive = (char)219;
	char dead = ' ';

};


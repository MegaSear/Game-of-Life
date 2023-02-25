#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <sstream>
#include "Field.h"

using namespace std;


Field::Field(int f_length, int f_width)
	{
		this->f_length = f_length, this->f_width = f_width;
		std::vector<vector<char>> vec(f_width, std::vector<char>(f_length, dead));
		this->data = move(vec);
	};

Field::Field(const Field& other)
	{
		this->f_length = other.f_length;
		this->f_width = other.f_width;
		std::vector<vector<char>> vec(f_width, std::vector<char>(f_length, dead));
		this->data = move(vec);
	};

Field::	~Field()
	{
		this->data.clear();
	};

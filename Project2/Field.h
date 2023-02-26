#pragma once
#include <vector>

class Field
{
public:

	Field(int f_length = 138, int f_width = 58);

	Field(const Field & other);

	~Field();

	std::vector<std::vector<char>> data;
	int f_length, f_width;
	char alive = (char)219;
	char dead = ' ';

};


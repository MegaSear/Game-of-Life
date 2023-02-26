#pragma once
#include <iostream>
#include <vector>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <sstream>
#include "Field.h"

class GUI
{
public:

	GUI();

	~GUI();

	void print_field(Field& field, int len_code);

	void clear_command(Field& field, int& len_code);

	char alive = (char)219;
	char dead = ' ';	
};


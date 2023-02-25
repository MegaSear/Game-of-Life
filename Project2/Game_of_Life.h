#pragma once
#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <sstream>
#include "Field.h"
#include "GUI.h"

using namespace std;

class Game_of_Life
{

public:

	Game_of_Life();

	Game_of_Life(vector<int> B, vector<int> S);

	~Game_of_Life();

	void start();

private:

	Field field;

	GUI gui;

	int check_neighbours(int i, int j);

	void load(string path);

	void load_game(int mode);

	bool mfind(vector<int> v, int key);

	void step_field();

	int handler(string& input, int& len_code);

	vector<int> RB;
	vector<int> RS;

	int Cy = 16;
	int Cx = 12;

	char alive = (char)219;
	char dead = ' ';
};


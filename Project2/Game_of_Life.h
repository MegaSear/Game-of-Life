#pragma once
#include <vector>
#include "Field.h"
#include "GUI.h"

class Game_of_Life
{

public:

	Game_of_Life();

	Game_of_Life(std::vector<char> B, std::vector<char> S);

	~Game_of_Life();

	void start();

private:

	Field field;

	GUI gui;

	int check_neighbours(int i, int j);

	void load_game(int mode);

	bool mfind(std::vector<char> v, int key);

	void step_field();

	int handler(std::string& input, int& len_code);

	Game_of_Life ReadPath(std::string path);

	void DumpGame(std::string path, std::string name);

	std::vector<char> RB;
	std::vector<char> RS;
	std::vector<char> name;

	int Cy = 16;
	int Cx = 12;

	char alive = (char)219;
	char dead = ' ';
};


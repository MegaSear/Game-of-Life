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
#include "Game_of_Life.h"

using namespace std;


Game_of_Life::Game_of_Life()
	{
		this->RB.push_back(3);
		this->RS.push_back(2);
		this->RS.push_back(3);
	};

Game_of_Life::Game_of_Life(std::vector<int> B, std::vector<int> S)
	{
		this->RS = S;
		this->RB = B;
	};

Game_of_Life::	~Game_of_Life()
	{
		RB.clear();
		RS.clear();
	};

	void Game_of_Life::start()
	{
		int len_code = 0;
		std::string code = "pause";
		this->gui.print_field(this->field, len_code);
		while (handler(code, len_code))
		{
			if (_kbhit())
			{
				getline(cin, code);
				len_code = code.size();
				this->gui.clear_command(this->field, len_code);
			}
		}
	}

	int Game_of_Life::check_neighbours(int i, int j)
	{
		int N = 0;
		for (int d = -1; d < 2; d++)
		{
			for (int f = -1; f < 2; f++)
			{
				if (d == 0 and f == 0)
					continue;
				if (this->field.data[((i + d + this->field.f_width) % this->field.f_width)][((j + f + this->field.f_length) % this->field.f_length)] == alive)
					N++;
			}
		}
		return N;
	}

	void Game_of_Life::load(std::string path)
	{
		this->gui.ReadPath(path);
	}

	void Game_of_Life::load_game(int mode)
	{
		switch (mode)
		{
		case 0:
		{
			for (int i = 0; i < this->field.f_width; i++)
			{
				this->field.data[i][0] = alive;
				this->field.data[i][field.f_length - 1] = alive;
			}
			for (int i = 0; i < this->field.f_length; i++)
			{
				this->field.data[0][i] = alive;
				this->field.data[field.f_width - 1][i] = alive;
			}
		}
		}
	}

	bool Game_of_Life::mfind(std::vector<int> v, int key)
	{
		bool result = false;
		for (int i = 0; i < v.size(); i++)
		{
			if (v[i] == key)
			{
				result = true;
				break;
			}
		}
		return result;
	}

	void Game_of_Life::step_field()
	{
		Field field_new(this->field);

		for (int i = 0; i < field_new.f_width; i++)
		{
			for (int j = 0; j < field_new.f_length; j++)
			{
				if (
					(mfind(RS, check_neighbours(i, j)) and field.data[i][j] == alive)
					or
					(mfind(RB, check_neighbours(i, j)) and field.data[i][j] == dead)
					)
					field_new.data[i][j] = alive;
				else
					field_new.data[i][j] = dead;
			}
		}
		this->field = field_new;
	};

	int Game_of_Life::handler(std::string& input, int& len_code)
	{
		istringstream code1{ input };
		vector<string> result;
		while (!code1.eof())
		{
			string substring;
			code1 >> substring;
			result.push_back(substring);
		}
		string code = result[0];

		if (code.compare("quit") == 0)
		{
			return false;
		}
		if (code.compare("start") == 0)
		{
			gui.print_field(this->field, len_code);
			Sleep(10);
			step_field();
		}
		if (code.compare("pause") == 0)
		{
			HWND hwnd = GetConsoleWindow();
			POINT p;
			GetCursorPos(&p);
			ScreenToClient(hwnd, &p);
			int i = p.y * 1080 / 863 / Cy;
			int j = p.x * 1920 / 1535 / Cx;
			if (GetAsyncKeyState(VK_RBUTTON))
			{
				if (not(field.f_width > i and i >= 0 and field.f_length > j and j >= 0))
					return true;

				field.data[i][j] = alive;

				if (GetAsyncKeyState(VK_LCONTROL))
				{
					field.data[i][j] = dead;
				}
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { SHORT(j), SHORT(i) });
				cout << field.data[i][j];
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { SHORT(0), SHORT(field.f_width + 1) });
			}
		}
		if (code.compare("step") == 0)
		{
			for (int i = 0; (result.size() > 1) and (i < stoi(result[1])); i++)
			{
				step_field();
				if ((result.size() == 3) and result[2] == "v")
				{
					gui.print_field(field, len_code);
				}
				Sleep(10);
			}
			gui.print_field(field, len_code);
			input = "pause";
			len_code = input.size();
		}
		if (code.compare("load") == 0)
		{
			string path = "";
			this->load(path);
		}
		result.clear();
		return true;
	};



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


	GUI::GUI()
	{

	};

	GUI::~GUI()
	{

	};

	void GUI::print_field(Field& field, int len_code)
	{
		string res = "";
		for (int i = 0; i < field.f_width; i++)
		{
			for (int j = 0; j < field.f_length; j++)
			{
				res += field.data[i][j];
			}
			res += "\n";
		}
		const char* str = res.c_str();
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { SHORT(0), SHORT(0) });
		cout << str << endl;
	}

	void GUI::clear_command(Field& field, int& len_code)
	{
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { SHORT(0), SHORT(field.f_width + 1) });
		cout << string(len_code, dead) << endl;
		len_code = 0;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { SHORT(0), SHORT(field.f_width + 1) });
	};

	Field GUI::ReadPath(string path)
	{
		string line;
		ifstream in(path);
		Field A;
		if (in.is_open())
		{
			while (getline(in, line))
			{
				cout << line << endl;
			}
		}
		in.close();

		return A;
	};


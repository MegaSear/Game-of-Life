#include "GUI.h"

GUI::GUI()
{

};

GUI::~GUI()
{
};

void GUI::print_field(Field& field, int len_code)
{
	std::string res = "";
	for (int i = 0; i < field.GetWidth(); i++)
	{
		for (int j = 0; j < field.GetLength(); j++)
		{
			res += field.GetCellData(i, j);
		}
		res += "\n";
	}
	const char* str = res.c_str();
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { SHORT(0), SHORT(0) });
	std::cout << str << std::endl;
}

void GUI::clear_command(Field& field, int& len_code)
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { SHORT(0), SHORT(field.GetWidth() + 1) });
	std::cout << std::string(len_code, field.dead) << std::endl;
	len_code = 0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { SHORT(0), SHORT(field.GetWidth() + 1) });
};


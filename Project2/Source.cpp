#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <windows.h>
#include <conio.h>

using namespace std;
int Cy = 16;
int Cx = 12;

class Field
{
public:

	Field(int f_length = 139, int f_width = 58)
	{
		this->era = 0, this->f_length = f_length, this->f_width = f_width;
		vector<vector<char>> vec(f_width, vector<char>(f_length, ' '));
		//	vec[15][15] = 'O';
		this->field = move(vec);
		this->RB.push_back(3);
		this->RS.push_back(2);
		this->RS.push_back(3);
	};

	Field(vector<vector<char>> field, int era, int f_length, int f_width, vector<int> B, vector<int> S)
	{
		this->era, this->f_length, this->f_width = era, f_length, f_width;
		this->field = field;
		for (int i = 0; i < era; i++)
		{
			this->step_field();
		}
		this->RS = S;
		this->RB = B;
	};

	~Field()
	{
		field.clear();
	};

	void step_field()
	{
		vector<vector<char>> field_new = this->field;
		for (int i = 0; i < this->f_width; i++)
		{
			for (int j = 0; j < this->f_length; j++)
			{
				if (mfind(RS, check_neighbours(i, j)) and field[i][j] == 'O')
				{
					field_new[i][j] = 'O';
				}
				else if (mfind(RB, check_neighbours(i, j)) and field[i][j] == ' ')
				{
					field_new[i][j] = 'O';
				}
				else
				{
					field_new[i][j] = ' ';
				}
			}
		}
		this->field = move(field_new);
	};

	int check_neighbours(int i, int j)
	{
		int N = 0;
		for (int d = -1; d < 2; d++)
		{
			for (int f = -1; f < 2; f++)
			{
				if (d == 0 and f == 0)
					continue;
				if (this->field[((i + d + f_width) % f_width)][((j + f + f_length) % f_length)] == 'O')
					N++;
			}
		}
		return N;
	}

	bool mfind(vector<int> v, int key)
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

	vector<vector<char>> field;
	int f_length, f_width;
private:
	long long era;
	vector<int> RB;
	vector<int> RS;
};

void print_field(Field game, int len_code)
{
	string res = "";
	for (int i = 0; i < game.f_width; i++)
	{
		for (int j = 0; j < game.f_length; j++)
		{
			res += game.field[i][j];
		}
		res += "\n";
	}
	const char* str = res.c_str();
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { SHORT(0), SHORT(0) });
	cout << str << endl;
}

void clear_command(Field game, int &len_code)
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { SHORT(0), SHORT(game.f_width + 1) });
	cout << string(len_code, ' ') << endl;
	len_code = 0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { SHORT(0), SHORT(game.f_width + 1) });
}

int handler(Field &game, string &code, int &len_code)
{
	if (code.compare("quit") == 0)
	{
		return false;
	}
	if (code.compare("start") == 0)
	{
		print_field(game, len_code);
		Sleep(10);
		game.step_field();
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
			if (game.f_width > i and i >= 0 and game.f_length > j and j >= 0)
			{
				game.field[i][j] = 'O';
			}
			if (GetAsyncKeyState(VK_LCONTROL) and game.f_width > i and i >= 0 and game.f_length > j and j >= 0)
			{
				game.field[i][j] = ' ';
			}
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { SHORT(j), SHORT(i) });
			cout << game.field[i][j];
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { SHORT(0), SHORT(game.f_width + 1) });
		}
	}
	return true;
}

int main()
{
	Field game;
	int len_code = 0;
	string code = "pause";
	print_field(game, len_code);
	while (handler(game, code, len_code))
	{
		if (_kbhit())
		{
			getline(cin, code);
			len_code = code.size();
			clear_command(game, len_code);
		}
	}
	return 0;
}
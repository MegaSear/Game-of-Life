#include "Game_of_Life.h"

Game_of_Life::Game_of_Life()
{
	this->RB.push_back(3);
	this->RS.push_back(2);
	this->RS.push_back(3);
};

Game_of_Life::Game_of_Life(std::vector<char> B, std::vector<char> S)
{
	this->RS = S;
	this->RB = B;
};

Game_of_Life::~Game_of_Life()
{
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
			getline(std::cin, code);
			len_code = code.size();
			this->gui.clear_command(this->field, len_code);
		}
	}
}

int Game_of_Life::check_neighbours(int i, int j)
{
	int N = 0;
	for (int dy = -1; dy < 2; dy++)
	{
		for (int dx = -1; dx < 2; dx++)
		{
			if (dy == 0 and dx == 0)
				continue;
			if (this->field.GetCellData(((i + dy + this->field.GetWidth()) % this->field.GetWidth()), ((j + dx + this->field.GetLength()) % this->field.GetLength())) == field.alive)
				N++;
		}
	}
	return N;
}

bool Game_of_Life::mfind(std::vector<char> v, int key)
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

bool Game_of_Life::step_field()
{
	Field field_new(this->field);

	for (int i = 0; i < field_new.GetWidth(); i++)
	{
		for (int j = 0; j < field_new.GetLength(); j++)
		{
			if (
				(mfind(RS, check_neighbours(i, j)) and field.GetCellData(i, j) == field.alive)
				or
				(mfind(RB, check_neighbours(i, j)) and field.GetCellData(i, j) == field.dead)
				)
				field_new.SetCellData(i, j, field.alive);
			else
				field_new.SetCellData(i, j, field.dead);
		}
	}
	bool sign = this->field == field_new;
	this->field = field_new;
	return sign;
};

int Game_of_Life::handler(std::string& input, int& len_code)
{
	std::istringstream code1{ input };
	std::vector<std::string> result;
	while (!code1.eof())
	{
		std::string substring;
		code1 >> substring;
		result.push_back(substring);
	}
	std::string code = result[0];

	if (code.compare("clear") == 0)
	{
		for (int x = 0; x < field.GetWidth(); x++)
		{
			for (int y = 0; y < field.GetLength(); y++)
			{
				field.SetCellData(x, y, field.dead);
			}
		}
		gui.print_field(field, len_code);
		input = "pause";
		len_code = input.size();
	}
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
			if (not(field.GetWidth() > i and i >= 0 and field.GetLength() > j and j >= 0))
				return true;

			field.SetCellData(i, j, field.alive);

			if (GetAsyncKeyState(VK_LCONTROL))
			{
				field.SetCellData(i, j, field.dead);
			}
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { SHORT(j), SHORT(i) });
			std::cout << field.GetCellData(i, j);
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { SHORT(0), SHORT(field.GetWidth() + 1) });
		}
	}
	if (code.compare("step") == 0)
	{
		for (int i = 0; (result.size() > 1) and (i < stoi(result[1])); i++)
		{
			std::cout << "Please wait... " << i * 100 / stoi(result[1]) << "%";
			int len = 30;
			bool sgn = step_field();
			if ((result.size() == 3) and result[2] == "v")
			{
				gui.print_field(field, len_code);
			}
			gui.clear_command(this->field, len);
			if (sgn)
				break;
		}
		gui.print_field(field, len_code);
		input = "pause";
		len_code = input.size();
	}
	if (code.compare("dump") == 0)
	{
		input = "pause";
		DumpGame(result[1], result[2]);
		len_code = input.size();
	}
	if (code.compare("load") == 0)
	{
		std::string path = result[1];
		Game_of_Life new_game = ReadPath(path);
		*this = new_game;
		this->start();
		input = "pause";
		len_code = input.size();
	}
	result.clear();
	return true;
};

Game_of_Life Game_of_Life::ReadPath(std::string path)
{
	std::ifstream in(path);
	std::string line;
	Game_of_Life game;
	bool Rules = false;
	bool Comment = false;
	bool Init = false;
	bool Size = false;
	if (in.is_open())
	{
		while (getline(in, line))
		{
			std::istringstream mline{ line };
			std::vector<std::string> result;
			while (!mline.eof())
			{
				std::string substring;
				mline >> substring;
				result.push_back(substring);
			}

			if ((result[0] == "#Life") and !Init)
			{
				if (result[1] == "1.06")
				{
					Init = true;
				}
				else
				{
					std::cout << "Error";
				}
				continue;
			}
			if ((result[0] == "#N") and !Comment)
			{
				std::vector<char>v(line.begin() + 3, line.end() - 1);
				game.name = move(v);
				Comment = true;
				continue;
			}
			if ((result[0] == "#R") and !Rules)
			{
				std::istringstream mmline{ result[1] };
				std::string B, S;
				getline(mmline, B, '/');
				getline(mmline, S, '\n');
				if (B[0] == 'B')
				{
					std::vector<char> v(B.begin() + 1, B.end());
					for (auto el : v)
					{
						game.RB.push_back(el - '0');
					}
				}
				else
				{

				}
				if (S[0] == 'S')
				{
					std::vector<char> v(S.begin() + 1, S.end());
					for (auto el : v)
					{
						game.RS.push_back(el - '0');
					}
				}
				else
				{

				}
				Rules = true;
				continue;
			}
			if ((result[0] == "#S") and !Size)
			{
				game.field = Field(stoi(result[1]), stoi(result[2]));
				continue;
			}
			if (Rules and Comment and Init)
			{
				game.field.SetCellData(stoi(result[0]), stoi(result[1]), field.alive);
				continue;
			}
			else
			{
			}
		}
	}
	else
	{

	}
	in.close();
	return game;
};

void Game_of_Life::DumpGame(std::string path, std::string name)
{
	std::ofstream out;
	out.open(path);
	out << "#Life 1.06\n#N " << name << "\n#R B";

	for (char rule : this->RB)
		out << char(rule + '0');
	out << "/S";
	for (auto rule : this->RS)
		out << char(rule + '0');
	out << "\n";
	out << "#S " << this->field.GetLength() << " " << this->field.GetWidth() << std::endl;

	for (int y = 0; y < this->field.GetLength(); ++y)
	{
		std::cout << "Please wait... " << y * 100 / this->field.GetLength() << "%";
		int len = 30;
		gui.clear_command(this->field, len);
		for (int x = 0; x < this->field.GetWidth(); ++x)
		{
			if (this->field.GetCellData(x, y) == field.alive)
			{
				out << x << " " << y << "\n";
			}
		}
	}
	out.close();
}

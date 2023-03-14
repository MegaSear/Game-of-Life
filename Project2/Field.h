#pragma once
#include <vector>

class Field
{
public:

	Field(int f_length = 138, int f_width = 58);
	Field(const Field& other);
	~Field();
	char alive = (char)219;
	char dead = ' ';
	int GetWidth();
	std::vector<std::vector<char>>GetData();
	int GetLength();
	void SetData(std::vector<std::vector<char>> data);
	void SetLength(int length);
	void SetWidth(int width);
	void SetCellData(int x, int y, char value);
	char GetCellData(int x, int y);
	bool operator==(const Field& other);
private:
	std::vector<std::vector<char>> data;
	int f_length, f_width;
};


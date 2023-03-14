#include "Field.h"

Field::Field(int f_length, int f_width)
{
	this->f_length = f_length, this->f_width = f_width;
	std::vector<std::vector<char>> vec(f_width, std::vector<char>(f_length, dead));
	this->data = move(vec);
};
Field::Field(const Field& other)
{
	this->f_length = other.f_length;
	this->f_width = other.f_width;
	this->data = other.data;
};
Field::	~Field()
{
};
std::vector<std::vector<char>> Field::GetData()
{
	return this->data;
}
int Field::GetLength()
{
	return this->f_length;
}
int Field::GetWidth()
{
	return this->f_width;
}
void Field::SetData(std::vector<std::vector<char>> data)
{
	this->data = data;
}
void Field::SetLength(int length)
{
	this->f_length = length;
}
void Field::SetWidth(int width)
{
	this->f_width = width;
}
void Field::SetCellData(int x, int y, char value)
{
	this->data[x][y] = value;
}
char Field::GetCellData(int x, int y)
{
	return this->data[x][y];
}
bool Field::operator==(const Field &other)
{
	if (other.f_width != this->f_width or other.f_length != this->f_length)
		return false;
	for (int i = 0; i < this->f_width; i++)
	{
		for (int j = 0; j < this->f_length; j++)
		{
			if (this->data[i][j]!=other.data[i][j])
			{
				return false;
			}
		}
	}
	return true;
}

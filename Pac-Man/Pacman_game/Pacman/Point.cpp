// Tomer Newman 318599305
// Roy Shnap 316060151

#include "Point.h"

int Point::getX() const
{
	return x;
}

int Point::getY() const
{
	return y;
}

void Point::setX(int _x)
{
	x = _x;
}

void Point::setY(int _y)
{
	y = _y;
}

void Point::gotoxy(const short x, const short y) const // going to to point (x,y) on the screen
{
	static HANDLE hConsoleOutput = nullptr;
	if (nullptr == hConsoleOutput)
		hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	COORD dwCursorPosition = { y, x };
	std::cout.flush();
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}
bool Point::operator==(const Point& p)const
{
	if (this->x == p.getX() && this->y == p.getY())
		return true;
	return false;
}

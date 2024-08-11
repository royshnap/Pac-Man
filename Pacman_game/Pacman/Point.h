// Tomer Newman 318599305
// Roy Shnap 316060151

#pragma once
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>

class Point {
private:
	int x;
	int y;
public:
	Point() :x(0), y(0) {}; // empty constructor
	Point(int _x, int _y) : x(_x), y(_y) {}; // constructor
	int  getX()const;
	int  getY()const;
	void setX(int _x);
	void setY(int _y);
	void gotoxy(const short x, const short y)const;
	bool operator==(const Point& p)const;
};

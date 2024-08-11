// Tomer Newman 318599305
// Roy Shnap 316060151
//Ex3

#pragma once
#include <vector>
#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include "Point.h"
#include<typeinfo>
#include <fstream>
#include <filesystem>
#include <set>
#include<string>
#include "Files.h"
class Files;
enum { NO_COLOR = 1, COLOR = 2 };
enum { White = 15, Cyan = 11, Blue = 9, Yellow = 6, Red = 12, Pink = 13, Green = 10 }; // colors

using std::vector;

class Board { // this class contains the board and his ingredients and runs the gameplay of the ghosts and the player
private:
	char board[100][100];
	int width, height;

	Point PacPos;
	vector <Point> GhPos;
	vector <Point> Tunnles;
	int fbreedcrumps = 0;
	Point poScoreLives;

public:
	void initBoard(const std::string& s);
	Board(const std::string& s);
	int getWidth()const;
	int getHeight()const;
	void setWidth(int _Width);
	void setHeight(int _Height);
	Point& getPacPoint();
	void setPacPoint(const Point& loc);
	vector <Point>& getGhoPoints();
	const vector <Point>& getTunnles() const;
	const Point& getScoreLivesPoint() const { return poScoreLives; };
	void setScoreLivesPoint(const Point& p) { poScoreLives = p; }
	void FindTunnles();

public:
	char getCharBoard(int x, int y)const;
	void setCharBoard(int x, int y, char ch);
	void printBoard(bool color)const;
	int getBreedCrumps()const;
	void setBreedCrumps(int _breedCrumps);
	void setLegend(Point& legend);
};
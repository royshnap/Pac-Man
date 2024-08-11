#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>
#include <sstream>
#include <string>
#include "Board.h"
class Board;

using std::string;
using std::vector;
using std::ifstream;
class Files
{
	int iteration = 0;
	std::vector<std::string> fnamesVect;
	std::vector<std::string> fstepsVect;
	std::vector<std::string> fresultVect;
	std::vector<int> resultsFile;
	std::vector<int> resultsTest;

public:
	void setVector(ifstream& file);
	static void setVector(ifstream& file, vector<int>& creature);
	static void setBoard(ifstream& file, Board& board);
	friend class Game;
};


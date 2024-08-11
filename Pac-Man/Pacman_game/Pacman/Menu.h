// Tomer Newman 318599305
// Roy Shnap 316060151

#pragma once
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <windows.h>
#include "Game.h"

class Menu
{
public:
	void menu(int argc, char** argv)const;
	void printMenu()const;
	void instructions()const;
	char Difficulty()const;
	bool Color()const;
	bool isLoadSilent(int argc, char** argv)const;
	bool isLoad(int argc, char** argv)const;
	bool isSave(int argc, char** argv)const;
};

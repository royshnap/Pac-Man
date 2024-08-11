// Tomer Newman 318599305
// Roy Shnap 316060151

#pragma once
#include "GameObject.h"
#include "Board.h"
#include "Ghost.h"
#include "PacMan.h"
#include <iostream>

class Fruit :public GameObject // a class for the moving fruit
{
	int timeLeft;
	int val;
public:
	int getTimeLeft()const;
	void setTimeLeft(int _timeLeft);
public:
	Fruit(int _timeLeft = 50, int _val = 5) :GameObject(), timeLeft(_timeLeft), val(_val) { valSetRand(); setColor(Green); };
	virtual ~Fruit() {};
	void valSetRand();
	void SpawnFinder(const Board& gameBoard, const vector <Ghost>& ghosts, const Pacman& player);
	void move(Board& gameBoard, bool color, bool moveInSilent) override; // polymorphism
	int getVal()const;
	static bool SpawnClearFromActors(const Point& newLoc, const Pacman& player, const vector <Ghost>& ghosts);
};

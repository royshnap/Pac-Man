// Tomer Newman 318599305
// Roy Shnap 316060151

#pragma once
#include "Point.h"
#include "GameObject.h"
#include "Board.h"

class Pacman :public GameObject // this class managing the player and the live and score of the player
{
private:
	int   score;
	Point LegendPos;
	int breedCrumps = 0;

public:
	Pacman(const Point& _LegendPos, int _breedCrumps, const int x = 9, const int y = 40) :GameObject('@', STAY, Point{ x,y }, Point{ x,y }), score(0), LegendPos(_LegendPos), breedCrumps(_breedCrumps) { setColor(Yellow); };
	virtual ~Pacman() {};
	int getBreedCrumps()const;
	const Point& getLegendPos()const;
	void setBreedCrumps(int _breedCrumps);
	void beforeMoving(Board& gameBoard, bool isLoadSilent);
	void afterMoving(bool color)const;// cout his symbol with his new location 
	int getScore() const;
	void setScore(const int _score);
	void printStats(bool color, int lives) const; // prints score and live every frame
	void enterTunnle(const Board& gameBoard);
	bool isInTunnle(const Board& gameBoard)const;
	void init(const int _x, const int _y);
	bool isStuck(const Board& gameBoard)const;
public:
	virtual void move(Board& gameBoard, bool color, bool moveInSilent) override;
	void setNewMove(const Board& gameBoard, char move);
	void legitDirection(const Board& gameBoard, const char curDir);
};
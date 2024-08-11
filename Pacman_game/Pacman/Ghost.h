// Tomer Newman 318599305
// Roy Shnap 316060151

#pragma once
#include "Point.h"
#include "GameObject.h"
#include "Board.h"

using std::abs;

class Ghost :public GameObject
{
	int gameMode;
public:
	void move(Board& gameBoard, bool color, bool moveInSilent) override;
	void moveNovice(Board& gameBoard, bool color, bool moveInSilent);
	void moveGood(Board& gameBoard, bool color, bool moveInSilent);
	void moveBest(Board& gameBoard, bool color, bool moveInSilent);
	void Chase(Board& gameBoard);
public:
	Ghost(const char _x, const char _y, int _gameMode = 3) :GameObject('$', UP, Point{ _x,_y }, Point{ _x,_y }), gameMode(_gameMode) { setColor(Pink); };
	virtual ~Ghost() {};
};

// Tomer Newman 318599305
// Roy Shnap 316060151

#pragma once
#include "Point.h"
#include "Board.h"

enum { UP = 119, DOWN = 120, RIGHT = 100, LEFT = 97, STAY = 115 }; // movments 

class GameObject
{
	char  symbol;
	char  direction;
	Point pos;
	Point Spawn; // initial spawn for the object
	int color;
	int gameIndex;
	int gameMode;
protected:
	vector<int>steps;
public:
	GameObject(char _symbol = '@', int _direction = UP, Point _pos = { 1,1 }, Point _spawn = { 0,0 }, int _gameMode = 1, int _color = Red, int _gameIndex = 0);
	virtual ~GameObject() {};
public:
	vector<int>& getSteps() { return steps; }
	bool isStep(char _direction) const;
	void pushStep(int step) { steps.push_back(step); };
	void moveStraight(Board& gameBoard, bool color, bool moveInSilent);
	int getGameMode()const;
	void setGameMode(int _gameMode);
	int getGameIndex() const { return gameIndex; };
	void gameIndexInc() { gameIndex++; };
	int getDirNum(int i) const;
	void loadSteps(ifstream& file);
	char getDirection()const;
	void setDirection(const char _direction);
	char getSymbol()const;
	void setSymbol(const char _symbol);
	const Point& getPoint()const;
	const Point& getSpawn()const;
	void setPoint(const int x, const int y);
	void setSpawn(const Point& p);
	void setSpawn(int x, int y);
	int getColor()const;
	void setColor(int _color);
public:
	void eraseActor(const Board& gameBoard, bool color) const;
	void printActor(bool _color)const;
	void setActor();
	void init(const int _x, const int _y);
	void startOver(const Board& gameBoard, bool color, bool moveInSilent);
	virtual void move(Board& gameBoard, bool color, bool moveInSilent) = 0;
	void randDir();
	void beforeMoving(const Board& gameBoard, bool _color);
	void afterMoving(bool color)const;
	void MoveAStep(const Board& gameBoard, bool color, bool moveInSilent);
	virtual bool isStuck(const Board& gameBoard)const;
};

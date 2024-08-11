// Tomer Newman 318599305
// Roy Shnap 316060151

#include "Fruit.h"

int Fruit::getTimeLeft()const
{
	return timeLeft;
}

int Fruit::getVal() const
{
	return val;
}

void Fruit::setTimeLeft(int _timeLeft)
{
	timeLeft = _timeLeft;
}

void Fruit::SpawnFinder(const Board& gameBoard, const vector <Ghost>& ghosts, const Pacman& player)
{
	if (getGameMode() != 4)
	{
		int x = 0;
		int y = 0;
		Point newLoc;
		do
		{
			x = (rand() % (gameBoard.getHeight() - 1));
			y = (rand() % (gameBoard.getWidth() - 1));
			newLoc = Point(x, y);

		} while (gameBoard.getCharBoard(x, y) != '.' && gameBoard.getCharBoard(x, y) != ' ' && SpawnClearFromActors(newLoc, player, ghosts));
		setSpawn(x, y);
		setPoint(x, y);
		steps.push_back(x);
		steps.push_back(y);
		steps.push_back(val);
		gameIndexInc();
		gameIndexInc();
		gameIndexInc();
	}
	else
	{
		int _x = getDirNum(getGameIndex());
		gameIndexInc();
		int _y = getDirNum(getGameIndex());
		gameIndexInc();
		int _val = getDirNum(getGameIndex());
		gameIndexInc();
		setPoint(_x, _y);
		setSpawn(_x, _y);
		val = _val;
	}
}

bool Fruit::SpawnClearFromActors(const Point& newLoc, const Pacman& player, const vector <Ghost>& ghosts)
{
	for (unsigned int i = 0; i < ghosts.size(); i++)
		if (newLoc == ghosts[i].getPoint())
			return false;
	if (player.getPoint() == newLoc)
		return false;
	return true;
}
void Fruit::valSetRand()
{
	if (getGameMode() != 4)
	{
		val = (rand() % 5) + 5;
		setSymbol('0' + val);
	}
}
void Fruit::move(Board& gameBoard, bool color, bool moveInSilent)
{
	if (getGameMode() == 4)
	{
		if (!isStep(getDirNum(getGameIndex())))
		{
			if (!moveInSilent) eraseActor(gameBoard, color);
			setPoint(getDirNum(getGameIndex()), getDirNum(getGameIndex() + 1));
			gameIndexInc();
			gameIndexInc();
			val = getDirNum(getGameIndex());
			if (val < 5 || val > 9)
				throw "Fruit value isnt between 5 and 9";
			gameIndexInc();
			setDirection(getDirNum(getGameIndex()));
		}
		if (!(GameObject::isStuck(gameBoard)))
			MoveAStep(gameBoard, color, moveInSilent);
		else if (!moveInSilent)
			printActor(color);
		return;
	}
	static int leftSteps = 20;
	if (leftSteps <= 0)
	{
		leftSteps = 20;
		randDir();
	}
	else
		leftSteps--;
	while (GameObject::isStuck(gameBoard))
		randDir();
	MoveAStep(gameBoard, color, moveInSilent);
	setTimeLeft(getTimeLeft() - 1);
}

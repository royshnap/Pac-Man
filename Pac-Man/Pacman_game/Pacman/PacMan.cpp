// Tomer Newman 318599305
// Roy Shnap 316060151

#include <iostream>
#include <iostream>
#include "Pacman.h"
#include "Board.h"

int Pacman::getBreedCrumps()const
{
	return breedCrumps;
}

void Pacman::setBreedCrumps(int _breedCrumps)
{
	breedCrumps = _breedCrumps;
}

void Pacman::beforeMoving(Board& gameBoard, bool isLoadSilent)
{
	getPoint().gotoxy(getPoint().getX(), getPoint().getY());

	if (gameBoard.getCharBoard(getPoint().getX(), getPoint().getY()) == '.') // changes food to space
	{
		gameBoard.setCharBoard(getPoint().getX(), getPoint().getY(), ' ');
		score++;
		breedCrumps--;
		if (!isLoadSilent) std::cout << ' ';
	}
	else if ((gameBoard.getCharBoard(getPoint().getX(), getPoint().getY()) == ' ' || gameBoard.getCharBoard(getPoint().getX(), getPoint().getY()) == '*') && (!isLoadSilent))
	{
		std::cout << ' ';
	}
}

void Pacman::afterMoving(bool color) const
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	Point afterMov = getPoint();
	afterMov.gotoxy(afterMov.getX(), afterMov.getY());
	if (color)
		SetConsoleTextAttribute(hConsole, getColor());
	std::cout << getSymbol();
}

const Point& Pacman::getLegendPos()const
{
	return LegendPos;
}

void Pacman::printStats(bool color, int lives)const
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	getPoint().gotoxy(LegendPos.getX() + 1, LegendPos.getY());
	if (color)
		SetConsoleTextAttribute(hConsole, Red); //prints the remaining lives
	std::cout << "LIVES: " << lives;
	getPoint().gotoxy(LegendPos.getX(), LegendPos.getY());
	if (color)
		SetConsoleTextAttribute(hConsole, Red); //prints the score
	std::cout << "SCORE: " << score;
}


int Pacman::getScore() const
{
	return score;
}

void Pacman::setScore(const int _score)
{
	if (_score >= 0)
		score = _score;
}

void Pacman::enterTunnle(const Board& gameBoard) //prints pacman in the right place after entering tunnle
{
	for (unsigned int i = 0; i < gameBoard.getTunnles().size(); i++)
	{
		if (gameBoard.getTunnles()[i] == getPoint())
		{
			if (getPoint().getX() == 0 && getDirection() == UP)
				setPoint(gameBoard.getHeight() - 1, getPoint().getY());
			else if (getPoint().getX() == gameBoard.getHeight() - 1 && getDirection() == DOWN)
				setPoint(0, getPoint().getY());

			else if (getPoint().getY() == 0 && getDirection() == LEFT)
				setPoint(getPoint().getX(), gameBoard.getWidth() - 1);
			else if (getPoint().getY() == gameBoard.getWidth() - 1 && getDirection() == RIGHT)
				setPoint(getPoint().getX(), 0);
			break;
		}
	}
}

bool Pacman::isInTunnle(const Board& gameBoard) const
{
	for (unsigned int i = 0; i < gameBoard.getTunnles().size(); i++)
		if (getPoint() == gameBoard.getTunnles()[i])
		{
			if (getPoint().getX() == 0 && getDirection() == UP && gameBoard.getCharBoard(gameBoard.getHeight() - 1, getPoint().getY()) != '#')
				return true;
			else if (getPoint().getX() == gameBoard.getHeight() - 1 && getDirection() == DOWN && gameBoard.getCharBoard(0, getPoint().getY()) != '#')
				return true;
			else if (getPoint().getY() == 0 && getDirection() == LEFT && gameBoard.getCharBoard(getPoint().getX(), gameBoard.getWidth() - 1) != '#')
				return true;
			else if (getPoint().getY() == gameBoard.getWidth() - 1 && getDirection() == RIGHT && gameBoard.getCharBoard(getPoint().getX(), 0) != '#')
				return true;
		}

	return false;
}

void Pacman::init(const int _x, const int _y)
{
	setDirection(STAY);
	setPoint(_x, _y);
}

void Pacman::setNewMove(const Board& gameBoard, char move)
{
	char prevDir = getDirection();
	setDirection(move);
	legitDirection(gameBoard, prevDir);
}

void Pacman::legitDirection(const Board& gameBoard, const char curDir) // seting a new legit direction in case of stucking
{
	if (isStuck(gameBoard))
		setDirection(curDir);
}

void Pacman::move(Board& gameBoard, bool color, bool moveInSilent) // moves the player 1 step
{
	Point newPos = getPoint();
	beforeMoving(gameBoard, moveInSilent);
	if (!moveInSilent)
	{
		getPoint().gotoxy(getPoint().getX(), getPoint().getY());
		std::cout << ' ';
	}

	if (isInTunnle(gameBoard))
		enterTunnle(gameBoard);

	else // if pacman dosn't stuck in a wall moves to the right place
	{
		if (getDirection() == UP)
		{
			if (gameBoard.getCharBoard(newPos.getX() - 1, newPos.getY()) != '#' && newPos.getX() != 0)
				setPoint(getPoint().getX() - 1, getPoint().getY());

		}
		if (getDirection() == RIGHT)
		{
			if (gameBoard.getCharBoard(newPos.getX(), newPos.getY() + 1) != '#' && newPos.getY() != gameBoard.getWidth() - 1)
				setPoint(getPoint().getX(), getPoint().getY() + 1);

		}
		if (getDirection() == DOWN)
		{
			if (gameBoard.getCharBoard(newPos.getX() + 1, newPos.getY()) != '#' && newPos.getX() != gameBoard.getHeight() - 1)
				setPoint(getPoint().getX() + 1, getPoint().getY());

		}
		if (getDirection() == LEFT)
		{
			if (gameBoard.getCharBoard(newPos.getX(), newPos.getY() - 1) != '#' && newPos.getY() != 0)
				setPoint(getPoint().getX(), getPoint().getY() - 1);

		}
	}
	if (!moveInSilent)
		afterMoving(color);
	gameBoard.setPacPoint(getPoint());
}

bool Pacman::isStuck(const Board& gameBoard)const
{
	Point newPos = getPoint();
	switch (getDirection())
	{
	case UP:
	{
		return (gameBoard.getCharBoard(newPos.getX() - 1, newPos.getY()) == '#' || newPos.getX() == 0);
		break;
	}
	case LEFT:
	{
		return (gameBoard.getCharBoard(newPos.getX(), newPos.getY() - 1) == '#' || newPos.getY() == 0);
		break;
	}
	case DOWN:
	{
		return (gameBoard.getCharBoard(newPos.getX() + 1, newPos.getY()) == '#' || newPos.getX() == gameBoard.getHeight() - 1);
		break;
	}
	case RIGHT:
	{
		return (gameBoard.getCharBoard(newPos.getX(), newPos.getY() + 1) == '#' || newPos.getY() == gameBoard.getWidth() - 1);
		break;
	}
	case STAY:
		return false;
	default:
		return true;
	}
}
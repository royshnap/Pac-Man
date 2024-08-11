// Tomer Newman 318599305
// Roy Shnap 316060151

#include <iostream>
#include "Ghost.h"

void Ghost::move(Board& gameBoard, bool color, bool moveInSilent)
{
	switch (getGameMode())
	{
	case 1:
	{
		moveNovice(gameBoard, color, moveInSilent);
		break;
	}
	case 2:
	{
		moveGood(gameBoard, color, moveInSilent);
		break;
	}
	case 3:
	{
		moveBest(gameBoard, color, moveInSilent);
		break;
	}
	case 4:
	{
		moveStraight(gameBoard, color, moveInSilent);
		break;
	}
	}

}

void Ghost::moveNovice(Board& gameBoard, bool color, bool moveInSilent)
{
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
}

void Ghost::moveGood(Board& gameBoard, bool color, bool moveInSilent)
{
	static int chaseCounter = 30;
	static int randomCouner = 7;
	if (chaseCounter > 0)
	{
		chaseCounter--;
		Chase(gameBoard);
	}
	else if (randomCouner > 1)
	{
		randomCouner--;
		do
			randDir();
		while (GameObject::isStuck(gameBoard));

	}
	else
	{
		chaseCounter = 30;
		randomCouner = 7;
		do
			randDir();
		while (GameObject::isStuck(gameBoard));
	}
	MoveAStep(gameBoard, color, moveInSilent);

}

void Ghost::moveBest(Board& gameBoard, bool color, bool moveInSilent)
{
	Chase(gameBoard);
	MoveAStep(gameBoard, color, moveInSilent);
}

void Ghost::Chase(Board& gameBoard) // main chasing algorithm for the ghost
{
	int prevDir = getDirection();
	if (getPoint().getX() > gameBoard.getPacPoint().getX())
	{
		setDirection(UP);
		if (isStuck(gameBoard))
		{
			if (getPoint().getY() > gameBoard.getPacPoint().getY())
				setDirection(LEFT);
			else
				setDirection(RIGHT);
		}
	}
	else if (getPoint().getX() < gameBoard.getPacPoint().getX())
	{
		setDirection(DOWN);
		if (isStuck(gameBoard))
		{
			if (getPoint().getY() > gameBoard.getPacPoint().getY())
				setDirection(LEFT);
			else
				setDirection(RIGHT);
		}
	}
	else
	{
		if (getPoint().getY() > gameBoard.getPacPoint().getY())
			setDirection(LEFT);
		else
			setDirection(RIGHT);
	}
	if (isStuck(gameBoard))
		setDirection(prevDir);
	while (isStuck(gameBoard))
		randDir();
}

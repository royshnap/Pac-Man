// Tomer Newman 318599305
// Roy Shnap 316060151

#include "GameObject.h"
GameObject::GameObject(char _symbol, int _direction, Point _pos, Point _spawn, int _gameMode, int _color, int _gameIndex)
	:symbol(_symbol), direction(_direction), pos(_pos), Spawn(_spawn), color(_color), gameIndex(_gameIndex), gameMode(_gameMode) {}

void GameObject::loadSteps(ifstream& file)
{
	Files::setVector(file, steps);
}

bool GameObject::isStep(char _direction) const
{
	return (_direction == UP || _direction == DOWN || _direction == LEFT || _direction == RIGHT || _direction == STAY);
}

int GameObject::getGameMode()const
{
	return gameMode;
}

void GameObject::setGameMode(int _gameMode)
{
	gameMode = _gameMode;
};

int GameObject::getColor()const
{
	return color;
}

char GameObject::getDirection()const
{
	return direction;
}

void GameObject::setColor(int _color)
{
	color = _color;
}

void GameObject::setDirection(const char _direction)
{
	if (_direction == 'w' || _direction == 'W' || _direction == UP)
		direction = UP;
	else if (_direction == 'a' || _direction == 'A' || _direction == LEFT)
		direction = LEFT;
	else if (_direction == 'd' || _direction == 'D' || _direction == RIGHT)
		direction = RIGHT;
	else if (_direction == 's' || _direction == 'S' || _direction == DOWN)
		direction = DOWN;
	else if (_direction == 'f' || _direction == 'F' || _direction == STAY)
		direction = STAY;

}

char GameObject::getSymbol()const
{
	return symbol;
}

void GameObject::setSymbol(const char _symbol)
{
	symbol = _symbol;
}

const Point& GameObject::getPoint() const
{
	return pos;
}

const Point& GameObject::getSpawn() const
{
	return Spawn;
}

void GameObject::setPoint(const int _x, const int _y)
{
	if (gameMode == 4 && (_x < 0 || _x > 25 || _y < 0 || _y > 80))
		throw "location is not in the board";
	pos.setX(_x);
	pos.setY(_y);
}

void GameObject::eraseActor(const Board& gameBoard, bool color) const
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	getPoint().gotoxy(getPoint().getX(), getPoint().getY());
	if (gameBoard.getCharBoard(getPoint().getX(), getPoint().getY()) == ' ')
		std::cout << " ";
	else
	{
		if (color)
			SetConsoleTextAttribute(hConsole, Cyan);
		std::cout << ".";
	}

}

void GameObject::printActor(bool _color)const
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (_color)
		SetConsoleTextAttribute(hConsole, this->color);
	getPoint().gotoxy(getPoint().getX(), getPoint().getY());
	std::cout << getSymbol();

}

int GameObject::getDirNum(int i) const
{
	if (i >= steps.size())
		throw "Number of Steps is too Short";

	else return steps[i];
};

void GameObject::setActor()
{
	init(getSpawn().getX(), getSpawn().getY());
}

void GameObject::init(const int _x, const int _y)
{
	setDirection(STAY);
	setPoint(_x, _y);
}

void GameObject::startOver(const Board& gameBoard, bool color, bool moveInSilent)// if pacman loses a life, return the actors to their places
{
	if (!moveInSilent)
		eraseActor(gameBoard, color);
	setActor();
	if (!moveInSilent)
		printActor(color);
}
void GameObject::setSpawn(const Point& p)
{
	Spawn = p;
}

void GameObject::setSpawn(int x, int y)
{
	Spawn.setX(x);
	Spawn.setY(y);
}

void GameObject::randDir()
{
	char dir = UP;
	int randDir = (rand() % 4);
	switch (randDir)
	{
	case 0: dir = UP;    break;
	case 1: dir = RIGHT; break;
	case 2: dir = DOWN;  break;
	case 3: dir = LEFT;  break;
	}
	setDirection(dir);
}

void GameObject::beforeMoving(const Board& gameBoard, bool _color)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	getPoint().gotoxy(getPoint().getX(), getPoint().getY());
	if (gameBoard.getCharBoard(getPoint().getX(), getPoint().getY()) == '.')// dosn't runs over the food
	{
		if (_color)
			SetConsoleTextAttribute(hConsole, Cyan);//light blue
		std::cout << '.';
	}
	else
	{
		std::cout << ' ';
	}
	SetConsoleTextAttribute(hConsole, White);
}

void GameObject::afterMoving(bool color)const
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	getPoint().gotoxy(getPoint().getX(), getPoint().getY());
	if (color)
		SetConsoleTextAttribute(hConsole, getColor());
	std::cout << getSymbol();
}
void GameObject::MoveAStep(const Board& gameBoard, bool color, bool moveInSilent)
{
	if (!moveInSilent)
		beforeMoving(gameBoard, color);
	switch (getDirection())
	{
	case UP:
	{
		setPoint(getPoint().getX() - 1, getPoint().getY());
		break;
	}
	case LEFT:
	{
		setPoint(getPoint().getX(), getPoint().getY() - 1);
		break;
	}
	case DOWN:
	{
		setPoint(getPoint().getX() + 1, getPoint().getY());
		break;
	}
	case RIGHT:
	{
		setPoint(getPoint().getX(), getPoint().getY() + 1);
		break;
	}
	}
	if (!moveInSilent)
		afterMoving(color);
}
bool GameObject::isStuck(const Board& gameBoard)const
{
	const Point newPos = getPoint();
	switch (getDirection())
	{
	case UP:
	{
		return (gameBoard.getCharBoard(newPos.getX() - 1, newPos.getY()) == '#' || gameBoard.getCharBoard(newPos.getX() - 1, newPos.getY()) == '*' || newPos.getX() == 0);
		break;
	}
	case LEFT:
	{
		return ((gameBoard.getCharBoard(newPos.getX(), newPos.getY() - 1) == '#') || (gameBoard.getCharBoard(newPos.getX(), newPos.getY() - 1) == '*' || newPos.getY() == 0));
		break;
	}
	case DOWN:
	{
		return ((gameBoard.getCharBoard(newPos.getX() + 1, newPos.getY()) == '#') || (gameBoard.getCharBoard(newPos.getX() + 1, newPos.getY()) == '*' || newPos.getX() == gameBoard.getHeight() - 1));
		break;
	}
	case RIGHT:
	{
		return ((gameBoard.getCharBoard(newPos.getX(), newPos.getY() + 1) == '#') || (gameBoard.getCharBoard(newPos.getX(), newPos.getY() + 1) == '*' || newPos.getY() == gameBoard.getWidth() - 1));
		break;
	}
	default:
		return true;
	}
}
void GameObject::moveStraight(Board& gameBoard, bool color, bool moveInSilent)
{
	if (!GameObject::isStuck(gameBoard))
		MoveAStep(gameBoard, color, moveInSilent);
	else if (!moveInSilent)
		printActor(color);
}
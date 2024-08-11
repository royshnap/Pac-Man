// Tomer Newman 318599305
// Roy Shnap 316060151

#include "Board.h"

int Board::getWidth()const
{
	return width;
}

int Board::getBreedCrumps()const
{
	return fbreedcrumps;
}

void Board::setBreedCrumps(int _breedcrumps)
{
	fbreedcrumps = _breedcrumps;
}

int Board::getHeight()const
{
	return height;
}

Point& Board::getPacPoint()
{
	return PacPos;
};

void Board::setPacPoint(const Point& loc)
{
	PacPos = loc;
};

vector <Point>& Board::getGhoPoints()
{
	return GhPos;
}
const vector <Point>& Board::getTunnles() const
{
	return Tunnles;
}
void Board::setCharBoard(int x, int y, char ch)
{
	board[x][y] = ch;
}
void Board::setWidth(int _Width)
{
	width = _Width;
}
void Board::setHeight(int _Height)
{
	if (_Height > 25) // If the height is greater than 25 chars take only first 25 chars
	{
		_Height = 25;
	}
	height = _Height;
}
void Board::initBoard(const std::string& name)
{
	std::ifstream file(name);
	Files::setBoard(file, *this);
	setLegend(poScoreLives);
	for (int l = 0; l < width && height >= 1; l++)
	{
		if (board[0][l] == '.')
		{
			board[0][l] = '*';
			fbreedcrumps--;
		}
		if (board[height - 1][l] == '.')
		{
			board[height - 1][l] = '*';
			fbreedcrumps--;
		}
		board[height][l] = '#';
	}

	for (int l = 0; l < height && width >= 1; l++)
	{
		if (board[l][0] == '.')
		{
			board[l][0] = '*';
			fbreedcrumps--;
		}
		if (board[l][width - 1] == '.')
		{
			board[l][width - 1] = '*';
			fbreedcrumps--;
		}
		board[l][width] = '#';
	}
	FindTunnles();
}

void Board::setLegend(Point& legend)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (board[i + legend.getX()][j + legend.getY()] == '.')
				fbreedcrumps--;
			if (board[i + legend.getX()][j + legend.getY()] != ' ' && board[i + legend.getX()][j + legend.getY()] != '*')
				board[i + legend.getX()][j + legend.getY()] = ' ';
		}
	}
}

void Board::FindTunnles()
{
	for (int i = 0; i < width; i++)
	{
		if (board[0][i] == ' ' || board[0][i] == '*')
		{
			if (board[height - 1][i] == ' ' || board[height - 1][i] == '*')
			{
				Point tunnle(0, i);
				Tunnles.push_back(tunnle);
			}
		}
		if (board[height - 1][i] == ' ' || board[height - 1][i] == '*')
		{
			if (board[0][i] == ' ' || board[0][i] == '*')
			{
				Point tunnle(height - 1, i);
				Tunnles.push_back(tunnle);
			}
		}
	}
	for (int i = 0; i < height; i++)
	{
		if (board[i][0] == ' ' || board[i][0] == '*')
		{
			if ((width > 0) && (board[i][width - 1] == ' ' || board[i][width - 1] == '*'))
			{
				Point tunnle(i, 0);
				Tunnles.push_back(tunnle);
			}
		}
		if ((width > 0) && (board[i][width - 1] == ' ' || board[i][width - 1] == '*'))
		{
			if (board[i][0] == ' ' || board[i][0] == '*')
			{
				Point tunnle(i, width - 1);
				Tunnles.push_back(tunnle);
			}
		}
	}
}

void Board::printBoard(bool color)const
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (color)
			{
				switch (board[i][j])
				{
				case '#': {SetConsoleTextAttribute(hConsole, Blue); break; } // blue
				case '.': {SetConsoleTextAttribute(hConsole, Cyan); break; } // light blue		
				}
			}
			if (board[i][j] == '*')
				std::cout << ' ';
			else
				std::cout << board[i][j];
		}
		std::cout << std::endl;
	}
	SetConsoleTextAttribute(hConsole, White);
}

Board::Board(const std::string& name)
{
	initBoard(name);;
}

char Board::getCharBoard(int x, int y)const
{
	if ((x >= 0 && x <= height - 1) && (y >= 0 && y <= width - 1))
	{
		return board[x][y];
	}
	return ' ';
}

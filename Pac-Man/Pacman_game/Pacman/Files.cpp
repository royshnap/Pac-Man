#include "Files.h"

void Files::setVector(ifstream& file, vector<int>& creature)
{
	string line;
	getline(file, line);
	std::istringstream input(line);
	std::string word;
	while (input >> word)
	{
		int number = std::stoi(word);
		creature.push_back(number);
	}
}

void Files::setVector(ifstream& file)
{
	string line;
	getline(file, line);
	std::istringstream input(line);
	std::string word;
	while (input >> word)
	{
		int number = std::stoi(word);
		resultsFile.push_back(number);
	}
}

void Files::setBoard(ifstream& file, Board& board)
{
	int logwidth, newlogwidth = 0;
	bool flag = false;
	char ch = ' ';
	board.setHeight(1);
	board.setWidth(1);
	std::string  firstline;
	getline(file, firstline);
	logwidth = firstline.length();
	if (logwidth > 80) //If the width is greater than 80 chars take only first 80 chars
	{
		logwidth = 80;
	}
	for (int k = 0; k <= logwidth; k++) // handling first line
	{
		board.setCharBoard(0, k, firstline[k]);
		switch (firstline[k])
		{
		case '%':
		{
			board.setCharBoard(0, k, ' ');
			break;
		}
		case '&':
		{
			if (k + 20 > logwidth)
				newlogwidth = k + 20;
			board.setScoreLivesPoint(Point(0, k));
			break;
		}
		case ' ':
		{
			board.setCharBoard(0, k, '.');
			board.setBreedCrumps(board.getBreedCrumps() + 1);
			break;
		}
		case '$':
		{
			board.setCharBoard(0, k, '.');
			board.setBreedCrumps(board.getBreedCrumps() + 1);
			board.getGhoPoints().push_back(Point(0, k));
			break;
		}
		case '@':
		{
			board.setCharBoard(0, k, '.');
			board.setBreedCrumps(board.getBreedCrumps() + 1);
			board.getPacPoint() = Point(0, k);
			break;
		}
		default: // In case of an unknown character put wall
		{
			board.setCharBoard(0, k, '#');
			break;
		}
		}
	}

	logwidth = static_cast<int>(std::fmax(newlogwidth, logwidth)); // first line length
	board.setWidth(logwidth);

	while (!file.eof())
	{
		for (int j = 0; j <= logwidth; j++)
		{
			file.get(ch);
			switch (ch)
			{
			case'#':
			{
				board.setCharBoard(board.getHeight(), j, '#');
				break;
			}
			case '\n':
			{
				while (j <= logwidth)
				{
					board.setCharBoard(board.getHeight(), j, ' ');
					j++;
				}
				board.setHeight(board.getHeight() + 1);
				break;
			}
			case '$':
			{
				board.setCharBoard(board.getHeight(), j, '.');
				board.setBreedCrumps(board.getBreedCrumps() + 1);
				board.getGhoPoints().push_back(Point(board.getHeight(), j));
				break;
			}
			case '@':
			{
				board.setCharBoard(board.getHeight(), j, '.');
				board.setBreedCrumps(board.getBreedCrumps() + 1);
				board.setPacPoint(Point(board.getHeight(), j));
				break;
			}
			case '%':
			{
				board.setCharBoard(board.getHeight(), j, ' ');
				break;
			}
			case'&':
			{
				board.setCharBoard(board.getHeight(), j, ' ');
				board.setScoreLivesPoint(Point(board.getHeight(), j));
				break;
			}
			case ' ':
			{
				board.setCharBoard(board.getHeight(), j, '.');
				board.setBreedCrumps(board.getBreedCrumps() + 1);
				break;
			}
			default: // In case of an unknown character put a wall
			{
				board.setCharBoard(board.getHeight(), j, '#');
				break;
			}
			}
		}
		if (ch != '\n')
		{
			std::getline(file, firstline); // "swallows" the remaining line if the line is too big
			board.setHeight(board.getHeight() + 1);
		}
	}
}
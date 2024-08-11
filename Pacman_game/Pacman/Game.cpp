// Tomer Newman 318599305
// Roy Shnap 316060151

#include "Game.h"

bool Game::getColor()const
{
	return color;
}

void Game::setColor(bool _color)
{
	color = _color;
}

char Game::getDifficulty() const
{
	return difficulty;
}

void Game::startFromLoad(Board& gameBoard)
{
	fileVar.resultsFile.clear();
	Pacman player(gameBoard.getScoreLivesPoint(), gameBoard.getBreedCrumps(), gameBoard.getPacPoint().getX(), gameBoard.getPacPoint().getY());
	Fruit fruit;
	vector <Ghost> ghosts;
	vector <GameObject*> Actors;
	for (unsigned int i = 0; i < gameBoard.getGhoPoints().size(); i++)
		ghosts.push_back(Ghost(gameBoard.getGhoPoints()[i].getX(), gameBoard.getGhoPoints()[i].getY()));
	bool GhostMoveAlso = true;
	std::ifstream fileName(fileVar.fnamesVect[fileVar.iteration]);
	std::ifstream resFile(fileVar.fresultVect[fileVar.iteration]);
	std::ifstream resSteps(fileVar.fstepsVect[fileVar.iteration]);
	if (load && !silent && (!resFile.good()) || (!resSteps.good()))
		throw "Please check for the Result/Steps files";
	Files::setVector(resFile, fileVar.resultsFile);
	if (!(silent && load))
		gameBoard.printBoard(color);
	Actors.push_back(&player);
	Actors.push_back(&fruit);
	for (unsigned int i = 0; i < ghosts.size(); i++)
		Actors.push_back(&(ghosts[i]));
	if (Actors.size() == 0)
	{
		std::cout << "the are no result files" << std::endl;
		return;
	}
	for (unsigned int i = 0; i < Actors.size(); i++) // initializing the STEPS vectors! first is pacman, second is fruit and else is Ghosts!
	{
		Files::setVector(resSteps, Actors[i]->getSteps());
		Actors[i]->setGameMode(4);
	}
	numOfFrames = 0;
	while (lives > 0 && player.getBreedCrumps() > 0)
	{
		Sleep(sleepTimer);
		numOfFrames++;
		if (GhostMoveAlso)
		{
			for (unsigned int i = 0; i < Actors.size(); i++)
			{
				try { Actors[i]->setDirection(Actors[i]->getDirNum(Actors[i]->getGameIndex())); }
				catch (const char* msg)
				{
					throw msg;
					return;
				}
				MeetUp(gameBoard, player, ghosts, fruit, Actors);
				Actors[i]->move(gameBoard, color, (silent && load));
				Actors[i]->gameIndexInc();
				MeetUp(gameBoard, player, ghosts, fruit, Actors);

			}

			GhostMoveAlso = false;
		}
		else
		{
			try { Actors[0]->setDirection(Actors[0]->getDirNum(Actors[0]->getGameIndex())); }
			catch (const char* msg)
			{
				if (silent && load)
					throw "Test Faild";
				else
					throw msg;
				return;
			}
			Actors[0]->move(gameBoard, color, (silent && load));
			MeetUp(gameBoard, player, ghosts, fruit, Actors);
			Actors[0]->gameIndexInc();
			GhostMoveAlso = true;
		}
		if (!(silent && load))player.printStats(color, lives);
	}
	fileVar.resultsTest.push_back(numOfFrames);
	if (player.getBreedCrumps() <= 0 && !load) // if winning
	{
		youWon();
		_getch();
	}
	else if (!load)
	{
		youLost();
		_getch();
	}
	try { TestPassed(fileVar.resultsTest, fileVar.resultsFile); }
	catch (const char* msg)
	{
		throw msg;
	}
	if (lives <= 0 && load && !silent)
		throw "You Lost";
}

void Game::TestPassed(vector<int>& v1, vector <int>& v2)
{
	if (silent == true)
	{
		if (v1 == v2)
			return;
		else
			throw "Test Failed";
	}
}

void Game::start(Board& gameBoard)//this func runs the entire game 
{
	system("CLS");
	Pacman player(gameBoard.getScoreLivesPoint(), gameBoard.getBreedCrumps(), gameBoard.getPacPoint().getX(), gameBoard.getPacPoint().getY());
	Fruit fruit;
	vector <Ghost> ghosts;
	vector <GameObject*> Actors;
	for (unsigned int i = 0; i < gameBoard.getGhoPoints().size(); i++)
		ghosts.push_back(Ghost(gameBoard.getGhoPoints()[i].getX(), gameBoard.getGhoPoints()[i].getY()));
	for (unsigned int i = 0; i < ghosts.size(); i++)
		ghosts[i].setGameMode(getDifficulty() - '0');
	bool GhostMoveAlso = true;
	setNewFruit(gameBoard, fruit, ghosts, player);
	gameBoard.printBoard(color);
	Actors.push_back(&player);
	Actors.push_back(&fruit);
	for (unsigned int i = 0; i < ghosts.size(); i++)
		Actors.push_back(&(ghosts[i]));
	numOfFrames = 0;
	while (lives > 0 && player.getBreedCrumps() > 0)// runs until game over
	{
		Sleep(sleepTimer);
		numOfFrames++;
		if (_kbhit())
		{
			char ch = _getch();
			if (ch == ESC) // if the game paused
			{
				Pause(gameBoard);
				while (_getch() != ESC);
				Continue(gameBoard);
				continue;
			}
			else
				player.setNewMove(gameBoard, ch);
		}

		if (fruit.getTimeLeft() <= 0)
		{
			if (!(silent && load)) fruit.eraseActor(gameBoard, color);
			setNewFruit(gameBoard, fruit, ghosts, player);
		}
		if (GhostMoveAlso)
		{
			for (unsigned int i = 0; i < Actors.size(); i++)
			{
				MeetUp(gameBoard, player, ghosts, fruit, Actors);
				Actors[i]->move(gameBoard, color, (silent && load));
				if (save)
					Actors[i]->pushStep(Actors[i]->getDirection());
				MeetUp(gameBoard, player, ghosts, fruit, Actors);
			}
			GhostMoveAlso = false;
		}
		else
		{
			Actors[0]->move(gameBoard, color, (silent && load));
			if (save)
				Actors[0]->pushStep(Actors[0]->getDirection());
			MeetUp(gameBoard, player, ghosts, fruit, Actors);
			GhostMoveAlso = true;
		}
		player.printStats(color, lives);
	}
	if (save)
		fileVar.resultsTest.push_back(numOfFrames);
	if (player.getBreedCrumps() <= 0) // if winning
	{
		youWon();
		_getch();
	}
	else
	{
		youLost();
		_getch();
	}
	saveToFiles(Actors);
}

void Game::Pause(const Board& gameBoard) const
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (color == true)
		SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN);//green
	gameBoard.getScoreLivesPoint().gotoxy(gameBoard.getScoreLivesPoint().getX() + 2, gameBoard.getScoreLivesPoint().getY());
	std::cout << "PAUSED";
	SetConsoleTextAttribute(hConsole, White);
}

void Game::Continue(const Board& gameBoard) const // continue after pause
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, White);
	gameBoard.getScoreLivesPoint().gotoxy(gameBoard.getScoreLivesPoint().getX() + 2, gameBoard.getScoreLivesPoint().getY());
	std::cout << "      ";
}

void Game::youLost()
{
	system("cls");
	_flushall();
	Point winMes(WIN_MES_POS);
	Point escMes(ESC_MES_POS);
	escMes.gotoxy(escMes.getX(), escMes.getY());
	std::cout << "To Proceed press any key" << std::endl;
	winMes.gotoxy(winMes.getX(), winMes.getY());
	std::cout << "You Lost" << std::endl;
	lost = true;
	while (!_kbhit());
}

void Game::youWon() const
{
	system("cls");
	_flushall();
	Point winMes(WIN_MES_POS);
	Point escMes(ESC_MES_POS);
	escMes.gotoxy(escMes.getX(), escMes.getY());
	std::cout << "To Proceed press any key" << std::endl;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	while (!_kbhit())
	{
		Sleep(sleepTimer);
		winMes.gotoxy(winMes.getX(), winMes.getY());
		if (color)
			SetConsoleTextAttribute(hConsole, ((rand() % White) + 1));
		std::cout << "You Passed The Screen!" << std::endl;
	}
	SetConsoleTextAttribute(hConsole, White);
}

bool Game::isPacMeetsGhost(const Pacman& player, const vector <Ghost>& ghosts)const
{
	for (vector<Ghost>::const_iterator ptr = ghosts.begin(); ptr < ghosts.end(); ptr++)
		if (player.getPoint() == ptr->getPoint())
			return true;
	return false;
}

void Game::MeetUp(const Board& board, Pacman& player, vector <Ghost>& ghosts, Fruit& fruit, vector <GameObject*>& Actors)
{
	if (isPacMeetsGhost(player, ghosts) == true)
	{
		lives--;
		if (player.getGameMode() == 4 || save)
			fileVar.resultsTest.push_back(numOfFrames);
		for (unsigned int i = 0; i < ghosts.size(); i++)
		{
			if (!(silent && load)) ghosts[i].eraseActor(board, color);
			ghosts[i].setActor();
			if (!(silent && load))  ghosts[i].printActor(color);
		}
		if (!(silent && load)) player.eraseActor(board, color);
		player.setActor();
		player.printActor(color);
		if (!(silent && load)) fruit.eraseActor(board, color);
		setNewFruit(board, fruit, ghosts, player);
		if (!(silent && load))fruit.printActor(color);
	}
	else if (isPacMeetsFruit(player, fruit) == true)
	{
		player.setScore(player.getScore() + fruit.getVal());
		setNewFruit(board, fruit, ghosts, player);
	}
	else if (isGhostMeetsFruit(ghosts, fruit) == true)
		setNewFruit(board, fruit, ghosts, player);
}

bool Game::isPacMeetsFruit(const Pacman& player, Fruit& fruit)const
{
	if (player.getPoint() == fruit.getPoint())
		return true;
	return false;
}

bool Game::isGhostMeetsFruit(const vector <Ghost>& ghosts, const Fruit& fruit)const
{
	for (unsigned int i = 0; i < ghosts.size(); i++)
		if (ghosts[i].getPoint() == fruit.getPoint())
			return true;
	return false;

}

void Game::setNewFruit(const Board& board, Fruit& fruit, const vector <Ghost>& ghosts, const Pacman& player)const
{
	fruit.valSetRand();
	fruit.SpawnFinder(board, ghosts, player);
	fruit.setTimeLeft(50);
}

void Game::LoadFiles()
{

	for (unsigned int i = 0; i < fileVar.fnamesVect.size(); i++)
	{
		system("CLS");
		Board board(fileVar.fnamesVect[i]);
		try
		{
			if (difficulty == 4)
				startFromLoad(board);
			else
			{
				start(board);
				if (lost == true)
					break;
			}
		}
		catch (const char* msg)
		{
			system("cls");
			if (silent && load)
				std::cout << "Test Faild";
			else
				std::cout << msg;
			return;
		}
		fileVar.iteration++;
	}
	if (difficulty == 4)
	{
		system("cls");
		if (silent)
			std::cout << "Test Passed" << std::endl;

		return;
	}
}

void Game::saveToFiles(vector <GameObject*> Actors)
{
	std::fstream writeFileSteps(fileVar.fstepsVect[fileVar.iteration], std::ios::trunc | std::ios::out);
	std::fstream writeFileResult(fileVar.fresultVect[fileVar.iteration], std::ios::trunc | std::ios::out);
	int pacStepsSize = Actors[0]->getSteps().size();
	int fruitStepsSize = Actors[1]->getSteps().size();
	for (int i = 0; i < pacStepsSize; i++)
		writeFileSteps << Actors[0]->getSteps()[i] << " ";

	writeFileSteps << std::endl;
	for (int i = 0; i < fruitStepsSize; i++)
		writeFileSteps << Actors[1]->getSteps()[i] << " ";

	writeFileSteps << std::endl;
	for (int i = 2; i < Actors.size(); i++)
	{
		for (int j = 0; j < Actors[i]->getSteps().size(); j++)
		{
			writeFileSteps << Actors[i]->getSteps()[j] << " ";
		}
		writeFileSteps << std::endl;
	}
	for (int i = 0; i < fileVar.resultsTest.size(); i++)
	{
		writeFileResult << fileVar.resultsTest[i] << " ";
	}
}

void Game::LoadAFile()
{
	std::string name;
	std::vector <std::string> tempVect;
	system("cls");
	_flushall();
	std::cout << "Please enter the file name:" << std::endl;
	std::cin >> name;

	for (unsigned int i = 0; i < fileVar.fnamesVect.size();)
	{
		if (name != fileVar.fnamesVect[i])
		{
			i++;
		}
		else
		{
			fileVar.iteration = i;
			Board gameBoard(name);
			start(gameBoard);
			break;
		}
		if (i == fileVar.fnamesVect.size())
		{
			std::cout << "There is no such file, please enter another file, else to return please write 1" << std::endl;
			std::cin >> name;
			i = 0;
		}
		if (name == "1")
			break;
	}
}

bool Game::setFiles()
{
	bool areFiles = false;
	std::string currPathName = fs::current_path().string();
	int isFoundName = -1; //start as false
	int isFoundSteps = -1; //start as false
	int isFoundResult = -1; //start as false
	std::set<string> setOfPathNames;
	std::set<string> setOfPathSteps;
	std::set<string> setOfPathResult;
	int numFiles = 0;
	for (auto& entry : fs::directory_iterator(currPathName))
	{
		isFoundName = entry.path().string().find(".screen");

		if (isFoundName != -1)
		{
			std::string base_filename = entry.path().string().substr(entry.path().string().find_last_of("/\\") + 1);
			setOfPathNames.insert(base_filename);
			base_filename = base_filename.substr(0, 9);
			base_filename += ".steps";
			setOfPathSteps.insert(base_filename);
			base_filename = base_filename.substr(0, 9);
			base_filename += ".result";
			setOfPathResult.insert(base_filename);
			isFoundName = -1;
		}
	}
	for (auto& filename : setOfPathNames)
		fileVar.fnamesVect.push_back(filename);

	for (auto& filename : setOfPathSteps)
		fileVar.fstepsVect.push_back(filename);

	for (auto& filename : setOfPathResult)
		fileVar.fresultVect.push_back(filename);

	if (fileVar.fnamesVect.empty())
	{
		areFiles = false;
		return areFiles;
	}
	else
	{
		areFiles = true;
		return areFiles;
	}
}

int Game::getLives() const
{
	return lives;
}

void Game::setLives(const int _lives)
{
	lives = _lives;
}
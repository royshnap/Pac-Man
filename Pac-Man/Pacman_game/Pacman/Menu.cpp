// Tomer Newman 318599305
// Roy Shnap 316060151

#include "Menu.h"

bool Menu::isLoadSilent(int argc, char** argv)const
{
	return (argc == 3 && std::strcmp(argv[1], "-load") == 0 && (std::strcmp(argv[2], "-silent") == 0));
}

bool Menu::isLoad(int argc, char** argv)const
{
	return (argc == 2 && std::strcmp(argv[1], "-load") == 0);
}

bool Menu::isSave(int argc, char** argv)const // plus save silent
{
	return ((argc == 2 && std::strcmp(argv[1], "-save") == 0) || (argc == 3 && std::strcmp(argv[1], "-save") == 0 && std::strcmp(argv[2], "-silent") == 0));
}

void Menu::menu(int argc, char** argv)const
{
	system("cls");
	if (isLoadSilent(argc, argv))
	{
		Game game(true, true, false, 4, false, 0);
		game.setFiles();
		game.LoadFiles();
		return;
	}
	else if (isLoad(argc, argv))
	{
		Game game(true, false, false, 4, false, 130);
		game.setFiles();
		game.LoadFiles();
		return;
	}
	else
	{
		bool toSave = false;
		if (isSave(argc, argv))
			toSave = true;
		if (argc != 1 && toSave == false)
		{
			std::cout << "Plaese choose only regular mode or save/load mode!" << std::endl << "The format is: -save/-load as first argument and -silent as a second argument for load!" << std::endl;
			return;
		}
		_flushall();
		srand(time(nullptr)); // once per program run
		printMenu();
		if (isSave(argc, argv))
			toSave = true;
		while (!_kbhit())
		{
			switch (_getch())
			{
			case ESC:
			{
				return;
			}
			case EXIT:
			{
				return;
			}
			case LOAD_ALL_FILES:
			{
				Game game(false, true, Color(), Difficulty(), toSave);
				if (game.setFiles() == false)
				{
					printMenu();
					std::cout << "There are no screen files" << std::endl;
					break;
				}
				game.LoadFiles();
				printMenu();
				continue;
			}
			case LOAD_A_FILE:
			{
				if (toSave)
				{
					printMenu();
					std::cout << "Can not play Single File mode with SAVE on!" << std::endl;
					break;
				}
				Game game(false, true, Color(), Difficulty(), false);
				if (game.setFiles() == false)
				{
					printMenu();
					std::cout << "There are no screen files" << std::endl;
					break;
				}
				game.LoadAFile();
				printMenu();
				continue;
			}
			case INSTRUCTIONS:
			{
				instructions();
				printMenu();
				break;
			}
			}
		}
	}
}

void Menu::printMenu() const
{
	system("cls");
	_flushall();
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, White);
	std::cout << "Welome to Pacman!" << std::endl << "(1) Start all games" << std::endl << "(2) Start a single game" << std::endl << "(8) Present instructions and keys" << std::endl << "(9) EXIT" << std::endl;
}

void Menu::instructions() const
{
	system("CLS");
	//instructions
	std::cout << "Instructions:" << std::endl << std::endl << "You are Pacman (marked @)!\n" << "your goal is to eat all the breedcrumps(marked .)." << std::endl;
	std::cout << "Watch out from the Ghosts (marked $)!\n" << "if they touch you, you will lose a life, you got only 3!" << std::endl;
	//keys
	std::cout << std::endl << "KEYS:" << std::endl;
	std::cout << "Up -> w/W" << std::endl << "Left -> a/A" << std::endl << "Down -> x/X" << std::endl << "Right -> d/D" << std::endl << "Stay -> s/S" << std::endl;

	std::cout << std::endl << "To return menu press 9" << std::endl;
	while (_getch() != '9');
	return;
}

char Menu::Difficulty()const
{
	char ch;
	system("cls");
	_flushall();
	std::cout << "please Select Difficulty from the following:" << std::endl;
	std::cout << "(1) Novice" << std::endl;
	std::cout << "(2) Good" << std::endl;
	std::cout << "(3) Best" << std::endl;
	do
		ch = _getch();
	while (ch != '1' && ch != '2' && ch != '3');
	return ch;
}

bool Menu::Color()const
{
	char ch;
	system("cls");
	_flushall();

	std::cout << "please Select Color option from the following:" << std::endl;
	std::cout << "(1) With Color" << std::endl;
	std::cout << "(2) Without Color" << std::endl;
	do
		ch = _getch();
	while (ch != '1' && ch != '2');
	if (ch == '1')
		return true;
	return false;
}

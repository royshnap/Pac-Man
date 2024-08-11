// Tomer Newman 318599305
// Roy Shnap 316060151

#pragma once
#include "Board.h"
#include "Fruit.h"
#include "GameObject.h"
#include "Ghost.h"
#include "PacMan.h"
#include "Point.h"
#include <iostream>
#include <string>
#include <filesystem> // Added this include for std::filesystem

#define LOAD_ALL_FILES '1' // no color text
#define LOAD_A_FILE '2' //  color text
#define EXIT '9'
#define INSTRUCTIONS '8'
#define ESC 27
#define WIN_MES_POS 12, 36 // win message location
#define ESC_MES_POS 17, 28 // escape message location

namespace fs = std::filesystem; // Ensure that you have C++17 enabled for filesystem support

class Game { // this class runs the menu and the game with the help of class Board
private:
	Files fileVar;
	bool color;
	char difficulty;
	bool lost = false;
	bool load;
	bool save;
	bool silent;
	int numOfFrames;
	int sleepTimer;
	int lives;
public:
	void LoadFiles();
	void LoadAFile();
	void saveToFiles(std::vector <GameObject*> Actors); // Added std:: namespace qualifier
	bool setFiles();
	void start(Board& gameBoard);
	void startFromLoad(Board& gameBoard);
	void Pause(const Board& gameBoard) const;
	void Continue(const Board& gameBoard) const;
	void youWon() const;
	void youLost();
	void TestPassed(std::vector<int>& v1, std::vector <int>& v2); // Added std:: namespace qualifier
	int getLives()const;
	void setLives(const int _lives);
public:
	Game(bool _load, bool _silent, bool _color = true, int _difficulty = '1', bool _save = false, int _sleepTimer = 130)
		: silent(_silent), color(_color), difficulty(_difficulty), numOfFrames(0), sleepTimer(_sleepTimer), save(_save), load(_load), lives(3) {};

	bool isPacMeetsGhost(const Pacman& player, const std::vector <Ghost>& ghosts) const; // Added std:: namespace qualifier
	void MeetUp(const Board& board, Pacman& player, std::vector <Ghost>& ghosts, Fruit& fruit, std::vector <GameObject*>& Actors); // Added std:: namespace qualifier
	bool isPacMeetsFruit(const Pacman& player, Fruit& fruit) const;
	bool isGhostMeetsFruit(const std::vector <Ghost>& ghosts, const Fruit& fruit) const; // Added std:: namespace qualifier
	void setNewFruit(const Board& board, Fruit& fruit, const std::vector <Ghost>& ghosts, const Pacman& player) const; // Added std:: namespace qualifier
public:
	bool getColor() const;
	void setColor(bool _color);
	char getDifficulty() const;
	void incrementTime() { numOfFrames++; };
};

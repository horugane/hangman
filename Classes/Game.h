#pragma once
#include<iostream>
#include <string>
#include <vector>
#include <ctime>
#include <Windows.h>
#include "Word.h"

using namespace std;

class Game
{
private:
	int failCount, hintCount, wordCount;
	int failLimit, hintLimit, wordLimit;
	vector<Word*> wordBank;
public:
	// constructors and destructors
	Game();
	Game(int, int, int, int, int, int); 
	~Game();
	// getters and setters
	void setFailLimit();
	void setHintLimit();
	void setWordLimit();

	int getFailLimit();
	int getHintLimit();
	int getWordLimit();
	int getNumberWord();
	// functions

	void addWord(Word* word);
	void resetWordBank();
	void shuffleWordBank();
	void getWordList();
	Word* getOneWord(int index);
	void playGame();
};

#include "Game.h"

Game::Game()
{
	failCount = hintCount = wordCount = 0;
	failLimit = hintLimit = wordLimit = 0;
}

Game::Game(int failCount, int hintCount, int wordCount, 
		   int failLimit, int hintLimit, int wordLimit)
{
	this->failCount = failCount;
	this->hintCount = hintCount;
	this->wordCount = wordCount;
	this->failLimit = failLimit;
	this->hintLimit = hintLimit;
	this->wordLimit = wordLimit;
}

Game::~Game()
{
}

void Game::setFailLimit()
{
	cout << "Enter the limit for failed guesses: ";
	int fLimit;
	cin >> fLimit;
	failLimit = fLimit;
	cout << "Limit set successfully!\n" << endl;
	system("pause");
}

void Game::setHintLimit()
{
	int hLimit;
	do {
		cout << "Enter the limit for hints allowed: ";
		cin >> hLimit;
		if (hLimit > 0 && hLimit < wordLimit) {
			hintLimit = hLimit;
			cout << "Limit set successfully!\n" << endl;
			system("pause");
			break;
		}
		else {
			cout << "Invalid number of hint limit" << endl;
		}
	} while (!(hLimit > 0 && hLimit < wordLimit));
}

void Game::setWordLimit()
{
	cout << "Enter the limit of words to guess in a match: ";
	int wLimit;
	cin >> wLimit;
	if (wLimit < wordBank.size()) {
		wordLimit = wLimit;
		cout << "Limit set successfully!\n" << endl;
		system("pause");
	}
	else {
		while (wLimit >= wordBank.size()) {
			cout << "Error: Number of words to guess is larger than that of the Word Bank!" << endl;
			cout << "Try again: ";
			cin >> wLimit;
		}
	}
}

int Game::getFailLimit()
{
	return failLimit;
}

int Game::getHintLimit()
{
	return hintLimit;
}

int Game::getWordLimit()
{
	return wordLimit;
}

int Game::getNumberWord()
{
	return wordBank.size();
}

void Game::addWord(Word* word)
{
	wordBank.push_back(word);
	wordCount++;
}

void Game::resetWordBank()
{
	wordBank.clear();
}

void Game::shuffleWordBank()
{
	srand(time(0));
	int count = 0;
	while (true) {
		int ind1 = rand() % wordBank.size();
		int ind2 = rand() % wordBank.size();
		if (ind1 == ind2) {
			continue;
		}
		Word* tmp = wordBank[ind1];
		wordBank[ind1] = wordBank[ind2];
		wordBank[ind2] = tmp;
		count++;
		if (count > 10) {
			break;
		}
	}
}

void Game::getWordList()
{
	if (wordBank.empty()) {
		cout << "Word bank is empty, add more words!\n" << endl;
	}
	else {
		cout << "Displaying all words in the Word Bank:\n" << endl;
		for (const auto& word : wordBank) {
			cout << word->getText() << endl;
		}
		cout << endl;
	}
}

Word* Game::getOneWord(int index)
{
	return wordBank[index];
}

void Game::playGame()
{
	char letter, choice = '\0';
	Word* w;
	bool rerun = true, rerun2 = true;
	// automatic fail limit
	startGame:
	do {
		failCount = 0;
		int countFail = failLimit - 1;
		int n = rand() % wordBank.size();
		bool hintDisplayed = false;
		shuffleWordBank();
		w = getOneWord(n);
		system("cls");
		w->displayWord();
		while (failCount < failLimit && !w->isWordGuessed()) {
			cout << "\nGuess a letter: ";
			cin >> letter;
			if (w->checkGuess(letter) == 0) {
				failCount++;
				system("cls");
				w->displayWord();
				cout << "\nWrong guess, the letter does not exist for this word!" << endl;
				cout << "You have " << countFail-- << " tries left." << endl;
			}
			else {
				system("cls");
				w->displayWord();
				cout << "\nA letter has been found!" << endl;
			}
			if (failCount >= failLimit/2 && !hintDisplayed)
			{
				cout << "\nDo you want to display hint for the word? (Y/N): ";
				cin >> choice;
				if (choice == 'n' || choice == 'N') continue;
				else if (choice == 'y' || choice == 'Y') {
					cout << "\nDisplaying hint of the word: \n\n" << w->getHint() << endl;
					hintDisplayed = true;
				}
			}
			if (w->isWordGuessed()) {
				cout << "\nYou have guessed the correct word! Congratulations!" << endl;
				Sleep(3000);
				system("cls");
				cout << "Start a new game? (Y/N): "; cin >> choice;
				while (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N') {
					cout << "\033[1A"; // Move the cursor up one line
					cout << "\033[K"; // Clear the line
					cout << "\033[1A"; // Move the cursor up one line
					cout << "\033[K"; // Clear the line
					cout << "Invalid input, enter again. \nStart a new game? (Y/N): "; cin >> choice;
				}
				if (choice == 'n' || choice == 'N') {
					break;
				}
			}
		}
		if (failCount == failLimit) {
			cout << "\nToo many failed guesses! Our hero is slain by the death rope! \nGame Over..." << endl;
			Sleep(3000);
			system("cls");
			cout << "Gane over... Try again? (Y/N): "; cin >> choice;
			while (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N') {
				cout << "\033[1A"; // Move the cursor up one line
				cout << "\033[K"; // Clear the line
				cout << "\033[1A"; // Move the cursor up one line
				cout << "\033[K"; // Clear the line
				cout << "Invalid input, enter again. \nTry again? (Y/N): "; cin >> choice;
			}
			if (choice == 'y' || choice == 'Y') {
				goto startGame;
			}
			else if (choice == 'n' || choice == 'N') {
				rerun2 = false;
				break;
			}
		}
	} while (choice == 'y' || choice == 'Y');
}

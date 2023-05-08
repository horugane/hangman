#include "Game.h"

Game::Game()
{
	failCount = hintCount = wordCount = 0;
	failLimit = hintLimit = wordLimit = 0;
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
	cout << "Enter the limit of words to be guessed in a match: ";
	int wLimit;
	cin >> wLimit;
	wordLimit = wLimit;
	cout << "Limit set successfully!\n" << endl;
	system("pause");
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
		cout << "Displaying all words in the Word Bank:" << endl;
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
	char letter, choice;
	Word* w;
	bool rerun = true, rerun2 = true;
	failCount = 0;
	failLimit = 7;
	do {
		int n = rand() % wordBank.size();
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
				cout << "You have " << failLimit-- << " tries left." << endl;
			}
			else {
				system("cls");
				w->displayWord();
				cout << "\nA letter has been found!" << endl;
			}
			if (w->isWordGuessed()) {
				cout << "\nYou have guessed the correct word! Congratulations!" << endl;
				Sleep(3000);
			}
		}
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
		
	} while (choice == 'y' || choice == 'Y');

	if (failCount == failLimit) {
		while (rerun2) {
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
				rerun = true;
			}
			else if (choice == 'n' || choice == 'N') {
				rerun2 = false;
				break;
			}
		}
	}
}

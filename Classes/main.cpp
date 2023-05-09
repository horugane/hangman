#include <iostream>
#include <windows.h>
#include "Game.h"
#include "Menu.h"
#include "Word.h"
using namespace std;

void displayWelcomeMessage();

enum ACTION {
	ADD,
	RESET,
	DISPLAY_WB,
	CHALLENGER,
	SET_WORD,
	SET_FAILED,
	SET_HINT,
	PLAY,
	CREDIT,
	EXIT
};

int main() {
	// Main menu
	Menu* mainMenu = new Menu("Main Menu", "");
	Menu* play = new Menu("Start Game", "Game starting", PLAY);
	Menu* challenger = new Menu("Challenger Option", "", CHALLENGER);
	Menu* credit = new Menu("Credit\n", "", CREDIT);
	Menu* exit = new Menu("Exit", "See you soon", EXIT);


	mainMenu->addSubMenu(play);
	mainMenu->addSubMenu(challenger);
	mainMenu->addSubMenu(credit);
	mainMenu->addSubMenu(exit);
	
	// Challenger Main menu
	Menu* menuChallenger = new Menu("Challenger Option", "Challenger's menu\n");
	Menu* manageGameSettings = new Menu("Manage Game Settings", "Change the game's settings\n");
	Menu* manageWordBank = new Menu("Manage Word Bank\n", "Modify the word bank\n");

	menuChallenger->addSubMenu(manageGameSettings);
	menuChallenger->addSubMenu(manageWordBank);
	menuChallenger->addSubMenu(mainMenu);
	
	// Manage game settings menu
	Menu* setTotalWords = new Menu("Set the number of words to be guessed in one game", "", SET_WORD);
	Menu* setAllowedFails = new Menu("Set the number of failed guess allowed in one game", "", SET_FAILED);
	Menu* setAllowedHints = new Menu("Set the number of hints allowed in one game\n", "", SET_HINT);

	manageGameSettings->addSubMenu(setTotalWords);
	manageGameSettings->addSubMenu(setAllowedFails);
	manageGameSettings->addSubMenu(setAllowedHints);
	manageGameSettings->addSubMenu(menuChallenger);

	// Manage Word Bank menu
	Menu* addWord = new Menu("Add a new word", "", ADD);
	Menu* resetWord = new Menu("Reset the word bank", "", RESET);
	Menu* displayWordBank = new Menu("Display words in the Word Bank\n", "", DISPLAY_WB);

	manageWordBank->addSubMenu(addWord);
	manageWordBank->addSubMenu(resetWord);
	manageWordBank->addSubMenu(displayWordBank);
	manageWordBank->addSubMenu(menuChallenger);

	// introduction to the program
	Menu* currentMenu = mainMenu;
	cout << "+----------------------------+" << endl;
	cout << "|Welcome to the Hangman Game!|" << endl;
	cout << "+----------------------------+" << endl;
	system("pause");

	// declare class variables
	Game game(0, 2, 4, 7, 2, 4);
	Word w;
	Word word1("lion", "king of the jungle"),
		 word2("england", "once, the sun never slept in this country"),
		 word3("pineapple", "fruit"),
		 word4("sword", "two-edge medieval melee weapon");
	
	Word* w1 = new Word(word1);
	Word* w2 = new Word(word2);
	Word* w3 = new Word(word3);
	Word* w4 = new Word(word4);

	game.addWord(w1);
	game.addWord(w2);
	game.addWord(w3);
	game.addWord(w4);

	bool answer = true;
	while (answer == true) {
		string input;
		currentMenu->displayMenu();
		int choice = currentMenu->promtOption();
		currentMenu = currentMenu->getSubMenu(choice);
		switch (currentMenu->getAction()) {
		case -1:
			break;
		case PLAY: {
			system("cls");
			displayWelcomeMessage();
			system("pause");
			game.playGame();
			currentMenu = mainMenu;
			break;
		}
		case CHALLENGER:
			currentMenu = menuChallenger;
			break;
		case SET_WORD:
			system("cls");
			game.setWordLimit();
			currentMenu = manageGameSettings;
			break;
		case SET_FAILED:
			system("cls");
			game.setFailLimit();
			currentMenu = manageGameSettings;
			break;
		case SET_HINT:
			system("cls");
			game.setHintLimit();
			currentMenu = manageGameSettings;
			break;
		case ADD:
		{
			// declare within case ADD for looping
			char choice; bool rerun = true;
			while (rerun) {
				system("cls");
				cout << "Enter the word to be added: ";
				cin.ignore();
				getline(cin, input);
				Word* newWord = new Word();
				newWord->setText(input);
				cout << "Enter the hint of the word: ";
				cin.ignore();
				getline(cin, input);
				newWord->setHint(input);
				game.addWord(newWord);
				cout << "\nThe word has been sucessfully added to the word bank!\n" << endl;
				cout << "Do you want to add more words? (Y/N): ";
				cin >> choice;
				while (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N') {
					cout << "\033[1A"; // Move the cursor up one line
					cout << "\033[K"; // Clear the line
					cout << "Invalid input, enter again (Y/N): "; cin >> choice;
				}
				if (choice == 'y' || choice == 'Y') {
					rerun = true;
				}
				else if (choice == 'n' || choice == 'N') {
					rerun = false;
				}
			}
			currentMenu = manageWordBank;
			break;
		}
		case RESET:
			system("cls");
			cout << "Removing all words and resetting the word bank..." << endl;
			Sleep(1500);
			game.resetWordBank();
			cout << "\nThe Word Bank has been reset! \nPlease add new words to the Word Bank.\n" << endl;
			system("pause");
			currentMenu = manageWordBank;
			break;
		case DISPLAY_WB:
			system("cls");
			game.getWordList();
			system("pause");
			currentMenu = manageWordBank;
			break;
		case CREDIT:
			currentMenu = credit;
			system("cls");
			cout << "Listing the members contributing to this program:\n";
			cout << "\n+-----------------------+";
			cout << "\n|    Duong Anh Trung    |" << endl;
			cout << "+-----------------------+\n" << endl;
			system("pause");
			currentMenu = mainMenu;
			break;
		case EXIT:
			answer = false;
			break;
		default:
			cout << "Invalid action!" << endl;
			break;
		}
	}
	return 0;
}

void displayWelcomeMessage()
{
	cout << "+----------------------------------------------+"
		 << "\n|The demon lord is threatening the peace of the|"
		 << "\n| world once again! Should he not be stopped,  |"
		 << "\n|    the world will be doomed to oblivion!     |"
		 << "\n+----------------------------------------------+"
		 << "\n|   Our hero has been captured after a fierce  |"
		 << "\n|battle with the demon lord, and is locked by a|"
		 << "\n| magical lock that can only be unlocked with  |"
		 << "\n| the correct password. Your task is to guess  |"
		 << "\n| the hidden password to free the hero, but be |"
		 << "\n|  warned: too many incorrect guesses and our  |"
		 << "\n|hero will be choked to death by the death rope|"
		 << "\n+----------------------------------------------+"
		 << "\n|           Let the rescue begins!             |"
		 << "\n+----------------------------------------------+\n" << endl;
}

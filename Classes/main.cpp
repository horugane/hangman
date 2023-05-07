#include <iostream>
#include <windows.h>
#include "Game.h"
#include "Menu.h"
#include "Word.h"


using namespace std;

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
	Game game;
	Word w;
	Word* newWord = new Word();

	bool answer = true;
	while (answer == true) {
		string input;
		currentMenu->displayMenu();
		int choice = currentMenu->promtOption();
		currentMenu = currentMenu->getSubMenu(choice);
		switch (currentMenu->getAction()) {
		case -1:
			break;
		case PLAY:
			break;
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
					cout << "Invalid input, enter again: "; cin >> choice;
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
			cout << "\n\tGroup 3";
			cout << "\n+-----------------------+";
			cout  << "\n|Nguyen Nhu Hoang Phuong|" << "\n|Dang Trung Hieu        |" << "\n|Duong Anh Trung        |" << endl;
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
#include "Menu.h"

Menu::Menu() : name(""), description(""), action(-1)
{
	subMenu.clear();
}

Menu::Menu(string name, string description, int action)
{
	this->name = name;
	this->description = description;
	this->subMenu.clear();
	this->action = action;
}

Menu::~Menu()
{
	if (!subMenu.empty()) {
		for (int i = 0; i < subMenu.size(); i++) {
			if (subMenu[i]) {
				delete subMenu[i];
			}
		}
		subMenu.clear();
	}
}

void Menu::setName(string name)
{
	this->name = name;
}

void Menu::setDescription(string description)
{
	this->description = description;
}

void Menu::setAction(int action)
{
	this->action = action;
}

string Menu::getName()
{
	return name;
}

string Menu::getDescription()
{
	return description;
}

int Menu::getAction()
{
	return action;
}

void Menu::displayMenu()
{
	system("cls");
	cout << "\t\t" << name << "\t\t" << endl;
	cout << description << endl;
	for (int i = 0; i < subMenu.size(); i++) {
		cout << i + 1 << ". " << subMenu[i]->getName() << endl;
	}
}
	
void Menu::addSubMenu(Menu* m)
{
	this->subMenu.push_back(m);
	// m->subMenu.push_back(this) : auto push parent menu
}

int Menu::promtOption()
{
	bool errorDisplayed = false; //flag to track if an error message has been displayed
	while (true) {
		int option;
		cout << "\nPick an option: ";
		cin >> option;
		try {
			if (cin.fail()) {
				cin.clear();
				cin.ignore();
				throw "Invalid input, strings or characters are not allowed.";
			}
			else if (option < 1 || option > subMenu.size()) {
				throw "Menu out of range";
			}
			else {
				return option;
			}
		}
		catch (const char* error) {
			cin.clear();
			cin.ignore();
			if (errorDisplayed) {
				cout << "\033[1A";
				cout << "\033[K";
				cout << "\033[1A";
				cout << "\033[1A";
				cout << "\033[K";
				cout << "Error: " << error << endl;
			}
			else {
				cout << "\033[1A"; // Move the cursor up one line
				cout << "\033[K"; // Clear the line
				cout << "Error: " << error << endl;
				errorDisplayed = true;
			}
		}
	}
}

Menu* Menu::getSubMenu(int index)
{
	if (index > 0 && index <= subMenu.size()) {
		index--;
		return subMenu[index];
	}
	else {
		return NULL;
	}
}
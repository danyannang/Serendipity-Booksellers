#define_CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>
#include "Project.h"

using namespace std;

struct book
{
	string isbn;
	string date;
	string title;
	string author;
	double bPrice;
	double sPrice;
};

int main() {
	string choice;
	Module *user = new Module; //Pointer to be used for menu interaction
	delete user;
	user = nullptr;

	do { //Main menu loop
		cout << "--Serendipity Booksellers--\n";
		cout << "         Main Menu\n";
		cout << "1. Cashier Module\n";
		cout << "2. Inventoary Module\n";
		cout << "3. Report Module\n";
		cout << "4. Exit program.\n";
		cout << "Enter your Choice: ";
		getline(cin, choice);
		if (choice == "1")
		{
			cout << "You have selected cashier.\n";
			user = new Cashier;
			user->cashierMenu(); //Calls the book module.

			delete user;
			user = nullptr; //resets the pointer to be used in another module;
			cout << "Would you like to return to the main menu? (y/n): "; //Selection for returning to main menu or closig program.
			getline(cin, choice);
		}
		else if (choice == "2")
		{
			//run inventory module;
			cout << "Would you like to return to the main menu? (y/n): ";
			getline(cin, choice);
		}
		else if (choice == "3")
		{
			//run report Module
			cout << "Would you like to return to the main menu? (y/n): ";
			getline(cin, choice);
		}
		else
			choice = "n";
	} while (choice == "Y" || choice == "y");


	system("pause");
	return 0;
}

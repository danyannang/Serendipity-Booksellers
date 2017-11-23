#define_CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>
#include "Project.h"

using namespace std;

const double tax = 0.0875;

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
	Module *user = new Module;
	delete user;
	user = nullptr;

	do {
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
			delete user;
			user = nullptr;
			cout << "Would you like to return to the main menu? (y/n): ";
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

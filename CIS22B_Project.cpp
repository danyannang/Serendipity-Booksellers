#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>
#include "Project.h"

using namespace std;
//
//
//problem seems to be about data is allocated into bookdata for this test project.
//
//
int main() {
	string choice, tempstring;
	int newSize = 2;
	string **bookData;
	bookData = new std::string*[newSize];
	for (int i = 0; i < newSize; i++)
	{
		bookData[i] = new std::string[8];
	}
	Module *user = new Module; //Pointer to be used for menu interaction
	user->createBookArray(bookData);
	int mainsize = user->getinvenSize();


	for (int i = 0; i < mainsize - 2; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			tempstring += bookData[i][j];
		}
	}
	Module admin = (*user) + tempstring; //operator overload to create backupdata for booklist.

	delete user;
	user = nullptr;

	do { //Main menu loop
		cout << "--Serendipity Booksellers--\n";
		cout << "         Main Menu\n***************************\n";
		cout << "1. Cashier Module\n\n";
		cout << "2. Inventoary Module\n\n";
		cout << "3. Report Module\n\n";
		cout << "4. Exit program.\n\n";
		cout << "Enter your Choice: ";
		getline(cin, choice);
		if (choice == "1")
		{
			cout << "You have selected the cashier module.\n";
			user = new Cashier;
			user->setInvenSize(mainsize);
			user->cashierMenu(bookData); //Calls the book module.
			mainsize = user->getinvenSize();

			delete user;
			user = nullptr; //resets the pointer to be used in another module;
			cout << "Would you like to return to the main menu? (y/n): "; //Selection for returning to main menu or closig program.
			getline(cin, choice);
		}
		else if (choice == "2")
		{
			cout << "You have selected the inventory module.\n";
			user = new Inventory;
			user->setInvenSize(mainsize);
			user->inventoryMenu(bookData);
			mainsize = user->getinvenSize();

			delete user;
			user = nullptr;
			cout << "Would you like to return to the main menu? (y/n): ";
			getline(cin, choice);
		}
		else if (choice == "3")
		{
			cout << "You have selected the report module.\n";//
			user = new Report;
			user->setInvenSize(mainsize);
			user->reportMenu(bookData);
			mainsize = user->getinvenSize();

			delete user;
			user = nullptr;
			cout << "Would you like to return to the main menu? (y/n): ";
			getline(cin, choice);
		}
		else
			choice = "n";
	} while (choice == "Y" || choice == "y");
	for (int i = 0; i < mainsize - 1; i++)
	{
		delete[] bookData[i];
	}
	delete[] bookData;
	bookData = nullptr;


	system("pause");
	return 0;
}

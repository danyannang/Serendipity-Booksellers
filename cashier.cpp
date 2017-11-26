#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include "Project.h"

Module::Module() //Add creation of book array.
{
	std::cout << "This is a flag to show that a Module has been created.\n";
}
void Module::createBookArray()
{
	std::cout << "Creating array.\n";
	std::string unsplit;
	std::ifstream iniBooks;
	iniBooks.open("booklist.txt");
	if (!iniBooks)
		std::cout << "Error Opening file.\n";
	int nthBook = 0;
	for (int i = 0; i < 25; i++) //primitive loop which creates the entire array, but no filter.
	{
		for (int j = 0; j < 8; j++)
		{
			std::getline(iniBooks, unsplit, '\t');
			bookData[i][j] = unsplit;
		}
	}
	iniBooks.close();
}
void Module::cashierMenu()
{
	std::cout << "Check the child class.\n";
}
void Module::inventoryMenu()
{
	std::cout << "Check the child class.\n";
}
int Module::bookSearch() //(booklist[i][j]
{
	std::string isbn;
	std::cout << "Enter the isbn of the book you are searching: ";
	std::getline(std::cin, isbn);
	//linear search to find isbn;
	int index = 0;
	int position = -1;
	bool found = false;
	while (index < 25 && !found) //100 is fake size declarator for the array
	{
		if (bookData[index][ISBN] == isbn)
		{
			found = true;
			position = index;
		}
		index++;
	}
	return position;
}
Cashier::Cashier()
{
	std::cout << "This is a flag to show that a Cashier has been created.\n";
	total = 0;
	subtotal = 0;
	tax = 0;
	taxRate = .0875;
}
void Cashier::cashierMenu() //note for outpitting things neatly books neatly. store books in array.
{
	int arrayposition;
	int purchasenumber = 0;
	std::string choice;
	std::cout << "Serendipity BookSellers\n";
	std::cout << "Date: " << std::endl;
	do {
		std::cout << "Add a book? (y/n): ";
		std::getline (std::cin, choice);
		if (choice == "y" || choice =="Y")
		{
			arrayposition = bookSearch();//booklist[i][j]);
			if (arrayposition != -1)//output line for the added book
			{
				std::string tempstring;
				int count;
				setSubTotal(arrayposition);//Adds to total
				if (bookData[arrayposition][QUANTITY] != "0")
				{
					std::cout << "Qty\tISBN\t\tTitle\t\t\t\t\tPrice\tTotal\n" << std::endl;
					std::cout << bookData[arrayposition][QUANTITY] << "\t" << bookData[arrayposition][ISBN] << " " << bookData[arrayposition][TITLE] << " \t$" << bookData[arrayposition][RETAIL] << " $" << subtotal << std::endl;
					for (int j = 0; j < 8; j++) //stores all the purchased books in a new array.
					{
						checkoutBooks[purchasenumber][j] = bookData[arrayposition][j];
					}
					purchasenumber++;
					tempstring = bookData[arrayposition][QUANTITY];
					count = std::stoi(tempstring);
					count -= 1;
					tempstring = std::to_string(count);
					bookData[arrayposition][QUANTITY] = tempstring;
				}
				else if (bookData[arrayposition][QUANTITY] == "0")
				{
					std::cout << "That book is out of stock.\n";
				}
			}
			else if (arrayposition == -1)
				std::cout << "Book not found.\n";
		}
	} while (arrayposition = -1 && choice == "y" || choice == "Y");
	std::cout << "Qty\tISBN\t\tTitle\t\t\t\t\tPrice\n" << std::endl;
	for (int i = 0; i < purchasenumber; i++)
	{
		std::cout << checkoutBooks[i][QUANTITY] << "\t" << checkoutBooks[i][ISBN] << " " <<checkoutBooks[i][TITLE] << " \t$" << checkoutBooks[i][RETAIL] << std::endl;
	}
	setTotal(subtotal);
	std::cout << "\tSubtotal: " << std::setw(4) << "$" << std::setprecision(2) << subtotal << std::endl;
	std::cout << "\tTax: " << std::setw(9) << "$" << std::setprecision(2) << tax << std::endl;
	std::cout << "\tTotal: " << std::setw(7) << "$" << std::setprecision(2) << total << std::endl;
}
void Cashier::setTotal(double x)
{
	tax = (subtotal*taxRate);
	total = subtotal + tax;
}
void Cashier::setSubTotal(int x)
{
	double temp = std::stod(bookData[x][RETAIL]);
	subtotal += temp;
}
Inventory::Inventory()
{

}
void Inventory::inventoryMenu()
{
	std::cout << "1. Add a book" << std::endl;
	std::cout << "2. Delete a book" << std::endl;
	std::cout << "3. Edit book info" << std::endl;
	std::cout << "4. Back to Module menu" << std::endl;

	std::string choice;
	std::cin >> choice;
	if (choice == "1")
	{
		//addBook();
	}
	else if (choice == "2")
	{
		//deleteBook();
	}
	else if (choice == "3")
	{
		//bookListing(choice);
		//editBook();
	}
	else if (choice == "4")
	{
		//Code to go back to main Module's menu method
	}
}

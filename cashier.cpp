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
	iniBooks.open("BookStock.txt");
	if (!iniBooks)
		std::cout << "Error Opening file.\n";
	int nthBook = 0;
	/*for (int i = 0; i < 100; i++) //primitive loop which creates the entire array, but no filter.
	{
		for (int j = 0; j < 7; j++)
		{
			std::getline(iniBooks, unsplit, '\t');
			bookData[i][j] = unsplit;
		}
	}*/
	//Loop for creating the array without multiple instances of same book.
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			bool exists = false;
			std::getline(iniBooks, unsplit, '\t');
			if (j == 0) //isbn catcher.
			{
				for (int k = 0; k < i; k++)
				{
					if (bookData[k][j] == unsplit) //if any of the previous instances of book match the current one, increment quantity
					{
						exists = true;
						//increment quantity
					}
					else if (exists == false) //if not continue storing data in the array
					{
						bookData[i][j] = unsplit;
						//set quantity to one
					}
				}
			}
			else if (j != 0 && exists == false) //store the rest of the essential data into the same array if the isbn was not the same
			{
				bookData[i][j] = unsplit;
			}
		}
	}
	iniBooks.close();
	std::cout << bookData[2][ISBN] << std::endl;
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
	std::cin >> isbn;
	//linear search to find isbn;
	int index = 0;
	int position = -1;
	bool found = false;
	/*while (index < 100 && !found) //100 is fake size declarator for the array
	{
		if (bookData[index][ISBN] = isbn)
		{
			found = true;
			position = index;
			break;
			return position;
		}
		index++;
	}*/

	return position;
}
Cashier::Cashier()
{
	std::cout << "This is a flag to show that a Cashier has been created.\n";
	total = 0;
	subtotal = 0;
	tax = 0;
}
void Cashier::cashierMenu()
{
	int arrayposition = -1;
	std::string choice;
	std::cout << "Serendipity BookSellers\n";
	std::cout << "Date: " << std::endl;
	std::cout << "Qty    ISBN        Title      Price           Total\n";
	do {
		std::cout << "Add a book? (y/n): ";
		std::getline (std::cin, choice);
		if (choice == "y" || choice =="Y")
		{
			arrayposition = bookSearch();//booklist[i][j]);
			if (arrayposition != -1)//output line for the added book
			{
				setSubTotal(arrayposition);//Adds to total
				//std::cout << book[arrayposition][QUANTITY] << " " << book[arrayposition][ISBN] << " " << book[arrayposition][TITLE] << " $" << book[arrayposition][RETAIL] << " $" << subtotal;
			}
			else if (arrayposition == -1)
				std::cout << "Book not found.\n";
		}
	} while (arrayposition = -1 && choice == "y" || choice == "Y");

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
	//double temp = std::stod(book[x][RETAIL])
	//total+=temp;
}
void Cashier::setTaxRate()
{
	taxRate = .0875;
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

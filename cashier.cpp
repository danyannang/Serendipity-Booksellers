#include <iostream>
#include <string>
#include <iomanip>
#include "Project.h"

Module::Module() //Add creation of book array.
{
	std::cout << "This is a flag to show that a Module has been created.\n";
}
void Module::cashierMenu()
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
		if (booklist[index][ISBN] = isbn)
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
std::string Module::titleCompare()
{
	return 0;
}
Cashier::Cashier()
{
	std::cout << "This is a flag to show that a Cashier has been created.\n";
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
		std::cin >> choice;
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
	//double temp = std::stod(book[x][RETAIL]) //string to double for retail value
	//total+=temp;
}
void Cashier::setTaxRate()
{
	taxRate = .0875;
}

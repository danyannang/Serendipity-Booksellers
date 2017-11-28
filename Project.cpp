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
void Module::reportMenu()
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
//This is the start of the cashier module functions.
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
//This is the start of the inventory module functions.
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
//This is the start of the report modules functions.
Report::Report()
{
	std::cout << "This is a flag to show that a report has been created.\n";
}
void Report::reportMenu()
{
	std::string choice;
	do {
		std::cout << "1. Inventory Listing\n2. Inventory Wholesale Value\n3. Inventory Retail Value\n4. Listing by Quantity\n5. Listing by Cost\n6. Listing by Age\n7. Return to menu\n";
		std::cout << "Enter your choice: ";
		std::getline(std::cin, choice);
		if (choice == "1")
			invenList();
		else if (choice == "2")
			wholesaleVal();
		else if (choice == "3")
			retailVal();
		else if (choice == "4")
			quantitylist();
		else if (choice == "5")
			wholeCostList();
		else if (choice == "6")
			dateList();
		if (choice != "7")
		{
			std::cout << "Would you like to select another inventory function? (y/n): ";
			std::getline(std::cin, choice);
		}
	} while (choice != "7" || choice == "Y" || choice == "y");
}
void Report::invenList()
{
	std::cout << std::setw(10) << "ISBN" << std::setw(30) << "TITLE" << std::setw(15) << "AUTHOR" << std::setw(15) << "PUBLISHER" << std::setw(15) << "DATE" << std::setw(5) << "#" << std::setw(15) << "WHOLESALECOST" << std::setw(15) << "RETAIL PRICE" << std::endl;
	for (int i = 0; i < 25; i++)
	{

		std::cout << std::endl;
		for (int k = 0; k < 8; k++)
		{
			switch (k)
			{

			case 0:
				std::cout << std::fixed << std::left << std::setw(12) << bookData[i][k];
				break;
			case 1:
				std::cout << std::fixed << std::left << std::setw(30) << bookData[i][k];
				break;
			case 2:
				std::cout << std::fixed << std::left << std::setw(15) << bookData[i][k];
				break;
			case 3:
				std::cout << std::fixed << std::left << std::setw(15) << bookData[i][k];
				break;
			case 4:
				std::cout << std::fixed << std::left << std::setw(15) << bookData[i][k];
				break;
			case 5:
				std::cout << std::fixed << std::left << std::setw(5) << bookData[i][k];
				break;
			case 6:
				std::cout << std::fixed << std::left << std::setw(15) << bookData[i][k];
				break;
			case 7:
				std::cout << std::fixed << std::left << std::setw(15) << bookData[i][k];
				break;
			}
		}
		std::cout << std::endl;
	}
}
void Report::wholesaleVal()
{
	std::cout << std::endl;
	double  total = 0.0;
	std::cout << "***WHOLESALE COSTS*** " << std::endl << std::endl;
	for (int i = 0; i < 25; i++)
	{
		std::cout << std::left << std::setw(80) << bookData[i][1] + ": " << std::setw(6) << "$" + bookData[i][5] << std::endl;
		double isample = std::stod(bookData[i][5]);
		total += isample;
	}
	std::cout << std::endl << "TOTAL WHOLESALE COST: " << total << " $" << std::endl << std::endl;
}
void Report::retailVal()
{
	std::cout << std::endl;
	double  total = 0.0;
	std::cout << "***RETAIL COSTS***" << std::endl << std::endl;
	for (int i = 0; i < 25; i++)
	{
		std::cout << std::left << std::setw(80) << bookData[i][1] + ": " << std::setw(6) << "$" + bookData[i][6] << std::endl;
		double isample = std::stod(bookData[i][6]);
		total += isample;
	}
	std::cout << std::endl << "TOTAL RETAIL COST: " << "$" << total << std::endl << std::endl;
}
void Report::swapV(double *x, double *y) //Need to check and update
{
	double temp = *x;
	*x = *y;
	*y = temp;
}
void Report::swapV(int *x, int *y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}
void Report::quantitylist()//need to check and update
{
	std::cout << std::setw(10) << "ISBN" << std::setw(30) << "TITLE" << std::setw(15) << "AUTHOR" << std::setw(15) << "PUBLISHER" << std::setw(15) << "DATE" << std::setw(5) << "#" << std::setw(15) << "WHOLESALECOST" << std::setw(15) << "RETAIL PRICE" << std::endl;
	int itemp[24][2] = {};
	int swap1 = 0;
	int swap2 = 0;
	for (int i = 0; i < 24; i++)
	{
		itemp[i][0] = i;
		itemp[i][1] = std::stoi(bookData[i][7]);
	}
	for (int k = 0; k < 24; k++)
	{

		for (int i = 0; i < 24; i++)
		{

			if (itemp[i][1] > itemp[k][1])
			{

				swapV(&itemp[i][1], &itemp[k][1]);

				swapV(&itemp[k][0], &itemp[i][0]);
				k = i;
			}
		}

	}
	for (int i = 0; i < 24; i++)
	{
		for (int y = 0; y < 8; y++)
		{
			switch (y)
			{
			case 0:
				std::cout << std::setw(10) << bookData[itemp[i][0]][y] << std::endl;
				break;
			case 1:
				std::cout << std::setw(30) << bookData[itemp[i][0]][y] << std::endl;
				break;
			case 2:
				std::cout << std::setw(15) << bookData[itemp[i][0]][y] << std::endl;
				break;
			case 3:
				std::cout << std::setw(15) << bookData[itemp[i][0]][y] << std::endl;
				break;
			case 4:
				std::cout << std::setw(15) << bookData[itemp[i][0]][y] << std::endl;
				break;
			case 5:
				std::cout << std::setw(5) << bookData[itemp[i][0]][y] << std::endl;
				break;
			case 6:
				std::cout << std::setw(15) << bookData[itemp[i][0]][y] << std::endl;
				break;
			case 7:
				std::cout << std::setw(15) << bookData[itemp[i][0]][y] << std::endl;
				break;
			}
		}
	}

}
void Report::wholeCostList()
{
	std::cout << std::setw(10) << "ISBN" << std::setw(30) << "TITLE" << std::setw(15) << "AUTHOR" << std::setw(15) << "PUBLISHER" << std::setw(15) << "DATE" << std::setw(5) << "#" << std::setw(15) << "WHOLESALECOST" << std::setw(15) << "RETAIL PRICE" << std::endl;
	double itemp[24][2] = {};
	int swap1 = 0;
	int swap2 = 0;

	for (int i = 0; i < 9; i++)
	{
		itemp[i][0] = i;
		itemp[i][1] = std::stod(bookData[i][5]);
	}
	for (int k = 0; k < 24; k++)
	{

		for (int i = 0; i < 24; i++)
		{

			if (itemp[i][1] > itemp[k][1])
			{

				swapV(&itemp[i][1], &itemp[k][1]);

				swapV(&itemp[k][0], &itemp[i][0]);
				k = i;
			}
		}

	}

	for (int i = 0; i < 24; i++)
	{
		for (int y = 0; y < 8; y++)
		{
			int x = itemp[i][0]; //Is the base array supposed to be what is outputted here? or the temparray?
			switch (y)
			{
			case 1:
				std::cout << std::setw(15) << bookData[x][y] << std::endl;
				break;
			case 2:
				std::cout << std::setw(15) << bookData[x][y] << std::endl;
				break;
			case 3:
				std::cout << std::setw(15) << bookData[x][y] << std::endl;
				break;
			case 4:
				std::cout << std::setw(15) << bookData[x][y] << std::endl;
				break;
			case 5:
				std::cout << std::setw(15) << bookData[x][y] << std::endl;
				break;
			case 6:
				std::cout << std::setw(15) << bookData[x][y] << std::endl;
				break;
			case 7:
				std::cout << std::setw(15) << bookData[x][y] << std::endl;
				break;
			case 8:
				std::cout << std::setw(15) << bookData[x][y] << std::endl;
				break;
			case 9:
				std::cout << std::setw(15) << bookData[x][y] << std::endl;
				break;
			case 10:
				std::cout << std::setw(15) << bookData[x][y] << std::endl;
				break;
			case 11:
				std::cout << std::setw(15) << bookData[x][y] << std::endl;
				break;
			case 12:
				std::cout << std::setw(15) << bookData[x][y] << std::endl;
				break;
			case 13:
				std::cout << std::setw(15) << bookData[x][y] << std::endl;
				break;
			case 14:
				std::cout << std::setw(15) << bookData[x][y] << std::endl;
				break;
			case 15:
				std::cout << std::setw(15) << bookData[x][y] << std::endl;
				break;
			case 16:
				std::cout << std::setw(15) << bookData[x][y] << std::endl;
				break;
			case 17:
				std::cout << std::setw(15) << bookData[x][y] << std::endl;
				break;
			case 18:
				std::cout << std::setw(15) << bookData[x][y] << std::endl;
				break;
			case 19:
				std::cout << std::setw(15) << bookData[x][y] << std::endl;
				break;
			case 20:
				std::cout << std::setw(15) << bookData[x][y] << std::endl;
				break;
			case 21:
				std::cout << std::setw(15) << bookData[x][y] << std::endl;
				break;
			case 22:
				std::cout << std::setw(15) << bookData[x][y] << std::endl;
				break;
			case 23:
				std::cout << std::setw(15) << bookData[x][y] << std::endl;
				break;
			case 24:
				std::cout << std::setw(15) << bookData[x][y] << std::endl;
				break;
			}
		}
	}
}
void Report::dateList()
{
	std::cout << "Date list is not ready.\n";
}
